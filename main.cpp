#include <iostream>
#include <stdint.h>

#include "Enums.h"

#include "Managers.h"
#include "WirelessController.h"

using namespace std;

int main() 
{
    Managers::Init();
    WirelessController sender;

    while (true)
        sender.SendIfModified();

    return 0;
}
