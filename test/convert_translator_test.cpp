#include <gtest.h>
#include "converter/converter.h"
#include "parser/parser.h"

class converter_test : public::testing::Test
{
protected:
	std::vector<Term> input;
    std::vector<Term> output;
	std::vector<double> operands;
	std::map<std::string, double> values;

    void add_operator(const char& ch,std::vector<Term>& v) 
    {
        Term a(ch);
        v.push_back(a);
    }
    void add_operand(double value,std::vector<Term>& v) 
    {
        Term a(value);
        v.push_back(a);
    }
    void add_operand(const std::string& variable,std::vector<Term>& v)
    {
        Term a(variable);
        v.push_back(a);
    }
    void add_variable(const std::string& name, double value)
    {
        std::pair<std::string, double> a;
        a.first = name;
        a.second = value;
        values.insert(a);
    }
    void SetUp() override {
        input.clear();
        operands.clear();
        values.clear();
    }
};

TEST_F(converter_test, can_convert_simple_addition)
{
    add_operand(1,input);
    add_operator('+', input);
    add_operand(3,input);
    
    add_operand(1, output);
    add_operand(3, output);
    add_operator('+',output);

    EXPECT_EQ(output, Converter::conv(input, operands, values));
}
TEST_F(converter_test, can_convert_simple_substraction)
{
    add_operand(1, input);
    add_operator('-', input);
    add_operand(3, input);

    add_operand(1, output);
    add_operand(3, output);
    add_operator('-', output);

    EXPECT_EQ(output, Converter::conv(input, operands, values));
}
TEST_F(converter_test, can_convert_simple_multipliaction)
{
    add_operand(1, input);
    add_operator('*', input);
    add_operand(3, input);

    add_operand(1, output);
    add_operand(3, output);
    add_operator('*', output);

    EXPECT_EQ(output, Converter::conv(input, operands, values));
}
TEST_F(converter_test, can_convert_simple_division)
{
    add_operand(1, input);
    add_operator('/', input);
    add_operand(3, input);

    add_operand(1, output);
    add_operand(3, output);
    add_operator('/', output);

    EXPECT_EQ(output, Converter::conv(input, operands, values));
}
TEST_F(converter_test, can_correctly_determine_prio_of_operations)
{
    add_operand(1, input);
    add_operator('-', input);
    add_operand(3, input);
    add_operator('*', input);
    add_operand(3, input);

    add_operand(1, output);
    add_operand(3, output);
    add_operand(3, output);
    add_operator('*', output);
    add_operator('-', output);

    EXPECT_EQ(output, Converter::conv(input, operands, values));
}
TEST_F(converter_test, can_correctly_determine_prio_of_operations_with_brackets)
{
    add_operator('(', input);
    add_operand(1, input);
    add_operator('-', input);
    add_operand(3, input);
    add_operator(')', input);
    add_operator('*', input);
    add_operand(3, input);

    add_operand(1, output);
    add_operand(3, output);
    add_operator('-', output);
    add_operand(3, output);
    add_operator('*', output);

    EXPECT_EQ(output, Converter::conv(input, operands, values));
}
TEST_F(converter_test, can_convert_simple_addition_with_variable)
{
    add_variable("a", 10);

    add_operand("a", input);
    add_operator('+', input);
    add_operand(3, input);

    add_operand(10, output);
    add_operand(3, output);
    add_operator('+', output);

    EXPECT_EQ(output, Converter::conv(input, operands, values));
}
TEST_F(converter_test, can_convert_simple_substraction_with_variable)
{
    add_variable("a", 10);

    add_operand("a", input);
    add_operator('-', input);
    add_operand(3, input);

    add_operand(10, output);
    add_operand(3, output);
    add_operator('-', output);

    EXPECT_EQ(output, Converter::conv(input, operands, values));
}
TEST_F(converter_test, can_convert_simple_multiplication_with_variable)
{
    add_variable("a", 10);

    add_operand("a", input);
    add_operator('*', input);
    add_operand(3, input);

    add_operand(10, output);
    add_operand(3, output);
    add_operator('*', output);

    EXPECT_EQ(output, Converter::conv(input, operands, values));
}
TEST_F(converter_test, can_convert_simple_division_with_variable)
{
    add_variable("a", 10);

    add_operand("a", input);
    add_operator('/', input);
    add_operand(3, input);

    add_operand(10, output);
    add_operand(3, output);
    add_operator('/', output);

    EXPECT_EQ(output, Converter::conv(input, operands, values));
}
TEST_F(converter_test, empty_return_if_variable_is_not_existing)
{
    add_operand("a", input);
    add_operator('*', input);
    add_operand(3, input);

    EXPECT_TRUE(Converter::conv(input, operands, values).empty());
}
TEST_F(converter_test, can_correctly_determine_prio_of_operations_with_variable)
{
    add_variable("a", 10);

    add_operand(3, input);
    add_operator('*', input);
    add_operand("a", input);
    add_operator('+', input);
    add_operand(1, input);
    
    add_operand(3, output);
    add_operand(10, output);
    add_operator('*', output);
    add_operand(1, output);
    add_operator('+', output);

    EXPECT_EQ(output, Converter::conv(input, operands, values));
}
TEST_F(converter_test, can_correctly_determine_prio_of_operations_with_variable_and_brackets)
{
    add_variable("a", 10);

    add_operand(3, input);
    add_operator('*', input);
    add_operator('(', input);
    add_operand("a", input);
    add_operator('+', input);
    add_operand(1, input);
    add_operator(')', input);

    add_operand(3, output);
    add_operand(10, output);
    add_operand(1, output);
    add_operator('+', output);
    add_operator('*', output);

    EXPECT_EQ(output, Converter::conv(input, operands, values));
}
TEST_F(converter_test, can_covert_simple_operation_with_two_variables)
{
    add_variable("a", 10);
    add_variable("b", 14);

    add_operand("a", input);
    add_operator('+', input);
    add_operand("b", input);

    add_operand(10, output);
    add_operand(14, output);
    add_operator('+', output);

    EXPECT_EQ(output, Converter::conv(input, operands, values));
}
