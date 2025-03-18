#pragma once
#include <iostream>
#include "interface.h"
#include <conio.h>
#include "stack.h"
#include <vector>
#include <string>


struct coef
{
	double k = 0;
	int x = 0;
	int y = 0;
	int z = 0;

	bool empty() const
	{
		return (k == 0 && x == 0 && y == 0 && z == 0);
	}
	void clear()
	{
		k = 0;
		x = 0;
		y = 0;
		z = 0;
	}
	bool operator==(const coef& other) const {
		return (k == other.k && x == other.x && y == other.y && z == other.z);
	}
};
class Term
{
public:
	enum class Type
	{
		NUMBER,
		MONOM,
		OPERATOR,
		EQ,
		POW,
		VALUE
	};
protected:
	Type type;
	coef k;
	std::string name;
public:
	
	Term(const coef& s)
	{
		type = Type::MONOM;
		k = s;
	}
	Term(const std::string& n)
	{
		type = Type::VALUE;
		name = n;
	}
	Term(const char& ch)
	{
		if (ch == '=')
		{
			type = Type::EQ;
			name = ch;
		}
		else
		{
			type = Type::OPERATOR;
			name = ch;
		}
	}
	bool operator==(const Term& t) const
	{
		return (type == t.type && k == t.k && name == t.name && type == t.type);
	}
	Type get_type() const
	{
		return type;
	}
	coef get_coef() const
	{
		return k;
	}
	std::string get_name() const
	{
		return name;
	}
	friend std::ostream& operator<<(std::ostream& ostr, const Term& m)
	{
		switch (m.type)
		{
		case Type::MONOM:
			ostr << "MONOM: " << m.k.k<< " "<<m.k.x<<m.k.y<<m.k.z;
			break;
		case Type::OPERATOR:
			ostr << "OPERATOR: " << m.name;
			break;
		case Type::EQ:
			ostr << "EQ: " << m.name;
			break;
		case Type::POW:
			ostr << "POW: " << m.name;
			break;
		case Type::VALUE:
			ostr << "VALUE: " << m.name;
			break;
		default:
			ostr << "Unknown type";
			break;
		}
		return ostr;
	}
};

class Parser
{
public:
	static void set_k(const std::string& value, coef& s)
	{
		if (value.empty()) s.k = 1;
		else s.k = std::stod(value);
	}
	static std::vector<Term> pars(const std::string& str)
	{
		std::vector<Term> input;
		int status = 0;
		std::vector<Term> t;
		std::vector<int> mon;
		coef s;
		std::string value;//коэффициент перед мономом
		std::string var;//имя переменной
		for (char ch : str)
		{
			switch (status)
			{
			case 0:

				s.clear();

				if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'V')
				{
					var.push_back(ch);
					status = 11;
					break;
				}
				if (ch >= '0' && ch <= '9')
				{
					value.push_back(ch);
					set_k(value, s);
					status = 1;
					break;
				}
				if (ch == 'X')
				{
					s.k = 1;
					status = 2;
					break;
				}
				if (ch == 'Y')
				{
					s.k = 1;
					s.x = 0;
					status = 5;
					break;
				}
				if (ch == 'Z')
				{
					s.k = 1;
					s.x = 0;
					s.y = 0;
					status = 8;
					break;
				}
				else
				{
					status = 100;
					break;
				}
			case 1:
				if (ch >= '0' && ch <= '9' || ch =='.')
				{
					value.push_back(ch);
					status = 1;
					break;
				}
				if (ch == 'X')
				{
					set_k(value, s);
					value.clear();
					s.x = 1;
					status = 2;
					break;
				}
				if (ch == 'Y')
				{
					set_k(value, s);
					value.clear();
					s.x = 0;
					s.y = 1;
					status = 5;
					break;
				}
				if (ch == 'Z')
				{
					set_k(value, s);
					value.clear();
					s.x = 0;
					s.y = 0;
					s.z = 1;
					status = 8;
					break;
				}
				if (ch == '+' || ch == '*' || ch == '-')
				{
					set_k(value, s);
					value.clear();
					t.push_back(Term(s));
					s.clear();
					t.push_back(Term(ch));
					status = 0;
					break;
				}
				else
				{
					status = 100;
					break;
				}
			case 2:

				if (ch == '^')
				{
					status = 3;
					break;
				}
				if (ch == 'Y')
				{
					status = 5;
					s.x = 1;
					s.y = 1;
					break;
				}
				if (ch == 'Z')
				{
					status = 8;
					s.x = 1;
					s.y = 0;
					s.z = 0;
					break;
				}
				if (ch == '+' || ch == '*' || ch == '-')
				{
					s.x = 1;
					s.y = 0;
					s.z = 0;
					t.push_back(Term(s));
					s.clear();
					t.push_back(Term(ch));
					status = 0;
					break;
				}
				else
				{
					status = 100;
					break;
				}
			case 3:
				if (ch >= '0' && ch <= '9')
				{
					s.x = ch - '0';
					status = 4;
					break;
				}
				else
				{
					status = 100;
					break;
				}
			case 4:
				if (ch == 'Y')
				{
					s.y = 1;
					status = 5;
					break;
				}
				if (ch == 'Z')
				{
					status = 8;
					s.y = 0;
					s.z = 1;
					break;
				}
				if (ch == '+' || ch == '-' || ch == '*')
				{
					status = 0;
					s.y = 0;
					s.z = 0;
					t.push_back(Term(s));
					s.clear();
					t.push_back(Term(ch));
					break;
				}
				else
				{
					status = 100;
					break;
				}
			case 5:
				if (ch == '^')
				{
					status = 6;
					break;
				}
				if (ch == 'Z')
				{
					status = 8;
					s.y = 1;
					s.y = 1;
					break;
				}
				if (ch == '+' || ch == '-' || ch == '*')
				{
					status = 0;
					s.y = 1;
					s.z = 0;
					t.push_back(Term(s));
					s.clear();
					t.push_back(Term(ch));
					break;
				}
				else
				{
					status = 100;
					break;
				}
			case 6:
				if (ch >= '0' && ch <= '9')
				{
					s.y = ch - '0';
					status = 7;
					break;
				}
				else
				{
					status = 100;
					break;
				}
			case 7:
				if (ch == 'Z')
				{
					s.z = 1;
					status = 8;
					break;
				}
				if (ch == '+' || ch == '-' || ch == '*')
				{
					status = 0;
					s.z = 0;
					t.push_back(Term(s));
					s.clear();
					t.push_back(Term(ch));
					break;
				}
				else
				{
					status = 100;
					break;
				}
			case 8:
				if (ch == '^')
				{
					status = 9;
					break;
				}
				if (ch == '+' || ch == '-' || ch == '*')
				{
					status = 0;
					s.z = 1;
					t.push_back(Term(s));
					s.clear();
					t.push_back(Term(ch));
					break;
				}
				else
				{
					status = 100;
					break;
				}
			case 9:
				if (ch >= '0' && ch <= '9')
				{
					s.z = ch - '0';
					t.push_back(Term(s));
					s.clear();
					status = 10;
					break;
				}
				else
				{
					status = 100;
					break;
				}
			case 10:
				if (ch == '+' || ch == '*' || ch == '-')
				{
					status = 0;
					t.push_back(Term(ch));
					break;
				}
				else
				{
					status = 100;
					break;
				}
			case 11:
				if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'V')
				{
					status = 11;
					var.push_back(ch);
					break;
				}
				if (ch == '+' || ch == '-' || ch == '*')
				{
					status = 0;
					t.push_back(Term(var));
					var.clear();
					t.push_back(Term(ch));
				}
				if (ch == '=')
				{
					status = 12;
					t.push_back(Term(var));
					var.clear();
					t.push_back(Term(ch));
					break;
				}
				else
				{
					status = 100;
					break;
				}
			case 12:
				if (ch >= '0' && ch <= '9')
				{
					value.push_back(ch);
					set_k(value, s);
					status = 1;
					break;
				}
				if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'V')
				{
					var.push_back(ch);
					status = 13;
					break;
				}
				else
				{
					status = 100;
					break;
				}
			case 13:
				if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'V')
				{
					var.push_back(ch);
					status = 13;
					break;
				}
				if (ch == '+' || ch == '-' || ch == '*')
				{
					status = 12;
					t.push_back(Term(var));
					var.clear();
					t.push_back(Term(ch));
					break;
				}
				else
				{
					status = 100;
					break;
				}
			case 100:
				t.clear();
				std::cout << "Exeption" << std::endl;
				return t;

			default:
				break;
			}
		}
		if (!s.empty())
			t.push_back(Term(s));
		
		if (!t.empty() && ((*(--t.end())).get_type() == Term::Type::OPERATOR || (*(--t.end())).get_type() == Term::Type::EQ))
		{
			t.clear();
			std::cout << "Exeption" << std::endl;
		}
		return t;
	}
};