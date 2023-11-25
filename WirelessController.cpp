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
    
    // 값이 달라졌으면 전송
    Managers::GetWireless()->Send(data);
    _prevPacket = data;
}
