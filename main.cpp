#include <wiringPi.h>
#include <wiringPiSPI.h> // SPI 통신
#include <iostream> // 표준 입출력
#include <stdint.h>

#include "Enums.h"
#include "Types.h"
#include "JoyStick.h"

using namespace std; // 편하게 입출력을 위한 네임스페이스

int main()
{
	wiringPiSetupGpio(); // GPIO 핀번호로 설정 wiringPi 초기화
	wiringPiSPISetup(SPI_Channel, SPI_Speed); // SPI wiringPi라이브러리 SPI 초기화
	pinMode(GPN_SPIChannel, OUTPUT); // MCP_3008의 CS핀을 출력 모드로 설정

	JoyStick stick(ModuleType::MovingJoyStick);
	stick.Init();
	
	while (true)
	{
		bool buttonInput = stick.GetInputValue();
		Coordinate coord = stick.GetCoordinate();

		cout << "button pressed: " << (buttonInput ? "true" : "false")
			<< ", x좌표: " << coord.x
			<< ", y좌표: " << coord.y << endl;

		delay(100);
	}

	return 0;
}
