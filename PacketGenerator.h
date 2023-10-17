#ifndef __PacketGenerator__
#define __PacketGenerator__

#include <stdint.h>

class PacketGenerator
{
public:
    PacketGenerator();
    ~PacketGenerator();
    // MSB(1) Move(2) AimingX(10) AimingY(10)
    // MovingJoyBtn(1) AimingJoyBtn(1) Btn1 ~ Btn7 (7)
    int32_t Generate();
};

#endif
