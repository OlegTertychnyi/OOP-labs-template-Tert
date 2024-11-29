#include <gtest/gtest.h>
#include "../include/execute.h"

TEST(test_01, basic_test_set)
{
    ASSERT_TRUE(isAfraid("Понедельник",12)==true);
}

TEST(test_02, basic_test_set)
{
    ASSERT_TRUE(isAfraid("Вторник",100)==true);
}

TEST(test_03, basic_test_set)
{
    ASSERT_TRUE(isAfraid("Четверг",20)==false);
}

TEST(test_04, basic_test_set)
{
    ASSERT_TRUE(isAfraid("Cуббота",-70)==false);
}

TEST(test_05, basic_test_set)
{
    ASSERT_TRUE(isAfraid("Воскресенье",-666)==true);
}

TEST(test_07, basic_test_set)
{
    ASSERT_TRUE(isAfraid("Понедельни",20)==false);
}
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
