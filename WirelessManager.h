#ifndef __WirelessManager__
#define __WirelessManager__

#include <stdint.h>

class WirelessManager
{
public:
    WirelessManager();
    virtual ~WirelessManager();
    virtual void Init() = 0;
    virtual void Send(int32_t data) = 0;
};

#endif
