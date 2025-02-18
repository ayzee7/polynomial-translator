#include <gtest.h>
#include "connect/connect.h"

class test_connection : public::testing::Test
{
protected:
    std::vector<Term> terms;
    std::map<std::string, double> values;

    void add_operator(const char& ch)
    {
        Term a(ch);
        terms.push_back(a);
    }
    void add_operand(double value)
    {
        Term a(value);
        terms.push_back(a);
    }
    void add_operand(const std::string& variable)
    {
        Term a(variable);
        terms.push_back(a);
    }
    void add_variable(const std::string& name, double value)
    {
        std::pair<std::string, double> a;
        a.first = name;
        a.second = value;
        values.insert(a);
    }
    void SetUp() override
    {
        terms.clear();
        values.clear();
    }
};

TEST_F(test_connection, can_assign_expression_to_variable)
{
    add_operand("a");
    add_operator('=');
    add_operand(2);
    add_operator('+');
    add_operand(7);

    Connect::handler(values, terms);
    EXPECT_EQ(9,values["a"]);
}
TEST_F(test_connection, can_assign_expression_to_already_existing_variable)
{
    add_variable("a", 10);

    add_operand("a");
    add_operator('=');
    add_operand(2);
    add_operator('+');
    add_operand(7);

    Connect::handler(values, terms);
    EXPECT_EQ(9, values["a"]);
}
TEST_F(test_connection, can_assign_expression_with_variables)
{
    add_variable("b", 10);
    add_variable("c", 24);

    add_operand("a");
    add_operator('=');
    add_operand("b");
    add_operator('+');
    add_operand("c");

    Connect::handler(values, terms);
    EXPECT_EQ(34, values["a"]);
}
TEST_F(test_connection, can_assign_expression_with_variable_to_itself)
{
    add_variable("a", 10);
    add_operand("a");
    add_operator('=');
    add_operand("a");
    add_operator('+');
    add_operand(7);

    Connect::handler(values, terms);
    EXPECT_EQ(17, values["a"]);
}
TEST_F(test_connection, doesnt_throw_when_expression_with_not_existing_variable)
{
    add_operand("a");
    add_operator('+');
    add_operand(7);

    ASSERT_NO_THROW(Connect::handler(values, terms));
}
