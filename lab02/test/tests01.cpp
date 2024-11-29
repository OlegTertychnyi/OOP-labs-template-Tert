#include <gtest/gtest.h>
#include "../include/seven.h"


TEST(SevenTest, DefaultConstructor) {
    Seven s;
    EXPECT_EQ(s.get_size(), 0);
}

TEST(SevenTest, ParametrizedConstructor) {
    Seven s(5, '3');
    EXPECT_EQ(s.get_size(), 5);
    for (int i = 0; i < s.get_size(); ++i) {
        EXPECT_EQ(s.get_digits()[i], '3');
    }
}

TEST(SevenTest, StringConstructor) {
    Seven s("355");
    EXPECT_EQ(s.get_size(), 3);
    EXPECT_EQ(s.get_digits()[0], '3');
    EXPECT_EQ(s.get_digits()[1], '5');
    EXPECT_EQ(s.get_digits()[2], '5');
}

TEST(SevenTest, LargeStringConstructor) {
    Seven s("64425");
    EXPECT_EQ(s.get_size(), 5); 
    EXPECT_EQ(s.get_digits()[0], '6');
    EXPECT_EQ(s.get_digits()[1], '4');
    EXPECT_EQ(s.get_digits()[2], '4');
    EXPECT_EQ(s.get_digits()[3], '2');
    EXPECT_EQ(s.get_digits()[4], '5');
}

TEST(SevenTest, InitializerConstructor_01) {
    Seven s({'1', '2'});
    EXPECT_EQ(s.get_size(), 2);
    EXPECT_EQ(s.get_digits()[0], '1');
    EXPECT_EQ(s.get_digits()[1], '2');
}

TEST(SevenTest, InitializerConstructor_02) {
    Seven s({'0', '0'});
    EXPECT_EQ(s.get_size(), 1);
    EXPECT_EQ(s.get_digits()[0], '0');
}

TEST(SevenTest, InvalidStringConstructor) {
    EXPECT_THROW(Seven s("76425"), std::invalid_argument); 
}

TEST(SevenTest, InvalidParametrizedConstructor) {
    EXPECT_THROW(Seven s(3, '7'), std::invalid_argument); 
}

TEST(SevenTest, NormalizationTest) {
    Seven s("0001433");
    EXPECT_EQ(s.get_size(), 4);  
    EXPECT_EQ(s.get_digits()[0], '1');
    EXPECT_EQ(s.get_digits()[1], '4');
    EXPECT_EQ(s.get_digits()[2], '3');
    EXPECT_EQ(s.get_digits()[3], '3');
}

TEST(SevenTest, LargeNumberNormalization) {
    Seven s("0006");
    EXPECT_EQ(s.get_size(), 1);  
    EXPECT_EQ(s.get_digits()[0], '6');
}

TEST(SevenTest, CopyConstructor) {
    Seven s1("32561");
    Seven s2(s1);
    EXPECT_EQ(s2.get_size(), 5); 
    EXPECT_EQ(s2.get_digits()[0], '3'); 
    EXPECT_EQ(s2.get_digits()[1], '2');
    EXPECT_EQ(s2.get_digits()[2], '5');
    EXPECT_EQ(s2.get_digits()[3], '6');
    EXPECT_EQ(s2.get_digits()[4], '1');

}

TEST(SevenTest, CopyConstructorLargeNumber) {
    Seven s1("22");
    Seven s2(s1); 
    EXPECT_EQ(s2.get_size(), 2); 
    EXPECT_EQ(s2.get_digits()[0], '2');
    EXPECT_EQ(s2.get_digits()[1], '2');
}

TEST(SevenTest, AdditionOperator) {
    Seven s1("1433");
    Seven s2("0");
    Seven result = s1 + s2;  
    EXPECT_EQ(result.get_size(), 4);  
    EXPECT_EQ(result.get_digits()[0], '1');
    EXPECT_EQ(result.get_digits()[1], '4');
    EXPECT_EQ(result.get_digits()[2], '3');
    EXPECT_EQ(result.get_digits()[3], '3');
}

TEST(SevenTest, AdditionOperatorLargeNumbers) {
    Seven s1("512");
    Seven s2("512");
    Seven result = s1 + s2;  
    EXPECT_EQ(result.get_size(), 4);
    EXPECT_EQ(result.get_digits()[0], '1');
    EXPECT_EQ(result.get_digits()[1], '3');
    EXPECT_EQ(result.get_digits()[2], '2');
    EXPECT_EQ(result.get_digits()[3], '4');
}

TEST(SevenTest, SubtractionOperator) {
    Seven s1("64425");
    Seven s2("2315");
    Seven result = s1 - s2;  
    EXPECT_EQ(result.get_size(), 5);
    EXPECT_EQ(result.get_digits()[0], '6');
    EXPECT_EQ(result.get_digits()[1], '2');
    EXPECT_EQ(result.get_digits()[2], '1');
    EXPECT_EQ(result.get_digits()[3], '1');
    EXPECT_EQ(result.get_digits()[4], '0');
}

TEST(SevenTest, SubtractionOperatorDifferentNumbers_01) {
    Seven s1("1431");
    Seven s2("512");
    Seven result = s1 - s2;  
    EXPECT_EQ(result.get_size(), 3);
    EXPECT_EQ(result.get_digits()[0], '6');
    EXPECT_EQ(result.get_digits()[1], '1');
    EXPECT_EQ(result.get_digits()[2], '6');
}

TEST(SevenTest, SubtractionOperatorDifferentNumbers_02) {
    Seven s1("512");
    Seven s2("512");
    Seven result = s1 - s2;  
    EXPECT_EQ(result.get_size(), 1);
    EXPECT_EQ(result.get_digits()[0], '0');
}

TEST(SevenTest, GreaterThenOtherNumber_01){
    Seven s1({'1', '4', '3', '1'});
    Seven s2({'1'});
    EXPECT_TRUE(s1 > s2);
    EXPECT_FALSE(s2 > s1);
}

TEST(SevenTest, GreaterThenOtherNumber_02){
    Seven s1("2000");
    Seven s2("2000");
    EXPECT_FALSE(s1 > s2);
    EXPECT_FALSE(s2 > s1);
}

TEST(SevenTest, LessThenOtherNumber_01){
    Seven s1({'1', '4', '3', '1'});
    Seven s2({'1'});
    EXPECT_TRUE(s2 < s1);
    EXPECT_FALSE(s1 < s2);
}

TEST(SevenTest, LessThenOtherNumber_02){
    Seven s1("0");
    Seven s2({'1'});
    EXPECT_TRUE(s1 < s2);
    EXPECT_FALSE(s2 < s1);
}

TEST(SevenTest, EqualityOperator) {
    Seven s1("0");
    Seven s2("0");
    Seven s3("66666");
    EXPECT_TRUE(s1 == s2);
    EXPECT_FALSE(s1 == s3); 
}

TEST(SevenTest, EqualityOperatorLargeNumbers) {
    Seven s1("34215");
    Seven s2("34215");
    Seven s3("32100");
    EXPECT_TRUE(s1 == s2);  
    EXPECT_FALSE(s1 == s3);
}

TEST(SevenTest, AssignmentOperator) {
    Seven s1("64425");
    Seven s2 = s1; 
    EXPECT_EQ(s2.get_size(), 5);
    EXPECT_EQ(s2.get_digits()[0], '6');
    EXPECT_EQ(s2.get_digits()[1], '4');
    EXPECT_EQ(s2.get_digits()[2], '4');
    EXPECT_EQ(s2.get_digits()[3], '2');
    EXPECT_EQ(s2.get_digits()[4], '5');
}

TEST(SevenTest, AssignmentOperatorDifferentNumber) {
    Seven s1("3623");
    Seven s2 = s1;  
    EXPECT_EQ(s2.get_size(), 4);
    EXPECT_EQ(s2.get_digits()[0], '3');
    EXPECT_EQ(s2.get_digits()[1], '6');
    EXPECT_EQ(s2.get_digits()[2], '2');
    EXPECT_EQ(s2.get_digits()[3], '3');
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}