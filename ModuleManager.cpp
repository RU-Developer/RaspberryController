#include <vector>
#include <stdint.h>

#include "Enums.h"
#include "ModuleManager.h"
#include "Module.h"
#include "JoyStick.h"
#include "Button.h"

using namespace std;

ModuleManager::ModuleManager()
{
    Init();
}

ModuleManager::~ModuleManager()
{

}

void ModuleManager::Init()
{
    CreateModule(ModuleType::MovingJoyStick);
    CreateModule(ModuleType::AimingJoyStick);
    CreateModule(ModuleType::Button, 1);
    CreateModule(ModuleType::Button, 2);
    CreateModule(ModuleType::Button, 3);
    CreateModule(ModuleType::Button, 4);
    CreateModule(ModuleType::Button, 5);
    CreateModule(ModuleType::Button, 6);
    CreateModule(ModuleType::Button, 7);
}

vector<Module*>& ModuleManager::GetModules()
{
    return _modules;
}

// 0번은 없음 조이스틱은 번호가 필요없음 따라서 그냥 0번 배정
void ModuleManager::CreateModule(ModuleType type, int buttonNumber/*default 0*/)
{
    switch (type)
    {
    case ModuleType::AimingJoyStick:
    {
        JoyStick* stick = new JoyStick(type);
        stick->Init();
        _modules.push_back(stick);
        break;
    }
    case ModuleType::MovingJoyStick:
    {
        JoyStick* stick = new JoyStick(type);
        stick->Init();
        _modules.push_back(stick);
        break;
    }
    case ModuleType::Button:
    {
        Button* btn = new Button(buttonNumber);
        btn->Init();
        _modules.push_back(btn);
        break;
    }
    }
}
