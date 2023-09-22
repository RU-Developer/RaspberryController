#ifndef __Module__
#define __Module__

#include "Enums.h"

/**
 * 버튼 입력을 받는 모듈들이 상속하게 될 추상 클래스
 */
class Module
{
protected:
    ModuleType _type; // 생성된 모듈들은 모두 모듈을 지정해야 함

public:
    Module(ModuleType type); // 모듈 타입을 넣지 않으면 생성 불가
    virtual ~Module();

    virtual void Init() = 0;
    ModuleType GetModuleType() { return _type; }
    virtual bool GetInputValue() = 0;
};

#endif
