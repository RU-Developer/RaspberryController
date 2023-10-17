#ifndef __WirelessController__
#define __WirelessController__

#include <stdint.h>
#include "PacketGenerator.h"

class WirelessController
{
public:
    WirelessController();
    ~WirelessController();
    void SendIfModified();

private:
    int32_t _prevPacket;
    // Packet 생성기 32bit 고정사이즈 패킷
    PacketGenerator _generator;
};

#endif
