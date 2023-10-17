#include <stdint.h>
#include <vector>

#include "Enums.h"
#include "PacketGenerator.h"
#include "Managers.h"
#include "ModuleManager.h"
#include "Module.h"
#include "JoyStick.h"
#include "Button.h"

PacketGenerator::PacketGenerator()
{

}

PacketGenerator::~PacketGenerator()
{

}

// MSB(1) Move(2) AimingX(10) AimingY(10)
// MovingJoyBtn(1) AimingJoyBtn(1) Btn1 ~ Btn7 (7)
int32_t PacketGenerator::Generate()
{
    ModuleManager* moduleMgr = Managers::GetModule();
    vector<Module*>& modules = moduleMgr->GetModules();

    int32_t data = 0;
    Coordinate movingStickCoordinate;
    Coordinate aimingStickCoordinate;

    for (Module* module : modules)
    {
        switch (module->GetModuleType())
        {
        case ModuleType::AimingJoyStick:
        {
            JoyStick* aimingStick = static_cast<JoyStick*>(module);
            aimingStickCoordinate = aimingStick->GetCoordinate();
            int buttonValue = aimingStick->GetInputValue();
            data |= (buttonValue << BML_AimingStickButton);
            break;
        }
        case ModuleType::MovingJoyStick:
        {
            JoyStick* movingStick = static_cast<JoyStick*>(module);
            movingStickCoordinate = movingStick->GetCoordinate();
            int buttonValue = movingStick->GetInputValue();
            data |= (buttonValue << BML_MovingStickButton);

            // 움직임 값: 00: 왼쪽, 01: 오른쪽, 10: 움직이지 않음
            if (movingStickCoordinate.x >= JSL_SmallLimit && movingStickCoordinate.x <= JSL_BigLimit)
                data |= (0b10 << BML_Move);
            else if (movingStickCoordinate.x < JSL_SmallLimit)
                data |= (0b00 << BML_Move);
            else
                data |= (0b01 << BML_Move);

            break;
        }
        case ModuleType::Button:
        {
            Button* button = static_cast<Button*>(module);
            int buttonValue = button->GetInputValue();
            int buttonNumber = button->GetButtonNumber();
            data |= (buttonValue << (MMD_ButtonMaxNumber - buttonNumber));
            break;
        }
        }
    }

    // 조준 조이스틱을 움직였으면 조준 조이스틱으로 조준.
    if ((aimingStickCoordinate.x > JSL_BigLimit || aimingStickCoordinate.x < JSL_SmallLimit) &&
            (aimingStickCoordinate.y > JSL_BigLimit || aimingStickCoordinate.y < JSL_SmallLimit))
    {
        data |= (aimingStickCoordinate.x << BML_JoyStickPosX);
        data |= (aimingStickCoordinate.y << BML_JoyStickPosY);
    }
    // 아니라면 무빙 스틱으로 조준
    else
    {
        data |= (movingStickCoordinate.x << BML_JoyStickPosX);
        data |= (movingStickCoordinate.y << BML_JoyStickPosY);
    }

    return data;
}
