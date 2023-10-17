#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include <thread>
#include <signal.h>
#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
    _udpSock = -1;
    _tcpSock = -1;
    _clientSock = -1;
    Init();
}

NetworkManager::~NetworkManager()
{
    close(_clientSock);
    close(_udpSock);
    close(_tcpSock);

    // 스레드 종료될때까지 기다리기
    if (_udpThread->joinable())
        _udpThread->join();
    if (_tcpThread->joinable())
        _tcpThread->join();
    
    // 안끝났으면 제거
    if (_udpThread)
        delete _udpThread;
    if (_tcpThread)
        delete _tcpThread;
}

void NetworkManager::StartClientFinder()
{
    _udpSock = socket(AF_INET, SOCK_DGRAM, 0);
    if (_udpSock < 0) 
    {
        std::cerr << "UDP 소켓 만들기 실패\n";
        return;
    }

    int broadcastEnable = 1;
    int ret = setsockopt(_udpSock, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));
    if (ret) 
    {
        std::cerr << "UDP 소켓 옵션 설정 실패\n";
        return;
    }

    struct sockaddr_in broadcastAddr;
    memset(&broadcastAddr, 0, sizeof(broadcastAddr));
    broadcastAddr.sin_family = AF_INET;
    broadcastAddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    broadcastAddr.sin_port = htons(12345);

    while (true) 
    {
        if (_clientSock >= 0)
            continue;

        const char* broadcastMessage = "RaspberryController";
        ret = sendto(_udpSock, broadcastMessage, strlen(broadcastMessage), 0, (struct sockaddr*)&broadcastAddr, sizeof(broadcastAddr));
        if (ret < 0) 
        {
            std::cerr << "UDP 브로드 캐스팅 실패\n";
            break;
        }

        usleep(100000); // 100ms 마다 전송
    }

    close(_udpSock);
}

void NetworkManager::StartClientAccepter()
{
    _tcpSock = socket(AF_INET, SOCK_STREAM, 0);
    if (_tcpSock < 0) 
    {
        std::cerr << "TCP 소켓 생성 실패\n";
        return;
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(23456);

    if (bind(_tcpSock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) 
    {
        std::cerr << "TCP 소켓 바인딩 실패\n";
        return;
    }

    if (listen(_tcpSock, 1) < 0) 
    {
        std::cerr << "TCP 소켓 리스닝 실패\n";
        return;
    }

    while (true) 
    {
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        _clientSock = accept(_tcpSock, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (_clientSock < 0) 
        {
            std::cerr << "TCP 연결 실패\n";
            break;
        }
    }

    close(_tcpSock);
}

void NetworkManager::Init()
{
    // SIGPIPE 시그널 무시
    signal(SIGPIPE, SIG_IGN); // 연결이 갑자기 종료될시 발생

    _udpThread = new std::thread(&NetworkManager::StartClientFinder, this);
    _tcpThread = new std::thread(&NetworkManager::StartClientAccepter, this);
}

void NetworkManager::Send(int32_t data)
{
    if (_clientSock < 0)
        return;

    int ret = send(_clientSock, &data, sizeof(data), 0);
    if (ret < 0) 
    {
        std::cerr << "TCP 데이터 전송 실패\n";
        _clientSock = -1;
    }
}
