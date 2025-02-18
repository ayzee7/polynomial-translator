#include <gtest.h>
#include "parser/parser.h"

class test_term_analis : public::testing::Test
{
protected:
	std::string input;
	std::vector<Term> output;

    void add_operator(const char& ch)
    {
        Term a(ch);
        output.push_back(a);
    }
    void add_operand(double value)
    {
        Term a(value);
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

TEST_F(test_term_analis, can_pars_simple_addition)
{
	input = "1+2";
	
    add_operand(1);
    add_operator('+');
    add_operand(2);

    EXPECT_EQ(output, Parser::term_analis(input));
}
TEST_F(test_term_analis, can_pars_simple_substraction)
{
    input = "1-2";

    add_operand(1);
    add_operator('-');
    add_operand(2);

    EXPECT_EQ(output, Parser::term_analis(input));
}
TEST_F(test_term_analis, can_pars_simple_multiplication)
{
    input = "1*27";

    add_operand(1);
    add_operator('*');
    add_operand(27);

    EXPECT_EQ(output, Parser::term_analis(input));
}
TEST_F(test_term_analis, can_pars_simple_division)
{
    input = "18/2";

    add_operand(18);
    add_operator('/');
    add_operand(2);

    EXPECT_EQ(output, Parser::term_analis(input));
}
TEST_F(test_term_analis, can_pars_expression_with_brackets)
{
    input = "(1+2)*3";

    add_operator('(');
    add_operand(1);
    add_operator('+');
    add_operand(2);
    add_operator(')');
    add_operator('*');
    add_operand(3);

    EXPECT_EQ(output, Parser::term_analis(input));
}
TEST_F(test_term_analis, can_pars_simple_expression_with_variable)
{
    input = "1+2+a";

    add_operand(1);
    add_operator('+');
    add_operand(2);
    add_operator('+');
    add_operand("a");

    EXPECT_EQ(output, Parser::term_analis(input));
}
TEST_F(test_term_analis, can_pars_expression_with_brackets_and_multi_character_variables)
{
    input = "MyVar*(1+Sec)";

    add_operand("MyVar");
    add_operator('*');
    add_operator('(');
    add_operand(1);
    add_operator('+');
    add_operand("Sec");
    add_operator(')');

    EXPECT_EQ(output, Parser::term_analis(input));
}
TEST_F(test_term_analis, can_pars_expression_with_the_equal_sign)
{
    input = "a=3+4";

    add_operand("a");
    add_operator('=');
    add_operand(3);
    add_operator('+');
    add_operand(4);

    EXPECT_EQ(output, Parser::term_analis(input));
}
TEST_F(test_term_analis, can_pars_expression_with_the_equal_sign_and_few_variables)
{
    input = "c=a+b";

    add_operand("c");
    add_operator('=');
    add_operand("a");
    add_operator('+');
    add_operand("b");

    EXPECT_EQ(output, Parser::term_analis(input));
}
TEST_F(test_term_analis, can_pars_expression_with_the_equal_sign_and_brackets)
{
    input = "a=(3+1)*b";

    add_operand("a");
    add_operator('=');
    add_operator('(');
    add_operand(3);
    add_operator('+');
    add_operand(1);
    add_operator(')');
    add_operator('*');
    add_operand("b");

    EXPECT_EQ(output, Parser::term_analis(input));
}

TEST_F(test_term_analis, can_pars_constant_pi)
{
    input = "pi+PI+Pi";

    add_operand(3.14159265359);
    add_operator('+');
    add_operand(3.14159265359);
    add_operator('+');
    add_operand(3.14159265359);

    EXPECT_EQ(output, Parser::term_analis(input));
}
TEST_F(test_term_analis, can_pars_constant_e)
{
    input = "e";

    add_operand(2.71828182846);

    EXPECT_EQ(output, Parser::term_analis(input));
}