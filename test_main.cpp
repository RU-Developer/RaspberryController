// test_main.cpp
#include <gtest/gtest.h>
//#include "main.cpp" // 테스트할 소스 파일 포함
#include "HighSensitivitySoundSensor.h"

// HighSensitivitySoundSensor 클래스의 ReadAnalogSoundValue 함수를 테스트하는 테스트 케이스
TEST(HighSensitivitySoundSensorTest, ReadAnalogSoundValue) {
    HighSensitivitySoundSensor sensor;
    int value = sensor.ReadAnalogSoundValue();
    // 값이 0 이상이고 1023 이하인지 확인
    ASSERT_GE(value, 0);
    ASSERT_LE(value, 1023);
}

// Google Test의 main 함수
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
