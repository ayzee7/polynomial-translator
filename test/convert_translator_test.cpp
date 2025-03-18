#include <gtest.h>
#include "converter.h"
#include "parser.h"
#include "polinom.h"

class converter_test : public::testing::Test
{
protected:
	std::vector<Term> input;
    std::vector<Term::Type> output;
	std::vector<Polynom> operands;
    std::vector<std::string> operators;
	std::map<std::string, Polynom> values;

    std::vector<Polynom> operands_out;
    std::vector<std::string> operators_out;

    void add_operator_inp(const char& ch)
    {
        Term a(ch);
        input.push_back(a);
    }
    void add_operand_inp(const coef& value)
    {
        Term a(value);
        input.push_back(a);
    }
    void add_operand_inp(const std::string& variable)
    {
        Term a(variable);
        input.push_back(a);
    }
    void add_operator_out(const std::string& ch) 
    {
        output.push_back(Term::Type::OPERATOR);
        operators.push_back(ch);
    }
    void add_operand_out(const coef& k) 
    {
        output.push_back(Term::Type::MONOM);
        Monom m(k.k, k.x, k.y, k.z);
        Polynom pol(m);
        operands.push_back(pol);
    }
    void add_operand_out(const std::string& variable)
    {
        output.push_back(Term::Type::MONOM);
        operands.push_back(values[variable]);
    }
    void add_variable(const std::string& name, const Polynom& value)
    {
        std::pair<std::string, Polynom> a;
        a.first = name;
        a.second = value;
        values.insert(a);
    }
    void SetUp() override {
        input.clear();
        operands.clear();
        operators.clear();
        values.clear();
        operators_out.clear();
        operands_out.clear();
    }
};


TEST_F(converter_test, can_convert_simple_addition)
{
    coef k1 = { 1,2,2,2 };
    coef k2 = { 3,3,3,3 };
    add_operand_inp(k1);
    add_operator_inp('+');
    add_operand_inp(k2);

    add_operand_out(k1);
    add_operand_out(k2);
    add_operator_out("+");

    EXPECT_EQ(output, Converter::conv(input, operands_out, operators_out, values));
}
TEST_F(converter_test, can_convert_simple_substraction)
{
    coef k1 = { 1,2,2,2 };
    coef k2 = { 3,3,3,3 };
    add_operand_inp(k1);
    add_operator_inp('-');
    add_operand_inp(k2);

    add_operand_out(k1);
    add_operand_out(k2);
    add_operator_out("-");

    EXPECT_EQ(output, Converter::conv(input, operands_out, operators_out, values));
}
TEST_F(converter_test, can_convert_simple_multipliaction)
{
    coef k1 = { 1,2,2,2 };
    coef k2 = { 3,3,3,3 };
    add_operand_inp(k1);
    add_operator_inp('*');
    add_operand_inp(k2);

    add_operand_out(k1);
    add_operand_out(k2);
    add_operator_out("*");

    EXPECT_EQ(output, Converter::conv(input, operands_out, operators_out, values));
}
TEST_F(converter_test, can_correctly_determine_prio_of_operations)
{
    coef k1 = { 1,2,2,2 };
    coef k2 = { 3,3,3,3 };
    coef k3 = { 2,1,1,1 };
    add_operand_inp(k1);
    add_operator_inp('-');
    add_operand_inp(k2);
    add_operator_inp('*');
    add_operand_inp(k3);

    add_operand_out(k1);
    add_operand_out(k2);
    add_operand_out(k3);
    add_operator_out("*");
    add_operator_out("-");

    EXPECT_EQ(output, Converter::conv(input, operands_out, operators_out, values));
}
TEST_F(converter_test, can_convert_simple_addition_with_variable)
{
    Monom m(10, 1, 1, 1);
    coef k1 = { 10,1,1,1 };
    Polynom pol(m);
    add_variable("a", pol);

    add_operand_inp("a");
    add_operator_inp('+');
    coef k2 = { 3,4,4,4 };
    add_operand_inp(k2);

    add_operand_out(k1);
    add_operand_out(k2);
    add_operator_out("+");

    EXPECT_EQ(output, Converter::conv(input, operands_out, operators_out, values));
}
TEST_F(converter_test, can_convert_simple_substraction_with_variable)
{
    Monom m(10, 1, 1, 1);
    coef k1 = { 10,1,1,1 };
    Polynom pol(m);
    add_variable("a", pol);

    add_operand_inp("a");
    add_operator_inp('-');
    coef k2 = { 3,4,4,4 };
    add_operand_inp(k2);

    add_operand_out(k1);
    add_operand_out(k2);
    add_operator_out("-");

    EXPECT_EQ(output, Converter::conv(input, operands_out, operators_out, values));
}
TEST_F(converter_test, can_convert_simple_multiplication_with_variable)
{
    Monom m(10, 1, 1, 1);
    coef k1 = { 10,1,1,1 };
    Polynom pol(m);
    add_variable("a", pol);

    add_operand_inp("a");
    add_operator_inp('*');
    coef k2 = { 3,4,4,4 };
    add_operand_inp(k2);

    add_operand_out(k1);
    add_operand_out(k2);
    add_operator_out("*");

    EXPECT_EQ(output, Converter::conv(input, operands_out, operators_out, values));
}
TEST_F(converter_test, empty_return_if_variable_is_not_existing)
{
    add_operand_inp("a");
    add_operator_inp('*');
    coef k = { 3,1,1,1 };
    add_operand_inp(k);

    EXPECT_TRUE(Converter::conv(input, operands_out, operators_out, values).empty());
}
TEST_F(converter_test, can_correctly_determine_prio_of_operations_with_variable)
{
    Monom m(10, 1, 1, 1);
    coef k1 = { 10,1,1,1 };
    Polynom pol(m);
    add_variable("a", pol);

    coef k2 = { 3,1,0,0 };
    coef k3 = { 1,2,2,2 };
    add_operand_inp(k2);
    add_operator_inp('*');
    add_operand_inp("a");
    add_operator_inp('+');
    add_operand_inp(k3);

    add_operand_out(k2);
    add_operand_out(k1);
    add_operator_out("*");
    add_operand_out(k3);
    add_operator_out("+");

    EXPECT_EQ(output, Converter::conv(input, operands_out, operators_out, values));
}

TEST_F(converter_test, can_covert_simple_operation_with_two_variables)
{
    Monom m1(10, 1, 1, 1);
    coef k1 = { 10,1,1,1 };
    Polynom pol1(m1);
    add_variable("a", pol1);
    
    Monom m2(10, 1, 1, 1);
    coef k2 = { 14,1,1,1 };
    Polynom pol2(m2);
    add_variable("b", pol2);

    add_operand_inp("a");
    add_operator_inp('+');
    add_operand_inp("b");

    add_operand_out(k1);
    add_operand_out(k2);
    add_operator_out("+");

    EXPECT_EQ(output, Converter::conv(input, operands_out, operators_out, values));
}