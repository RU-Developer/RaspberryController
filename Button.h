#ifndef __Button__
#define __Button__

#include "Module.h"

class Button : public Module
{
public:
    Button(int buttonNumber);
    virtual ~Button();

    virtual void Init() override;
    virtual int GetInputValue() override;

private:
    unsigned char _buttonPinNumber;
    int _buttonNumber;
};


#endif
