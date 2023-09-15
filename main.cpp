#include <wiringPi.h>
#include <wiringPiSPI.h> // SPI 통신
#include <iostream> // 표준 입출력
#include "HighSensitivitySoundSensor.h"

using namespace std; // 편하게 입출력을 위한 네임스페이스


int main()
{
	wiringPiSetupGpio(); // GPIO 핀번호로 설정 wiringPi 초기화
	HighSensitivitySoundSensor sensor;

	while (true)
	{
		int analogSound = sensor.ReadAnalogSoundValue();
		cout << "Sound: " << analogSound << endl;

		if (analogSound > 0)
			cout << "[Sound Detected!!!!]" << endl;

		delay(100);
	}

	return 0;
}
