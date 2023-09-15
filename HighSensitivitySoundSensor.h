#include <wiringPi.h>
#include <wiringPiSPI.h> // SPI 통신
#include <iostream> // 표준 입출력

using namespace std; // 편하게 입출력을 위한 네임스페이스

class HighSensitivitySoundSensor
{
private:
	enum GPIO_PIN_NUMBER
	{
		MCP_3008_CS = 8, // MCP_3008 ADC의 CS핀을 GPIO 8번으로 설정
		SPI_CHANNEL = 0, // SPI 채널을 0번으로 설정(MCP_3008의 CH0 ~ 7까지 있음)
	};

	enum SPI
	{
		SPI_SPEED = 1000000 // SPI의 속도를 1MHz로 설정
	};

	enum MCP_3008
	{
		RESOLUTION = 1023 // 0 ~ 1023사이의 값으로 변환함
	};

	void SPIChannelInit()
	{
		_buff[0] = 0x01;
		_buff[1] = (0x08 | _adcChannel) << 4;
		_buff[2] = 0x00;
	}

	void SPIChannelOpen()
	{
		digitalWrite(MCP_3008_CS, LOW); // MCP 3008 ADC의 CS핀을 LOW로 설정하여 통신 시작
	}

public:
	HighSensitivitySoundSensor()
	{
		wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED); // SPI wiringPi라이브러리 SPI 초기화
		pinMode(MCP_3008_CS, OUTPUT); // MCP_3008의 CS핀을 출력 모드로 설정
	}
	
	// MCP 3008 ADC와 SPI 통신을 통해 사운드 센서의 아날로그 값을 읽어오는 함수
	int ReadAnalogSoundValue()
	{
		SPIChannelInit();
		SPIChannelOpen();
		wiringPiSPIDataRW(SPI_CHANNEL, _buff, 3); // SPI 통신을 통해 데이터 전송
		SPIChannelClose();
		int result = ((_buff[1] & 0x03) << 8 | _buff[2]) - 13; // 읽어온 데이터 정수형 변환 13는 거의 기본 소음
		if (result < 0)
			result = 0;

		return result;
	}

	void SPIChannelClose()
	{
		digitalWrite(MCP_3008_CS, HIGH); // MCP 3008 ADC의 CS핀을 HIGH로 설정하여 통신 종료
	}

private:
	const unsigned char _adcChannel = 0;
	unsigned char _buff[3] = {};
};
