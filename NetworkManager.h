#ifndef __NetworkManager__
#define __NetworkManager__

#include <stdint.h>
#include <thread>
#include "WirelessManager.h"

class NetworkManager : public WirelessManager
{
public:
    NetworkManager();
    virtual ~NetworkManager();
    virtual void Init() override;
    virtual void Send(int32_t data) override;

private:
    int _udpSock;
    int _tcpSock;
    int _clientSock;
    std::thread* _udpThread;
    std::thread* _tcpThread;
    void StartClientFinder();
    void StartClientAccepter();
};

#endif
