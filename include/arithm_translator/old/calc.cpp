#include "calc.h"

Polynom Calc::Calculate(std::vector<Term::Type>& post_str, std::vector<Polynom>& operands, std::vector<std::string>& operators)
{
	Stack<std::vector, Polynom> s1(std::vector<Polynom> {});
	Polynom left, right;
	int i = 0;
	int j = 0;
	for (Term::Type t : post_str)
	{
		
		switch (t)
		{
		case Term::Type::MONOM:
			s1.push(operands[i]);
			i++;
			break;
		case Term::Type::OPERATOR:

			if (operators[j] == "+")
			{
				right = s1.top();
				s1.pop();
				left = s1.top();
				s1.pop();
				s1.push(left + right);
				j++;
				break;
			}
			if (operators[j] == "-")
			{
				right = s1.top();
				s1.pop();
				left = s1.top();
				s1.pop();
				s1.push(left - right);
				j++;
				break;
			}
			if (operators[j] == "*")
			{
				right = s1.top();
				s1.pop();
				left = s1.top();
				s1.pop();
				s1.push(left * right);
				j++;
				break;
			}
		}
	}
	return s1.top();
}