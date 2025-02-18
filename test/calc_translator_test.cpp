#include <gtest.h>
#include "calc/calc.h"
#include "parser/parser.h"

class calc_test : public ::testing::Test {
protected:
    std::vector<Term> post_str;
    std::vector<double> operands;

    void addOperator(const char& ch) {
        Term a(ch);
        post_str.push_back(a);
    }

    void addOperand(double value) {
        Term a(value);
        post_str.push_back(a);
        operands.push_back(value);
    }

    void SetUp() override {
        post_str.clear();
        operands.clear();
    }
};

TEST_F(calc_test, simple_addition) 
{
    addOperand(3.0);
    addOperand(5.0);
    addOperator('+');

    EXPECT_DOUBLE_EQ(8.0, Calc::Calculate(post_str, operands));
}
TEST_F(calc_test, simple_substraction) 
{
    addOperand(3.0);
    addOperand(5.0);
    addOperator('-');

    EXPECT_DOUBLE_EQ(-2.0, Calc::Calculate(post_str, operands));
}
TEST_F(calc_test, simple_multiplication) 
{
    addOperand(3.0);
    addOperand(5.0);
    addOperator('*');

    EXPECT_DOUBLE_EQ(15.0, Calc::Calculate(post_str, operands));
}
TEST_F(calc_test, simple_division) 
{   
    addOperand(3.0);
    addOperand(5.0);
    addOperator('/');

    EXPECT_DOUBLE_EQ(0.6, Calc::Calculate(post_str, operands));
}
TEST_F(calc_test, can_solve_complex_expression) 
{
    addOperand(2.0);
    addOperand(3.0);
    addOperator('+');
    addOperand(4.0);
    addOperator('*');

    EXPECT_DOUBLE_EQ(20.0, Calc::Calculate(post_str, operands));
}
TEST_F(calc_test, divison_by_zero)
{   
    addOperand(2.0);
    addOperand(0.0);
    addOperator('/');

    EXPECT_DOUBLE_EQ(INFINITY, Calc::Calculate(post_str, operands));
}
TEST_F(calc_test, can_take_integer_type_addition)
{
    addOperand(2);
    addOperand(3);
    addOperator('+');

    EXPECT_EQ(5, Calc::Calculate(post_str, operands));
}
TEST_F(calc_test, can_take_integer_type_substraction)
{
    addOperand(2);
    addOperand(3);
    addOperator('-');

    EXPECT_EQ(-1, Calc::Calculate(post_str, operands));
}
TEST_F(calc_test, can_take_integer_type_multiplication)
{
    addOperand(2);
    addOperand(3);
    addOperator('*');

    EXPECT_EQ(6, Calc::Calculate(post_str, operands));
}
TEST_F(calc_test, can_take_integer_type_division)
{
    addOperand(2);
    addOperand(5);
    addOperator('/');

    EXPECT_EQ(0.4, Calc::Calculate(post_str, operands));
}
TEST_F(calc_test, can_multiply_by_zero)
{
    addOperand(2);
    addOperand(0);
    addOperator('*');

    EXPECT_EQ(0, Calc::Calculate(post_str, operands));
}
