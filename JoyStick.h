#ifndef __JoyStick__
#define __JoyStick__

#include <stdint.h>

#include "Types.h"
#include "Enums.h"
#include "Module.h"

/**
 * JoyStick을 입력받기 위한 클래스
 */
class JoyStick : public Module
{
protected:
    unsigned char _buttonPinNumber; // 버튼 GPIO 핀번호
    unsigned char _channelX; // x좌표 통신 SPI 채널 번호
    unsigned char _channelY; // y좌표 통신 SPI 채널 번호
    unsigned char _bufferX[3] = {}; // x좌표 통신 버퍼
    unsigned char _bufferY[3] = {}; // y좌표 통신 버퍼

public:
    JoyStick(ModuleType type);
    virtual ~JoyStick();

    virtual void Init() override; // 조이스틱 타입에 따라 핀 설정
    virtual bool GetInputValue() override; // 버튼 입력 반환

protected:
    void SPIChannelInit(); // 버퍼 초기화
    void SPIChannelOpen(); // 통신 시작
    void SPIChannelClose(); // 통신 종료

public:
    Coordinate GetCoordinate(); // 조이스틱 x, y좌표 반환
};

#endif
