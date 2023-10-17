#ifndef __ModuleManager__
#define __ModuleManager__
#include <vector>
#include "Enums.h"

using namespace std;

class Module;

class ModuleManager
{
public:
    ~ModuleManager();
    void Init();
    vector<Module*>& GetModules();
    // 0번은 없음 조이스틱은 번호가 필요없음 따라서 그냥 0번 배정
    void CreateModule(ModuleType type, int buttonNumber = 0);

private:
    ModuleManager();

public:
    static ModuleManager* GetInstance()
    {
        static ModuleManager instance;
        return &instance;
    }

private:
    vector<Module*> _modules;
};

#endif
