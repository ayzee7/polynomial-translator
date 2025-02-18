#pragma once
#include <iostream>
#include "interface.h"
#include <conio.h>
#include "stack.h"
#include <vector>
#include <string>


class Term
{
public:
	enum class Type
	{
		NUMBER,
		OPERATOR,
		OPEN_BRACK,
		CLOSE_BRACK,
		VALUE,
		EQ
	};
	class CONSTANTS
	{
	public:
		static double pi;
		static double e;
	};
private:
	Type type;
	std::string value_str;
public:
	Term(double value);
	Term(char ch);
	Term(std::string str);
	
	static double to_value(std::string str);
	std::string get_value() const;
	Type get_type() const;
	bool operator==(const Term& other) const;

};
class Parser
{	
public:
	static void del_ch(std::string& input, Stack<std::vector, int>& S,int& status, int& parenthesis_counter);
	static int add_ch(std::string& input, Stack<std::vector, int>& S, int status, char& ch);
	static std::vector<char> pars(std::string str);
	static std::string synt_analis();
	static std::vector<Term> term_analis(std::string str);
	static char synt_analis_fsm(int& parenthesis_counter, std::string& input, Stack<std::vector, int>& S, int status);
	static void value_analis_fsm(char ch,std::string input, Stack<std::vector, int> S);
};