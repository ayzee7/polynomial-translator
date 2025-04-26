#include "connect.h"
void Connect::handler(std::map<std::string, double>& values, std::vector<Term>& terms)
{
	std::vector<double> operands;
	std::vector<Term> post_str;
	double ans;


	if (terms.size() >= 3 && terms[1].get_value() == "=")
	{
		std::string value = terms[0].get_value();
		terms.erase(terms.begin(), terms.begin() + 2);
		post_str = Converter::conv(terms, operands, values);

		if (values.count(value) != 0 && !post_str.empty()	)
		{
			values[value] = Calc::Calculate(post_str, operands);
			std::cout << "Click ESC to close or ENTER to continue";
		}
		if (values.count(value) == 0 && !post_str.empty())
		{
			std::pair < std::string, double> a;
			a.first = value;
			a.second = Calc::Calculate(post_str, operands);
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
		post_str = Converter::conv(terms, operands, values);
		if (post_str.empty() == true)
		{
			std::cout << "Click ESC to close or ENTER to continue";

		}
		else
		{
			ans = Calc::Calculate(post_str, operands);
			std::cout << ans << std::endl;
			std::cout << "Click ESC to close or ENTER to continue";
		}


	}
}
void Connect::connection()
{
	std::map<std::string, double> values;

	Interface::instraction();
	char ch;
	do {
		std::string str;
		str = Parser::synt_analis();
		std::vector<Term> terms = Parser::term_analis(str);

		Connect::handler(values, terms);
		
		ch = _getch();
		if (ch == 13)
			std::cout << std::endl;
	} while (ch != 27);

}