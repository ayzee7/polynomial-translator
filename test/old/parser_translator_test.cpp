#include <gtest.h>
#include "parser.h"
#include "polinom.h"

class test_parser : public::testing::Test
{
protected:
	std::string input;
	std::vector<Term> output;

    void add_operator(const char& ch)
    {
        Term a(ch);
        output.push_back(a);
    }
    void add_operand(const coef& k)
    {
        Term a(k);
        output.push_back(a);
    }
    void add_operand(const std::string& variable)
    {
        Term a(variable);
        output.push_back(a);
    }
	void SetUp() override 
	{
		input.clear();
		output.clear();
	}
};

TEST_F(test_parser, cant_pars_empty_expression)
{
    input = "";

    EXPECT_EQ(output, Parser::pars(input)); 
}

TEST_F(test_parser, can_get_monom)
{
    input = "8X^1Y^2Z^3";

    coef k = { 8,1,2,3 };
    add_operand(k);

    EXPECT_EQ(output, Parser::pars(input));
}
TEST_F(test_parser, cant_pars_expression_with_consecutive_operators)
{
    input = "8++X";

    EXPECT_EQ(output, Parser::pars(input));  
}

TEST_F(test_parser, can_pars_monoms_and_operator)
{
    input = "8X^1Y^2Z^3+X^2";

    coef k = { 8,1,2,3 };
    add_operand(k);
    add_operator('+');
    k = { 1,2,0,0 };
    add_operand(k);

    EXPECT_EQ(output, Parser::pars(input));
}
TEST_F(test_parser, can_pars_x_monoms_and_operator)
{
    input = "8X+X^2";

    coef k = { 8,1,0,0 };
    add_operand(k);
    add_operator('+');
    k = { 1,2,0,0 };
    add_operand(k);

    EXPECT_EQ(output, Parser::pars(input));
}
TEST_F(test_parser, can_pars_y_monoms_and_operator)
{
    input = "8Y+Y^2";

    coef k = { 8,0,1,0 };
    add_operand(k);
    add_operator('+');
    k = { 1,0,2,0 };
    add_operand(k);

    EXPECT_EQ(output, Parser::pars(input));
}
TEST_F(test_parser, can_pars_z_monoms_and_operator)
{
    input = "8Z+Z^2";

    coef k = { 8,0,0,1 };
    add_operand(k);
    add_operator('+');
    k = { 1,0,0,2 };
    add_operand(k);

    EXPECT_EQ(output, Parser::pars(input));
}
TEST_F(test_parser, can_pars_expression_with_multiple_operators)
{
    input = "8X+2Y-3Z";

    coef k = { 8, 1, 0, 0 };
    add_operand(k);
    add_operator('+');
    k = { 2, 0, 1, 0 };
    add_operand(k);
    add_operator('-');
    k = { 3, 0, 0, 1 };
    add_operand(k);

    EXPECT_EQ(output, Parser::pars(input));
}

TEST_F(test_parser, can_pars_0_monom)
{
    input = "8";

    coef k = { 8,0,0,0 };
    add_operand(k);
    
    EXPECT_EQ(output, Parser::pars(input));
}
TEST_F(test_parser, can_pars_0_monoms_with_operator)
{
    input = "8+1";
    coef k = { 8,0,0,0 };
    add_operand(k);
    add_operator('+');
    k = { 1,0,0,0 };
    add_operand(k);

    EXPECT_EQ(output, Parser::pars(input));
}
TEST_F(test_parser, cant_pars_expression_wich_end_with_operator)
{
    input = "8+";
    
    EXPECT_EQ(output, Parser::pars(input));
}
TEST_F(test_parser, can_pars_expression_with_operator_eq)
{
    input = "a=8X";

    add_operand("a");
    add_operator('=');
    coef k = { 8,1,0,0 };
    add_operand(k);

    EXPECT_EQ(output, Parser::pars(input));
}
TEST_F(test_parser, cant_pars_expression_wich_ends_with_eq)
{
    input = "a=";

    EXPECT_EQ(output, Parser::pars(input));
}
TEST_F(test_parser, cant_pars_expression_with_value)
{
    input = "a=a+2";

    add_operand("a");
    add_operator('=');
    add_operand("a");
    add_operator('+');
    coef k = { 2,0,0,0 };
    add_operand(k);

    EXPECT_EQ(output, Parser::pars(input));
}
TEST_F(test_parser, can_pars_expression_with_fractional_coefficients)
{
    input = "0.5X^2+0.2Y";

    coef k = { 0.5, 2, 0, 0 };
    add_operand(k);
    add_operator('+');
    k = { 0.2, 0, 1, 0 };
    add_operand(k);

    EXPECT_EQ(output, Parser::pars(input));
}
