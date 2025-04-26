//#pragma once
#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "polinom.h"
#include "interface.h"
#include "calculator.h"
#include "parser.h"
#include <exception>

class BaseTranslator {
public:
	virtual ~BaseTranslator(){};
	virtual void execute() = 0;
};

template <class TCont>
class Translator : public BaseTranslator {

	string user_input;
	TCont vars;
	Parser parser;
	Calculator<TCont> calc;

	Polynom assignment(string var_name, string var_value, bool is_test) {
		try {
			parser.lvalue_analysis(var_name);
			parser.syntax_analysis(var_value);
			vector<Term> terms = parser.get_terms(var_value);
			Polynom result = calc.calculate(terms, vars);
			vars.insert(var_name, result);
			return result;
		}
		catch (exception e) {
			if (!is_test) {
				output_error(e);
				return Polynom();
			}
			else throw exception();
		}
	}

	Polynom expression_calculate(string expr, bool is_test) {
		try {
			parser.syntax_analysis(expr);
			vector<Term> terms = parser.get_terms(expr);
			Polynom result = calc.calculate(terms, vars);
			return result;
		}
		catch (exception e) {
			if (!is_test) {
				output_error(e);
				return Polynom();
			}
			else throw exception();
		}
	}

public:

	void execute() {
		user_input = await_input();
		user_input.erase(remove_if(user_input.begin(), user_input.end(), [](char c) {return c == '\t' || isspace(c); }), user_input.end());		// removing spaces and tabs
		if (user_input == "help") {
			output_help();
			return;
		}
		size_t equal_sign_pos = user_input.find('=');
		string delete_word = "delete";
		if (equal_sign_pos != user_input.npos) {
			assignment(user_input.substr(0, equal_sign_pos), user_input.substr(equal_sign_pos + 1, user_input.size()), false);
		}
		else if (user_input.find(delete_word) == 0) {
			try {
				vars.erase(user_input.substr(user_input.find(delete_word) + 6, user_input.size()));
			}
			catch (exception e){
				output_error(e);
			}
		}
		else {
			Polynom result = expression_calculate(user_input, false);
			if (result.size())
				output_result(result);
		}
	}

	Polynom test_execute(string input) {
		user_input = input;
		user_input.erase(remove_if(user_input.begin(), user_input.end(), [](char c) {return c == '\t' || isspace(c); }), user_input.end());
		size_t equal_sign_pos = user_input.find('=');
		Polynom result;
		if (equal_sign_pos != user_input.npos) {
			result = assignment(user_input.substr(0, equal_sign_pos), user_input.substr(equal_sign_pos + 1, user_input.size()), true);
		}
		else {
			result = expression_calculate(user_input, true);
		}
		return result;
	}
};

#endif