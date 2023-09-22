#include <gtest/gtest.h>

// Google Test의 main 함수
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
