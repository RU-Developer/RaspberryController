#include <gtest/gtest.h>
#include "Module.h"
#include "Button.h"
#include "JoyStick.h"
#include "ModuleManager.h"
#include "PacketGenerator.h"
#include "Enums.h"
#include "Types.h"
#include "Managers.h"

#include <vector>

// 버튼 모듈 생성시 모듈 타입
TEST(GetModuleTypeTest, GetButtonType) 
{
    Button btn(1);
    EXPECT_EQ(btn.GetModuleType(), ModuleType::Button);
}

// 조준 조이스틱
TEST(GetModuleTypeTest, GetAimingStickType)
{
    JoyStick stick(ModuleType::AimingJoyStick);
    EXPECT_EQ(stick.GetModuleType(), ModuleType::AimingJoyStick);
}

// 움직임 조작 조이스틱
TEST(GetModuleTypeTest, GetMovingStickType)
{
    JoyStick stick(ModuleType::MovingJoyStick);
    EXPECT_EQ(stick.GetModuleType(), ModuleType::MovingJoyStick);
}

// ModuleManager Test
TEST(ModuleManagerTest, CreateAndGet)
{
    ModuleManager modules;
    modules.CreateModule(ModuleType::Button, 1);
    modules.CreateModule(ModuleType::AimingJoyStick);
    modules.CreateModule(ModuleType::MovingJoyStick);

    EXPECT_EQ(modules.GetModules()[0]->GetModuleType(), ModuleType::Button);
    EXPECT_EQ(modules.GetModules()[1]->GetModuleType(), ModuleType::AimingJoyStick);
    EXPECT_EQ(modules.GetModules()[2]->GetModuleType(), ModuleType::MovingJoyStick);
}

// Packet Generate Test
class MockButton : public Button
{
public:
    MockButton(int buttonNumber) : Button(buttonNumber) {}

    virtual void Init() override {}
    virtual int GetInputValue() override { return 1; }
};

class MockJoyStick : public JoyStick
{
public:
    MockJoyStick(ModuleType type) : JoyStick(type) {}

    virtual void Init() override {}
    virtual int GetInputValue() { return 1; }
    Coordinate GetCoordinate() { Coordinate coord; coord.x = 1023; coord.y = 1023; return coord; }
};

class MockModuleManager : public ModuleManager
{
    vector<Module*> vec;

    virtual void Init() override {}

    virtual vector<Module*>& GetModules() override
    {
        vec.push_back(new MockButton(1));
        vec.push_back(new MockButton(2));
        vec.push_back(new MockButton(3));
        vec.push_back(new MockButton(4));
        vec.push_back(new MockButton(5));
        vec.push_back(new MockButton(6));
        vec.push_back(new MockButton(7));
        vec.push_back(new MockJoyStick(ModuleType::AimingJoyStick));
        vec.push_back(new MockJoyStick(ModuleType::MovingJoyStick));

        return vec;
    }

    ~MockModuleManager()
    {
        for (Module* module : vec)
        {
            if (module)
                delete module;
        }
    }
};

class MockManagers : public Managers
{
public:
    void SetModule() 
    { 
        if (Managers::s_module)
            delete Managers::s_module;
        s_module = new MockModuleManager();
    }
};

TEST(PacketGenerateTest, PacketGenerate)
{
    MockManagers mock;
    mock.SetModule();
    ModuleManager* moduleMan = Managers::GetModule();
    PacketGenerator generator;

    int32_t packet = generator.Generate();

    EXPECT_EQ(packet, 0x3FFFFFFF);
}

// Google Test의 main 함수
int main(int argc, char **argv) {
    Managers::Init();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
