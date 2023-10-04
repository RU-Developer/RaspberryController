#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include <thread>

void udpBroadcast() 
{
    int udpSock = socket(AF_INET, SOCK_DGRAM, 0);
    if (udpSock < 0) 
    {
        std::cerr << "Error creating UDP socket\n";
        return;
    }

    int broadcastEnable = 1;
    int ret = setsockopt(udpSock, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));
    if (ret) 
    {
        std::cerr << "Error setting socket options\n";
        return;
    }

    struct sockaddr_in broadcastAddr;
    memset(&broadcastAddr, 0, sizeof(broadcastAddr));
    broadcastAddr.sin_family = AF_INET;
    broadcastAddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    broadcastAddr.sin_port = htons(12345);

    while (true) 
    {
        const char* broadcastMessage = "Hello, Unity!";
        ret = sendto(udpSock, broadcastMessage, strlen(broadcastMessage), 0, (struct sockaddr*)&broadcastAddr, sizeof(broadcastAddr));
        if (ret < 0) 
        {
            std::cerr << "Error sending UDP broadcast\n";
            break;
        }

        usleep(100000); // 100ms delay
    }

    close(udpSock);
}

void acceptTcpConnection() 
{
    int tcpSock = socket(AF_INET, SOCK_STREAM, 0);
    if (tcpSock < 0) 
    {
        std::cerr << "Error creating TCP socket\n";
        return;
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(23456);

    if (bind(tcpSock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) 
    {
        std::cerr << "Error binding TCP socket\n";
        return;
    }

    if (listen(tcpSock, 1) < 0) 
    {
        std::cerr << "Error listening on TCP socket\n";
        return;
    }

    while (true) 
    {
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        int clientSock = accept(tcpSock, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSock < 0) {
            std::cerr << "Error accepting TCP connection\n";
            break;
        }

        // TCP로 계속 데이터 전송
        while (true) 
        {
            int32_t data = 123; // 보낼 데이터
            int ret = send(clientSock, &data, sizeof(data), 0);
            if (ret < 0) 
            {
                std::cerr << "Error sending data\n";
                break;
            }
            
            // 필요에 따라 sleep 등을 사용하여 전송 간격을 조절할 수 있습니다.
            // sleep(1);
        }

        close(clientSock);
    }

    close(tcpSock);
}

int main() 
{
    std::thread udpThread(udpBroadcast);
    std::thread tcpThread(acceptTcpConnection);

    udpThread.join();
    tcpThread.join();

    return 0;
}
