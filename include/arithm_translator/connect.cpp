#include "connect.h"
void Connect::handler(std::map<std::string, Polynom>& values, std::vector<Term>& terms)
{
	std::vector<Polynom> operands;
	std::vector<std::string> operators;
	std::vector<Term::Type> post_str;
	Polynom ans;


	if (terms.size() >= 3 && terms[1].get_name() == "=")
	{
		std::string value = terms[0].get_name();
		terms.erase(terms.begin(), terms.begin() + 2);
		post_str = Converter::conv(terms, operands,operators, values);

		if (values.count(value) != 0 && !post_str.empty()	)
		{
			values[value] = Calc::Calculate(post_str, operands, operators);
			std::cout << "Click ESC to close or ENTER to continue";
		}
		if (values.count(value) == 0 && !post_str.empty())
		{
			std::pair < std::string, Polynom> a;
			a.first = value;
			a.second = Calc::Calculate(post_str, operands,operators);
			values.insert(a);
			std::cout << "Click ESC to close or ENTER to continue";
		}
		if (post_str.empty() == true)
		{
			std::cout << "Click ESC to close or ENTER to continue";
		}

	}
	else
	{
		post_str = Converter::conv(terms, operands, operators, values);
		if (post_str.empty() == true)
		{
			std::cout << "Click ESC to close or ENTER to continue";

		}
		else
		{
			ans = Calc::Calculate(post_str, operands, operators);
			std::cout << ans << std::endl;
			std::cout << "Click ESC to close or ENTER to continue";
		}


	}
}
void Connect::connection()
{
	std::map<std::string, Polynom> values;

	char ch;
	do {
		std::string str;
		std::vector<Term> terms = Parser::pars(str);

		Connect::handler(values, terms);
		
		ch = _getch();
		if (ch == 13)
			std::cout << std::endl;
	} while (ch != 27);

}