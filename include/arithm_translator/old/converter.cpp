#include "converter.h"

std::vector<Term::Type> Converter::conv(std::vector<Term> inp, std::vector<Polynom>& operands,std::vector<std::string> operators,std::map<std::string,Polynom>& values)
{
	std::map<std::string, int> prio = {  {"+",1}, {"-",1},{"*",2} };

	Stack<std::vector, Term> s1(std::vector<Term> {});
	std::vector<Term::Type> post_str;
	bool fl = 0;
	for (Term t : inp)
	{
		switch (t.get_type())
		{
		case Term::Type::MONOM:
		{
			coef k = t.get_coef();
			Monom m(k.k, k.x, k.y, k.z);
			operands.push_back(Polynom(m));
			post_str.push_back(t.get_type());
			break;
		}
			
		case Term::Type::OPERATOR:
			while (!s1.empty())
			{
				if (prio[s1.top().get_name()] >= prio[t.get_name()])
				{
					post_str.push_back(s1.top().get_type());
					operators.push_back(s1.top().get_name());
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
			if (values.count(t.get_name()) != 0)
			{
				operands.push_back(values[t.get_name()]);
				post_str.push_back(Term::Type::MONOM);
				break;
			}
			else
			{
				fl = 1;
				std::cout << "Value " << t.get_name() << " is not existing" << std::endl;
				post_str.clear();
				return post_str;
			}
		}
	}
	while (!s1.empty())
	{
		post_str.push_back(s1.top().get_type());
		operators.push_back(s1.top().get_name());
		s1.pop();
	}
	return post_str;
}