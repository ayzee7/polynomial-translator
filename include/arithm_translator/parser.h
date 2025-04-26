//#pragma once
#ifndef PARSER_H
#define PARSER_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <vector>
#include "polinom.h"

using namespace std;

class Term {
public:

	enum class Type {
		POLYNOM,
		OPERATOR,
		OPEN_BRACKET,
		CLOSE_BRACKET,
		VAR,
		VAR_ERROR,
		OPER_ERROR
	};

	Term(char c);
	Term(string s);
	Term(Polynom p);

	Type get_type();
	
	string get_value();

	Polynom get_polynom();

private:

	Type type;
	string value;
	Polynom polynom_value;
};

class Parser {
public:
	enum {
		STATE_INIT,
		STATE_OPERATOR,
		STATE_ERROR,
		STATE_NUM_DOUBLE,
		STATE_VAR,
		STATE_NUM_INT,
		STATE_X_POW,
		STATE_Y_POW,
		STATE_Z_POW,
		STATE_X_AWAIT_POW_SIGN,
		STATE_Y_AWAIT_POW_SIGN,
		STATE_Z_AWAIT_POW_SIGN,
		STATE_X_AFTER_POW,
		STATE_Y_AFTER_POW,
		STATE_Z_AFTER_POW,
	} STATES;

	void lvalue_analysis(string lvalue);

	void syntax_analysis(string expr);

	vector<Term> get_terms(string expr);
};

#endif