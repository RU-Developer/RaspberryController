#include "WirelessController.h"
#include "Managers.h"
#include "WirelessManager.h"
#include "Enums.h"

WirelessController::WirelessController()
{
    
}

WirelessController::~WirelessController()
{

}

void WirelessController::SendIfModified()
{
    int32_t data = _generator.Generate();

    // 데이터 전송
    // 이전과 데이터가 달라야만 전송.
    if (_prevPacket == data)
        return;

    // 이전과 약간 달라졌어도 약간의 차이만 나는 조이스틱 값이면 전송 안함
    int32_t xorData = data ^ _prevPacket;
    // 조이스틱 제외한 좌표가 다 같으면
    if ((xorData & ~(BF_JoyStickPosX | BF_JoyStickPosY)) == 0)
    {
        // 조이스틱 좌표 변화가 거의 없다면
        int32_t xDiff = ((data & BF_JoyStickPosX) >> BML_JoyStickPosX)
                        - ((_prevPacket & BF_JoyStickPosX) >> BML_JoyStickPosX);
        int32_t yDiff = ((data & BF_JoyStickPosY) >> BML_JoyStickPosY)
                        - ((_prevPacket & BF_JoyStickPosY) >> BML_JoyStickPosY);

        if (xDiff < JSL_Resolution && yDiff < JSL_Resolution)
            return;
    }
    
    // 값이 달라졌으면 전송
    Managers::GetWireless()->Send(data);
    _prevPacket = data;
}
