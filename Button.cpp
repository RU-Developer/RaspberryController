#include <wiringPi.h>

#include "Button.h"
#include "Enums.h"
#include "Module.h"

Button::Button(int buttonNumber) : Module(ModuleType::Button)
{
    _buttonNumber = buttonNumber;
}

Button::~Button()
{

}

void Button::Init()
{
    switch (_buttonNumber)
    {
    case 1:
        _buttonPinNumber = GPN_Button1;
        break;
    case 2:
        _buttonPinNumber = GPN_Button2;
        break;
    case 3:
        _buttonPinNumber = GPN_Button3;
        break;
    case 4:
        _buttonPinNumber = GPN_Button4;
        break;
    case 5:
        _buttonPinNumber = GPN_Button5;
        break;
    case 6:
        _buttonPinNumber = GPN_Button6;
        break;
    case 7:
        _buttonPinNumber = GPN_Button7;
        break;
    }

    pinMode(_buttonPinNumber, INPUT);
    pullUpDnControl(_buttonPinNumber, PUD_UP);
}

int Button::GetInputValue()
{
    return !digitalRead(_buttonPinNumber);
}
