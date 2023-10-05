#ifndef __Enums__
#define __Enums__

enum GPIO_PIN_NUMBER
{
    GPN_SPIChannel = 8, // MCP_3008 ADC의 CS핀을 GPIO 8번으로 설정
    GPN_SPIClock = 11, // 클락 펄스
    GPN_SPIDataInput = 9, // MCP_3008 ADC의 Data out
    GPN_SPIDataOutput = 10, // MCP_3008 ADC의 Data in
    GPN_MovingButton = 5, // 움직임 조작 조이스틱의 버튼
    GPN_AimingButton = 6, // 조준 조작 조이스틱의 버튼
};

enum SPI
{
    SPI_Channel = 0, // SPI 채널을 0번으로 설정
    SPI_Speed = 1000000, // SPI의 속도를 1MHz로 설정
    SPI_MovingX = 0,
    SPI_MovingY = 1,
    SPI_AimingX = 2,
    SPI_AimingY = 3,
};

enum MCP_3008
{
    MCP_Resolution = 1023 // 0 ~ 1023사이의 값으로 변환함
};

enum class ModuleType
{
    MovingJoyStick,
    AimingJoyStick,
    Button
};


#endif
