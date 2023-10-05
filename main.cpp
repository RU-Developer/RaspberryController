#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <iostream>
#include <stdint.h>

#include "Enums.h"
#include "Types.h"
#include "WirelessManager.h"
#include "NetworkManager.h"
#include "Module.h"
#include "JoyStick.h"

using namespace std;

int main() 
{
    wiringPiSetupGpio();
    wiringPiSPISetup(SPI_Channel, SPI_Speed);
    pinMode(GPN_SPIChannel, OUTPUT);

    int32_t data = 100;
    JoyStick stick(ModuleType::MovingJoyStick);
    stick.Init();

    WirelessManager* manager = new NetworkManager();
    manager->Init();

    while (true)
    {
        data = stick.GetCoordinate().x;
        manager->Send(data);
        delay(100);
    }

    return 0;
}
