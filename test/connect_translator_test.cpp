#include <gtest.h>
#include "connect.h"

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
