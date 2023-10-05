#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "Types.h"
#include "Enums.h"
#include "JoyStick.h"

JoyStick::JoyStick(ModuleType type) : Module(type)
{
    
}

JoyStick::~JoyStick()
{

}

void JoyStick::Init()
{
    switch (_type)
    {
    case ModuleType::MovingJoyStick:
        _buttonPinNumber = static_cast<unsigned char>(GPN_MovingButton);
        _channelX = static_cast<unsigned char>(SPI_MovingX);
        _channelY = static_cast<unsigned char>(SPI_MovingY);
        break;
    case ModuleType::AimingJoyStick:
        _buttonPinNumber = static_cast<unsigned char>(GPN_AimingButton);
        _channelX = static_cast<unsigned char>(SPI_AimingX);
        _channelY = static_cast<unsigned char>(SPI_AimingY);
        break;
    }

    pinMode(_buttonPinNumber, INPUT);
}

int JoyStick::GetInputValue()
{
    // 반대 값이 버튼의 눌림 유무
    return !static_cast<bool>(digitalRead(_buttonPinNumber));
}

void JoyStick::SPIChannelInit()
{
    _bufferX[0] = 0x01;
    _bufferX[1] = (0x08 | _channelX) << 4;
    _bufferX[2] = 0x00;

    _bufferY[0] = 0x01;
    _bufferY[1] = (0x08 | _channelY) << 4;
    _bufferY[2] = 0x00;
}

void JoyStick::SPIChannelOpen()
{
    // MCP 3008 ADC의 CS핀을 LOW로 설정하여 통신 시작
    digitalWrite(GPN_SPIChannel, LOW); 
}

void JoyStick::SPIChannelClose()
{
    // MCP 3008 ADC의 CS핀을 HIGH로 설정하여 통신 종료
    digitalWrite(GPN_SPIChannel, HIGH); 
}

Coordinate JoyStick::GetCoordinate()
{
    Coordinate coord;
    SPIChannelInit();
    SPIChannelOpen();   
    // SPI 통신을 통해 데이터 전송
    wiringPiSPIDataRW(SPI_Channel, _bufferX, 3);
    wiringPiSPIDataRW(SPI_Channel, _bufferY, 3);
    SPIChannelClose();
    coord.x = (_bufferX[1] & 0x03) << 8 | _bufferX[2];
    coord.y = (_bufferY[1] & 0x03) << 8 | _bufferY[2];

    return coord;
}
