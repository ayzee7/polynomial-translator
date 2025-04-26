#include "calc.h"

double Calc::Calculate(std::vector<Term>& post_str, std::vector<double>& operands)
{
	Stack<std::vector, double> s1(std::vector<double> {});
	double left, right = 0;
	int i = 0;
	for (Term t : post_str)
	{
		
		switch (t.get_type())
		{
		case Term::Type::NUMBER:
			s1.push(operands[i]);
			i++;
			break;
		case Term::Type::OPERATOR:
			if (t.get_value() == "+")
			{
				right = s1.top();
				s1.pop();
				left = s1.top();
				s1.pop();
				s1.push(left + right);
				break;
			}
			if (t.get_value() == "-")
			{
				right = s1.top();
				s1.pop();
				left = s1.top();
				s1.pop();
				s1.push(left - right);
				break;
			}
			if (t.get_value() == "*")
			{
				right = s1.top();
				s1.pop();
				left = s1.top();
				s1.pop();
				s1.push(left * right);
				break;
			}
			if (t.get_value() == "/")
			{
				right = s1.top();
				s1.pop();
				left = s1.top();
				s1.pop();
				s1.push(left / right);//�������� �� ����?
				break;
			}	
		}
	}
	return s1.top();
}