#include <gtest.h>

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::GTEST_FLAG(filter) = "*Tree*";
    return RUN_ALL_TESTS();
}