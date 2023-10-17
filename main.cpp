#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <iostream>
#include <stdint.h>

#include "Enums.h"
#include "Types.h"

#include "WirelessManager.h"
#include "NetworkManager.h"
#include "PacketGenerator.h"

using namespace std;

int main() 
{
    // GPIO SetUp
    wiringPiSetupGpio();
    wiringPiSPISetup(SPI_Channel, SPI_Speed);
    pinMode(GPN_SPIChannel, OUTPUT);

    // MSB(1) Move(2) AimingX(10) AimingY(10)
    // MovingJoyBtn(1) AimingJoyBtn(1) Btn1 ~ Btn7 (7)
    int32_t data = 0;
    int32_t prev = 0;

    // Wireless Communication
    WirelessManager* manager = new NetworkManager();
    manager->Init();

    // Packet 생성기 32bit 고정사이즈 패킷
    PacketGenerator generator;

    while (true)
    { 
        data = generator.Generate();

        // 데이터 전송
        // 이전과 데이터가 달라야만 전송.
        if (prev != data)
        {
            manager->Send(data);
            prev = data;
        }
    }

    return 0;
}
