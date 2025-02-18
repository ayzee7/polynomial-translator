#include "converter.h"

std::vector<Term> Converter::conv(std::vector<Term> inp, std::vector<double>& operands,std::map<std::string,double>& values)
{
	std::map<std::string, int> prio = { {"(",0}, {"+",1}, {"-",1},{"*",2},{"/",2}};

	Stack<std::vector, Term> s1(std::vector<Term> {});
	std::vector<Term> post_str;
	bool fl = 0;
	for (Term t : inp)
	{
		switch (t.get_type())
		{
		case Term::Type::NUMBER:
			operands.push_back(std::stod(t.get_value()));
			post_str.push_back(t);
			break;
		case Term::Type::OPEN_BRACK:
			s1.push(t);
			break;
		case Term::Type::CLOSE_BRACK:
			
			while (s1.top().get_value() != "(")
			{
				post_str.push_back(s1.top());
				s1.pop();
			}
			s1.pop();
			break;
		case Term::Type::OPERATOR:
			while (!s1.empty())
			{
				if (prio[s1.top().get_value()] >= prio[t.get_value()])
				{
					post_str.push_back(s1.top());
					s1.pop();
				}
				else
				{
					break;
				}
			}
			s1.push(t);
			break;
		case Term::Type::VALUE:
			if (values.count(t.get_value()) != 0)
			{
				operands.push_back(values[t.get_value()]);
				post_str.push_back(Term(values[t.get_value()]));
				break;
			}
			else
			{
				fl = 1;
				std::cout << "Value " << t.get_value() << " is not existing" << std::endl;
				post_str.clear();
				return post_str;
			}
		}
	}
	while (!s1.empty())
	{
		post_str.push_back(s1.top());
		s1.pop();
	}
	return post_str;
}