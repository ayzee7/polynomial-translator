#include <gtest.h>

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    //::testing::GTEST_FLAG(filter) = "*TranslatorTest*";
    return RUN_ALL_TESTS();
}