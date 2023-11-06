#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "Managers.h"
#include "ModuleManager.h"
#include "WirelessManager.h"
#include "NetworkManager.h"


Managers* Managers::s_instance = new Managers();
ModuleManager* Managers::s_module = nullptr;
WirelessManager* Managers::s_wireless = nullptr;


Managers::Managers()
{

}

Managers::~Managers()
{

}

Managers* Managers::GetInstance()
{
    return s_instance;
}

void Managers::Init()
{
    if (s_module != nullptr)
        return;

    // GPIO SetUp
    wiringPiSetupGpio();
    wiringPiSPISetup(SPI_Channel, SPI_Speed);
    pinMode(GPN_SPIChannel, OUTPUT);

    s_module = new ModuleManager();
    s_module->Init();
    s_wireless = new NetworkManager();
    s_wireless->Init();
}

ModuleManager* Managers::GetModule()
{
    return s_module;
}

// Wireless Communication
WirelessManager* Managers::GetWireless()
{
    return s_wireless;
}

void Managers::Clear()
{

}
