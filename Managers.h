#ifndef __Managers__
#define __Managers__

class ModuleManager;
class WirelessManager;

class Managers
{
public:
    ~Managers();
    static Managers* GetInstance();
    static void Init();
    static ModuleManager* GetModule();
    static WirelessManager* GetWireless();
    void Clear();

protected:
    Managers();
    static Managers* s_instance;
    static ModuleManager* s_module;
    static WirelessManager* s_wireless;
};

#endif
