#ifndef __PacketGenerator__
#define __PacketGenerator__

#include <stdint.h>

class PacketGenerator
{
public:
    PacketGenerator();
    ~PacketGenerator();
    int32_t Generate();
};

#endif
