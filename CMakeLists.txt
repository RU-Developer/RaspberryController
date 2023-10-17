cmake_minimum_required(VERSION 3.0.0)
project(RaspberryController VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

# wiringPi 라이브러리를 찾음
find_library(WIRINGPI_LIBRARIES NAMES wiringPi)

# bluetooth 라이브러리를 찾음
# find_library(BLUETOOTH_LIBRARIES NAMES bluetooth)

# 실제 실행 파일 추가
add_executable(RaspberryController main.cpp Module.cpp JoyStick.cpp WirelessManager.cpp NetworkManager.cpp Button.cpp ModuleManager.cpp PacketGenerator.cpp)
# 라이브러리를 링크
# target_link_libraries(RaspberryController ${WIRINGPI_LIBRARIES} ${BLUETOOTH_LIBRARIES} pthread)
target_link_libraries(RaspberryController ${WIRINGPI_LIBRARIES} pthread)

# Google Test 라이브러리를 찾음
find_package(GTest REQUIRED)
# 테스트 실행 파일 추가
add_executable(RaspberryControllerTest test_main.cpp)
# wiringPi와 GoogleTest 라이브러리 + pthread를 링크
# target_link_libraries(RaspberryControllerTest ${WIRINGPI_LIBRARIES} ${GTEST_LIBRARIES} ${BLUETOOTH_LIBRARIES} pthread)
target_link_libraries(RaspberryControllerTest ${WIRINGPI_LIBRARIES} ${GTEST_LIBRARIES} pthread)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
