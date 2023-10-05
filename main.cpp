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
    // GPIO SetUp
    wiringPiSetupGpio();
    wiringPiSPISetup(SPI_Channel, SPI_Speed);
    pinMode(GPN_SPIChannel, OUTPUT);

    // MSB(1) Move(2) AimingX(10) AimingY(10)
    // MovingJoyBtn(1) AimingJoyBtn(1) Btn1 ~ Btn7 (7)
    int32_t data = 0;

    int32_t prev = 0;

    // Moving Stick
    JoyStick movingStick(ModuleType::MovingJoyStick);
    movingStick.Init();
    
    // Aiming Stick
    JoyStick aimingStick(ModuleType::AimingJoyStick);
    aimingStick.Init();

    // Wireless Communication
    WirelessManager* manager = new NetworkManager();
    manager->Init();

    while (true)
    { 
        data = 0;
        Coordinate movingStickCoordinate = movingStick.GetCoordinate();
        Coordinate aimingStickCoordinate = aimingStick.GetCoordinate();
        // 500 ~ 550 사이의 값이면 조이스틱을 건드리지 않은 것으로 인식하겠음
        // 움직임 값: 00: 왼쪽, 01: 오른쪽, 10: 움직이지 않음
        if (movingStickCoordinate.x >= 500 && movingStickCoordinate.x <= 550)
            data |= (0b10 << 29); // 왼쪽에서 2번째 부터 3번째까지 오른쪽에서 30번째까지
        else if (movingStickCoordinate.x < 500)
        {
            data |= (0b00 << 29); // 왼쪽에서 2번째 부터 3번째까지 오른쪽에서 30번째까지
        }
        else
        {
            data |= (0b01 << 29); // 왼쪽에서 2번째 부터 3번째까지 오른쪽에서 30번째까지
        }

        // 조준 조이스틱을 움직였으면 조준 조이스틱으로 조준.
        if ((aimingStickCoordinate.x > 550 || aimingStickCoordinate.x < 500) &&
                (aimingStickCoordinate.y > 550 || aimingStickCoordinate.y < 500))
        {
            data |= (aimingStickCoordinate.x << 19); // 왼쪽에서 4번째부터 13번째까지 오른쪽에서 20번째까지
            data |= (aimingStickCoordinate.y << 9); // 왼쪽에서 14번째부터 23번째까지 오른쪽에서 10번째까지
        }
        // 아니라면 무빙 스틱으로 조준
        else
        {
            data |= (movingStickCoordinate.x << 19); // 왼쪽에서 4번째부터 13번째까지 오른쪽에서 20번째까지
            data |= (movingStickCoordinate.y << 9); // 왼쪽에서 14번째부터 23번째까지 오른쪽에서 10번째까지
        }

        // 조이스틱 버튼 값
        data |= (movingStick.GetInputValue() << 8); // 왼쪽에서 24번째 오른쪽에서 9번째
        data |= (aimingStick.GetInputValue() << 7); // 왼쪽에서 25번째 오른쪽에서 8번째

        // 일반 버튼 값 1 ~ 7


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
