#ifndef __Enums__
#define __Enums__

enum ModuleMetaData
{
    MMD_ButtonMaxNumber = 7
};

enum GPIO_PIN_NUMBER
{
    GPN_SPIChannel = 8, // MCP_3008 ADC의 CS핀을 GPIO 8번으로 설정
    GPN_SPIClock = 11, // 클락 펄스
    GPN_SPIDataInput = 9, // MCP_3008 ADC의 Data out
    GPN_SPIDataOutput = 10, // MCP_3008 ADC의 Data in
    
    GPN_MovingButton = 5, // 움직임 조작 조이스틱의 버튼
    GPN_AimingButton = 6, // 조준 조작 조이스틱의 버튼

    GPN_Button1 = 17, // 버튼 1번
    GPN_Button2 = 27, // 버튼 2번
    GPN_Button3 = 16, // 버튼 3번
    GPN_Button4 = 20, // 버튼 4번
    GPN_Button5 = 22, // 버튼 5번
    GPN_Button6 = 27, // 버튼 6번
    GPN_Button7 = 27, // 버튼 7번
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

// Bit Shift 연산을 위한 정보
enum BitMaskLayer
{
    BML_Button7 = 0,
    BML_Button6 = 1,
    BML_Button5 = 2,
    BML_Button4 = 3,
    BML_Button3 = 4,
    BML_Button2 = 5,
    BML_Button1 = 6,

    BML_AimingStickButton = 7,
    BML_MovingStickButton = 8,

    BML_JoyStickPosY = 9,
    BML_JoyStickPosX = 19,

    BML_Move = 29
};

enum BitFlag
{
    BF_Button7 = 0x00000001,
    BF_Button6 = 0x00000002,
    BF_Button5 = 0x00000004,
    BF_Button4 = 0x00000008,
    BF_Button3 = 0x00000010,
    BF_Button2 = 0x00000020,
    BF_Button1 = 0x00000040,
    
    BF_AimingStickButton = 0x00000080,
    BF_MovingStickButton = 0x00000100,

    BF_JoyStickPosY = 0x0007FE00,
    BF_JoyStickPosX = 0x1FF80000,

    BF_Move = 0x60000000
};

// 500 ~ 550 사이의 값이면 조이스틱을 건드리지 않은 것으로 인식하겠음
enum JoyStickLimit
{
    JSL_SmallLimit = 480,
    JSL_BigLimit = 550,
    JSL_Resolution = 2
};

#endif
