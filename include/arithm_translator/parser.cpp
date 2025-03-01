#include "parser.h"
double Term::CONSTANTS::pi = 3.14159265359;
double Term::CONSTANTS::e = 2.71828182846;
std::vector<char> Parser::pars(std::string str)
{
	std::vector<char> v{};
	for (char ch : str)
		v.push_back(ch);
	return v;
}
Term::Term(double value) :type(Type::NUMBER), value_str(std::to_string(value)) {}
Term::Term(char ch)
{
	if (ch == 40)
	{
		type = Type::OPEN_BRACK;
		value_str.push_back(ch);
	}
	if (ch == 41)
	{
		type = Type::CLOSE_BRACK;
		value_str.push_back(ch);
	}
	if (ch == 43 || ch == 42 || ch == 45 || ch == 47)
	{
		type = Type::OPERATOR;
		value_str.push_back(ch);
	}
	if (ch == 61)
	{
		type = Type::EQ;
		value_str.push_back(ch);
	}
}
Term::Term(std::string str)
{
	if (str == "pi" || str == "PI" || str == "Pi")
	{
		type = Type::NUMBER;
		value_str = std::to_string(Term::CONSTANTS::pi);
	}
	else if (str == "e")
	{
		type = Type::NUMBER;
		value_str = std::to_string(Term::CONSTANTS::e);
	}
	else
	{
		type = Type::VALUE;
		value_str = str;
	}
}
double Term::to_value(std::string str)
{
	return std::stod(str);
}
std::string Term::get_value() const
{
	return value_str;
}
Term::Type Term::get_type() const
{
	return type;
}
bool Term::operator==(const Term& other) const
{
	return (get_type() == other.get_type() && get_value() == other.get_value());
}
std::vector<Term> Parser::term_analis(std::string str)
{
	std::vector<Term> output {};

	int status = 0;
	std::string str_value;
	for (char ch : str)
	{
		switch (status)
		{
		case 0:
			if (ch == 40)
			{
				status = 7;
				output.push_back(Term(ch));
				break;
			}
			if (ch >= 48 && ch <= 57)
			{
				status = 1;
				str_value.push_back(ch);
				break;
			}
			if (ch >= 97 && ch <= 122 || ch >= 65 || ch <= 90)
			{
				status = 8;
				str_value.push_back(ch);
				break;
			}
		case 1:
			if (ch >= 48 && ch <= 57)
			{
				status = 1;
				str_value.push_back(ch);
				break;
			}
			if (ch == 46)
			{
				status = 6;
				str_value.push_back(ch);
				break;
			}
			if (ch == 43 || ch == 42 || ch == 45 || ch == 47)
			{
				status = 2;
				output.push_back(Term(Term::to_value(str_value)));
				output.push_back(Term(ch));
				str_value.clear();
				break;
			}
		case 2:
			if (ch == 40)
			{
				status = 0;
				output.push_back(Term(ch));
				break;
			}
			if (ch >= 48 && ch <= 57)
			{
				status = 3;
				str_value.push_back(ch);
				break;
			}
			if (ch >= 97 && ch <= 122 || ch >= 65 && ch <= 90)
			{
				status = 12;
				str_value.push_back(ch);
				break;
			}
		case 3:
			if (ch >= 48 && ch <= 57)
			{
				status = 3;
				str_value.push_back(ch);
				break;
			}
			if (ch == 46)
			{
				status = 6;
				str_value.push_back(ch);
				break;
			}
			if (ch == 41)
			{
				status = 4;
				output.push_back(Term(Term::to_value(str_value)));
				str_value.clear();
				output.push_back(Term(ch));
				break;
			}
			if (ch == 43 || ch == 42 || ch == 45 || ch == 47)
			{
				status = 2;
				output.push_back(Term(Term::to_value(str_value)));
				output.push_back(Term(ch));
				str_value.clear();
				break;
			}
		case 4:
			if (ch == 41)
			{
				status = 4;
				output.push_back(Term(ch));
				break;
			}
			if (ch == 43 || ch == 42 || ch == 45 || ch == 47)
			{
				status = 2;
				output.push_back(Term(ch));
				break;
			}
		case 6:
			if (ch >= 48 && ch <= 57)
			{
				status = 6;
				str_value.push_back(ch);
				break;
			}
			if (ch == 41)
			{
				status = 4;
				output.push_back(Term(Term::to_value(str_value)));
				str_value.clear();
				output.push_back(Term(ch));
				break;
			}
			if (ch == 43 || ch == 42 || ch == 45 || ch == 47)
			{
				status = 2;
				output.push_back(Term(Term::to_value(str_value)));
				str_value.clear();
				output.push_back(Term(ch));
				break;
			}
		case 7:
			if (ch == 40)
			{
				status = 7;
				output.push_back(Term(ch));
				break;
			}
			if (ch >= 48 && ch <= 57)
			{
				status = 1;
				str_value.push_back(ch);
				break;
			}
			if (ch >= 97 && ch <= 122 || ch >= 65 && ch <= 90)
			{
				status = 10;
				str_value.push_back(ch);
				break;
			}
		case 8:
			if (ch >= 97 && ch <= 122 || ch >= 65 && ch <= 90)
			{
				status = 8;
				str_value.push_back(ch);
				break;
			}
			if (ch == 61)
			{
				output.push_back(Term(str_value));
				str_value.clear();
				output.push_back(Term(ch));
				status = 9;
				break;
			}
			if (ch == 43 || ch == 42 || ch == 45 || ch == 47)
			{
				output.push_back(Term(str_value));
				str_value.clear();
				output.push_back(Term(ch));
				status = 11;
				break;
			}
		case 9:
			if (ch == 40)
			{
				status = 9;
				output.push_back(Term(ch));
				break;
			}
			if (ch >= 97 && ch <= 122 || ch >= 65 && ch <= 90)
			{
				status = 10;
				str_value.push_back(ch);
				break;
			}
			if (ch >= 48 && ch <= 57)
			{
				status = 1;
				str_value.push_back(ch);
				break;
			}
		case 10:
			if (ch >= 97 && ch <= 122 || ch >= 65 && ch <= 90)
			{
				status = 10;
				str_value.push_back(ch);
				break;
			}
			if (ch == 43 || ch == 42 || ch == 45 || ch == 47)
			{
				output.push_back(Term(str_value));
				str_value.clear();
				output.push_back(Term(ch));
				status = 11;
				break;
			}
		case 11:
			if (ch == 40)
			{
				status = 9;
				output.push_back(Term(ch));
				break;
			}
			if (ch >= 97 && ch <= 122 || ch >= 65 && ch <= 90)
			{
				status = 12;
				str_value.push_back(ch);
				break;
			}
			if (ch >= 48 && ch <= 57)
			{
				status = 3;
				str_value.push_back(ch);
				break;
			}
		case 12:
			if (ch >= 97 && ch <= 122 || ch >= 65 && ch <= 90)
			{
				status = 12;
				str_value.push_back(ch);
				break;
			}
			if (ch == 43 || ch == 42 || ch == 45 || ch == 47)
			{
				status = 2;
				output.push_back(Term(str_value));
				str_value.clear();
				output.push_back(Term(ch));
				break;
			}
			if (ch == 41)
			{
				status = 4;
				output.push_back(Term(str_value));
				str_value.clear();
				output.push_back(Term(ch));
				break;
			}
		}
	}
	if (str_value.empty() != true)
	{
		if (str.back() >= 48 && str.back() <= 57)
		{
			output.push_back(Term(Term::to_value(str_value)));
			str_value.clear();
		}
		if (str.back() >= 97 && str.back() <= 122 || str.back() >= 65 && str.back() <= 90)
		{
			output.push_back(Term(str_value));
			str_value.clear();
		}
		
	}
	return output;
}
void Parser::del_ch(std::string& input, Stack<std::vector, int>& S, int& status,int& parenthesis_counter)
{
	if (input.back() == 40)
		parenthesis_counter--;
	if (input.back() == 41)
		parenthesis_counter++;
	Interface::delete_ch();
	S.pop();
	input.pop_back();
	status = S.top();
}
int Parser::add_ch(std::string& input, Stack<std::vector, int>& S,int st,char& ch)
{
	S.push(st);
	Interface::print_ch(ch);
	input.push_back(ch);
	return st;
}
char Parser::synt_analis_fsm(int& parenthesis_counter,std::string& input, Stack<std::vector, int>& S,int status)	
{
	char ch = _getch();
	S.push(0);
	while ((ch != 13 || parenthesis_counter != 0 || status == 2 ||status==11 || status ==13 || status ==5 ) && ch != 3)
	{
		switch (status)
		{
		case 0:
			if (ch >= 97 && ch <= 122 || ch >= 65 && ch <= 90)
			{
				status = add_ch(input, S, 8, ch);
				break;
			}
			if ((ch >= 48 && ch <= 57))
			{
				status = add_ch(input, S, 1, ch);
				break;
			}

			if (ch == 40)
			{
				status = add_ch(input, S, 7, ch);
				parenthesis_counter++;
				break;
			}
			if (ch == 8)
			{
				if (input.size() == 0) break;
				if (S.size() == 1 && S.top() == 0)
				{
					Interface::delete_ch();
					input.pop_back();
					break;
				}
				del_ch(input, S, status, parenthesis_counter);
				break;
			}
			
			else
			{
				Interface::print_red_ch(ch);
				status = 5;
				break;
			}
		case 1:
			if (ch == 43 || ch == 42 || ch == 45 || ch == 47)
			{
				status = add_ch(input,S,2,ch);
				break;
			}
			if (ch == 8)
			{
				del_ch(input, S, status, parenthesis_counter);
				break;
			}
			if (ch == 46)
			{
				status = add_ch(input, S, 6, ch);
				break;
			}
			if (ch >= 48 && ch <= 57)
			{
				status = add_ch(input, S, 1, ch);
				break;
			}
			else
			{
				Interface::print_red_ch(ch);
				status = 5;
				break;
			}
		case 2:
			if (ch == 40)
			{
				status = add_ch(input, S, 0, ch);
				parenthesis_counter++;
				break;
			}
			if ((ch >= 48 && ch <= 57))
			{
				status = add_ch(input, S, 3, ch);
				break;
			}
			if (ch == 8)
			{
				del_ch(input,S,status,parenthesis_counter);
				break;
			}
			if (ch >= 97 && ch <= 122 || ch >= 65 && ch <= 90)
			{
				status = add_ch(input, S, 12, ch);
				break;
			}
			if (ch == 13)
			{
				status = 13;
				break;
			}
			else
			{
				Interface::print_red_ch(ch);
				status = 5;
				break;
			}
		case 3:
			if (ch == 41)
			{
				parenthesis_counter--;
				if (parenthesis_counter < 0)
				{
					Interface::print_red_ch(ch);
					status = 5;
					break;
				}
				status = add_ch(input, S, 4, ch);
				break;
			}
			if (ch == 43 || ch == 42 || ch == 45 || ch == 47)
			{
				status = add_ch(input, S, 2, ch);
				break;
			}
			if (ch == 8)
			{
				del_ch(input, S, status, parenthesis_counter);
				break;
			}
			if (ch == 46)
			{
				status = add_ch(input, S, 6, ch);
				break;
			}

			if (ch == 13)
			{
				status = 13;
				break;
			}
			if (ch >= 48 && ch <= 57)
			{
				status = add_ch(input, S, 3, ch);
				break;
			}
			
			else
			{
				Interface::print_red_ch(ch);
				status = 5;
				break;
			}
		case 4:
			if (ch == 41)
			{
				status = add_ch(input,S,4,ch);
				parenthesis_counter--;
				if (parenthesis_counter < 0)
				{
					Interface::print_red_ch(ch);
					parenthesis_counter++;
					status = 5;
					break;
				}
				break;
			}
			if (ch == 13)
			{
				status = 13;
				break;
			}
			if (ch == 43 || ch == 42 || ch == 45 || ch == 47)
			{
				status = add_ch(input, S, 2, ch);
				break;
			}
			if (ch == 8)
			{
				del_ch(input, S, status, parenthesis_counter);
				break;
			}
			
			else
			{
				Interface::print_red_ch(ch);
				status = 5;
				break;
			}
		case 5:
			if (ch == 8)
			{
				status = S.top();
				Interface::delete_ch();
				break;
			}
			status = 5;
			break;
		case 6:
			if (ch >= 48 && ch <= 57)
			{
				status = add_ch(input, S, 6, ch);
				break;
			}
			if (ch == 41)
			{
				parenthesis_counter--;
				if (parenthesis_counter < 0)
				{
					Interface::print_red_ch(ch);
					status = 5;
					break;
				}
				status = add_ch(input, S, 4, ch);
				break;
			}
			if (ch == 43 || ch == 42 || ch == 45 || ch == 47)
			{
				status = add_ch(input, S, 2, ch);
				break;
			}
			if (ch == 13)
			{
				status = 13;
				break;
			}
			if (ch == 8)
			{
				del_ch(input, S, status, parenthesis_counter);
				break;
			}
			
			else
			{
				Interface::print_red_ch(ch);
				status = 5;
				break;
			}
		case 7:
			if (ch == 40)
			{
				status = add_ch(input, S, 7, ch);
				parenthesis_counter++;
				break;
			}
			if (ch >= 48 && ch <= 57)
			{
				status = add_ch(input, S, 1, ch);
				break;
			}
			if (ch >= 97 && ch <= 122 || ch >= 65 && ch <= 90)
			{
				status = add_ch(input, S, 10, ch);
				break;
			}
			if (ch == 8)
			{
				del_ch(input, S, status, parenthesis_counter);
				break;
			}
			if (ch == 13)
			{
				status = 13;
				break;
			}
			else
			{
				Interface::print_red_ch(ch);
				status = 5;
				break;
			}
		case 8:
			if (ch >= 97 && ch <= 122 || ch >= 65 && ch <= 90)
			{
				status = add_ch(input,S,8,ch);
				break;
			}
			if (ch == 61)
			{
				status = add_ch(input, S, 9, ch);
				break;
			}
			if (ch == 43 || ch == 42 || ch == 45 || ch == 47)
			{
				status = add_ch(input, S, 11, ch);
				break;
			}
			if (ch == 8)
			{
				del_ch(input, S, status, parenthesis_counter);
				break;
			}
			
			else
			{
				Interface::print_red_ch(ch);
				status = 5;
				break;
			}
		case 9:
			if (ch == 40)
			{
				status = add_ch(input, S, 9, ch);
				parenthesis_counter++;
				break;
			}
			if (ch >= 97 && ch <= 122 || ch >= 65 && ch <= 90)
			{
				status = add_ch(input, S, 10, ch);
				break;
			}
			if (ch >= 48 && ch <= 57)
			{
				status = add_ch(input,S,1,ch);
				break;
			}
			if (ch == 13)
			{
				status = 13;
				break;
			}
			if (ch == 8)
			{
				del_ch(input, S, status, parenthesis_counter);
				break;
			}
			else
			{
				Interface::print_red_ch(ch);
				status = 5;
				break;
			}
		case 10:
			if (ch >= 97 && ch <= 122 || ch >= 65 && ch <= 90)
			{
				status = add_ch(input, S, 10, ch);
				break;
			}
			if (ch == 43 || ch == 42 || ch == 45 || ch == 47)
			{
				status = add_ch(input, S, 11, ch);
				break;
			}
			if (ch == 8)
			{
				del_ch(input, S, status, parenthesis_counter);
				break;
			}
			if (ch == 13)
			{
				status = 13;
				break;
			}
			else
			{
				Interface::print_red_ch(ch);
				status = 5;
				break;
			}
		case 11:
			if (ch == 40)
			{
				status = add_ch(input, S, 9, ch);
				parenthesis_counter++;
				break;
			}
			if (ch >= 97 && ch <= 122 || ch >= 65 && ch <= 90)
			{
				status = add_ch(input, S, 12, ch);
				break;
			}
			if (ch >= 48 && ch <= 57)
			{
				status = add_ch(input, S, 3, ch);
				break;
			}
			if (ch == 8)
			{
				del_ch(input, S, status, parenthesis_counter);
				break;
			}
			if (ch == 13)
			{
				status = 13;
				break;
			}
			else
			{
				Interface::print_red_ch(ch);
				status = 5;
				break;
			}
		case 12:
			if (ch >= 97 && ch <= 122 || ch >= 65 && ch <= 90)
			{
				status = add_ch(input, S, 12, ch);
				break;
			}
			if (ch == 41)
			{
				parenthesis_counter--;
				if (parenthesis_counter < 0)
				{
					Interface::print_red_ch(ch);
					status = 5;
					break;
				}
				status = add_ch(input, S, 4, ch);
				break;
			}
			if (ch == 43 || ch == 42 || ch == 45 || ch == 47)
			{
				status = add_ch(input, S, 2, ch);
				break;
			}
			if (ch == 8)
			{
				del_ch(input, S, status, parenthesis_counter);
				break;
			}
			if (ch == 13)
			{
				status = 13;
				break;
			}
			else
			{
				Interface::print_red_ch(ch);
				status = 5;
				break;
			}
		case 13:
			if (ch != 13)
			{
				status = S.top();
				break;
			}
			Interface::print_red_ch(63);
			status = 5;
			break;
		}
		ch = _getch();
	}
	return ch;
}
std::string Parser::synt_analis()
{
	int parenthesis_counter;
	std::string input;
	do
	{
		parenthesis_counter = 0;
		input.clear();
		Stack<std::vector, int> S(std::vector<int> {});
		int status = 0;
		char ch = synt_analis_fsm(parenthesis_counter, input, S, status);
		if (ch == 3)
		{
			input.clear();
		}
		std::cout << std::endl;
		if (parenthesis_counter != 0)
		{
			std::cout << "Check the number of parentthesis" << std::endl;
			std::cout << "Click ENTER to rewrite expression";
			while (_getch() != 13)
			{
				continue;
			}
			Interface::clear_console();
		}
	} while (parenthesis_counter != 0);
	
	return input;
}

