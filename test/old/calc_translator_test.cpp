#include <gtest.h>
#include "calc.h"
#include "parser.h"

class calc_test : public ::testing::Test {
protected:
    std::vector<Term::Type> post_str;
    std::vector<Polynom> operands;
    std::vector<std::string> operators;

    void addOperator(const std::string& ch) 
    {
        post_str.push_back(Term::Type::OPERATOR);
        operators.push_back(ch);
    }

    void addOperand(const Polynom& value) 
    {
        post_str.push_back(Term::Type::MONOM);
        operands.push_back(value);
    }

    void SetUp() override 
    {
        post_str.clear();
        operands.clear();
        operators.clear();
    }
};


TEST_F(calc_test, simple_addition)
{
    Monom a(3, 0, 0, 0);
    Polynom pol1(a);
    addOperand(pol1);
    Monom b(2, 1, 1, 1);
    Polynom pol2(b);
    addOperand(pol2);
    addOperator("+");

    Polynom p = pol1 + pol2;
    EXPECT_EQ(p, Calc::Calculate(post_str, operands, operators));
}
TEST_F(calc_test, simple_substraction)
{
    Monom a(3, 0, 0, 0);
    Polynom pol1(a);
    addOperand(pol1);
    Monom b(2, 1, 1, 1);
    Polynom pol2(b);
    addOperand(pol2);
    addOperator("-");

    Polynom p = pol1 - pol2;
    EXPECT_EQ(p, Calc::Calculate(post_str, operands, operators));
}
TEST_F(calc_test, simple_multiplication)
{
    Monom a(3, 0, 0, 0);
    Polynom pol1(a);
    addOperand(pol1);
    Monom b(2, 1, 1, 1);
    Polynom pol2(b);
    addOperand(pol2);
    addOperator("*");

    Polynom p = pol1 * pol2;
    EXPECT_EQ(p, Calc::Calculate(post_str, operands, operators));
}
TEST_F(calc_test, can_solve_complex_expression)
{
    Monom a(3, 0, 0, 0);
    Polynom pol1(a);
    addOperand(pol1);

    Monom b(2, 1, 1, 1);
    Polynom pol2(b);
    addOperand(pol2);

    addOperator("+");

    Monom c(4, 2, 2, 2);
    Polynom pol3(c);
    addOperand(pol3);

    addOperator("*");

    Polynom p = pol1 + pol2;
    p = p * pol3;
    EXPECT_EQ(p, Calc::Calculate(post_str, operands, operators));
}
TEST_F(calc_test, complex_expression_with_multiple_operations)
{
    Monom a(3, 0, 0, 0);  
    Monom b(2, 1, 1, 1);  
    Monom c(4, 2, 2, 2);  
    Monom d(1, 0, 1, 0);  

    Polynom pol1(a);  
    Polynom pol2(b);  
    Polynom pol3(c);
    Polynom pol4(d); 

    addOperand(pol1);
    addOperand(pol2);
    addOperator("+");

    addOperand(pol3);
    addOperator("*");

    addOperand(pol4);
    addOperator("-");

    Polynom expected = (pol1 + pol2) * pol3 - pol4;

    EXPECT_EQ(expected, Calc::Calculate(post_str, operands, operators));
}
TEST_F(calc_test, negative_coefficients)
{
    Monom a(-3, 1, 0, 0);
    Polynom pol1(a);

    Monom b(-2, 0, 1, 1); 
    Polynom pol2(b);

    addOperand(pol1);
    addOperand(pol2);
    addOperator("+");

    Polynom p = pol1 + pol2;
    EXPECT_EQ(p, Calc::Calculate(post_str, operands, operators));
}
TEST_F(calc_test, polynom_multiplication_by_constant)
{
    Monom a(3, 1, 1, 1);  
    Polynom pol1(a);

    Monom b(2, 0, 0, 0); 
    Polynom pol2(b);

    addOperand(pol1);
    addOperand(pol2);
    addOperator("*");

    Polynom p = pol1 * pol2;  
    EXPECT_EQ(p, Calc::Calculate(post_str, operands, operators));
}
