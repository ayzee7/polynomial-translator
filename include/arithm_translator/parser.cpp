#include "parser.h"

Term::Term(char c) {
	if (c == '(') {
		type = Type::OPEN_BRACKET;
	}
	else if (c == ')') {
		type = Type::CLOSE_BRACKET;
	}
	else if (c == '+' || c == '-' || c == '*' || c == '/') {
		type = Type::OPERATOR;
	}
	value = string{c};
}

Term::Term(string s) {
	if (s == "var_error") {
		type = Type::VAR_ERROR;
	}
	else if (s == "oper_error") {
		type = Type::OPER_ERROR;
	}
	else {
		type = Type::VAR;
	}
	value = s;
}

Term::Term(Polynom p) {
	type = Type::POLYNOM;
	polynom_value = p;
}

Term::Type Term::get_type() {
	return type;
}

string Term::get_value() {
	return value;
}

Polynom Term::get_polynom() {
	return polynom_value;
}

void Parser::lvalue_analysis(string lvalue) {
	if (!(isalpha(lvalue[0]) || lvalue[0] == '_')) {		//	Checks first symbol
		throw exception("Syntax error: invalid variable name.");

	}
	if (lvalue == string("delete")) {
		throw exception("Syntax error: cannot use keyword \"delete\" as a variable name.");
	}
	if (lvalue == string("help")) {
		throw exception("Syntax error: cannot use keyword \"help\" as a variable name.");
	}
	if (tolower(lvalue[0]) == 'x' || tolower(lvalue[0]) == 'y' || tolower(lvalue[0]) == 'z') {
		throw exception("Variable error: variable name cannot start with \'x\', \'y\' or \'z\'. Use \'_\' instead.");
	}
	for (char c : lvalue) {		//	Checks other symbols
		if (!(isalpha(c) || isdigit(c) || c == '_')) {
			throw exception("Syntax error: invalid variable name.");
		}
	}
}

void Parser::syntax_analysis(string expr) {
	if (expr.empty()) {
		throw exception("Syntax error: expression cannot be empty.");
	}
	int state = STATE_INIT;
	int bracket_counter = 0;
	for (char c : expr) {
		switch (state) {
		case STATE_INIT:
			if (c == '(') {
				bracket_counter++;
			}
			else if (isdigit(c)) {							//is a number
				state = STATE_NUM_INT;
			}
			else if (isalpha(c) || c == '_') {
				if (c == 'x' || c == 'X') {
					state = STATE_X_AWAIT_POW_SIGN;
				}
				else if (c == 'y' || c == 'Y') {
					state = STATE_Y_AWAIT_POW_SIGN;
				}
				else if (c == 'z' || c == 'Z') {
					state = STATE_Z_AWAIT_POW_SIGN;
				}
				else {
					state = STATE_VAR;
				}
			}
			else {
				state = STATE_ERROR;
			}
			break;
		case STATE_OPERATOR:
			if (c == ')') {
				bracket_counter--;
				if (bracket_counter < 0) {
					state = STATE_ERROR;
				}
				else {
					state = STATE_OPERATOR;
				}
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/') {
				state = STATE_INIT;
			}
			else {
				state = STATE_ERROR;
			}
			break;
		case STATE_NUM_DOUBLE:
			if (isdigit(c)) {
				state = STATE_NUM_DOUBLE;
			}
			else if (c == 'x' || c == 'X') {
				state = STATE_X_AWAIT_POW_SIGN;
			}
			else if (c == 'y' || c == 'Y') {
				state = STATE_Y_AWAIT_POW_SIGN;
			}
			else if (c == 'z' || c == 'Z') {
				state = STATE_Z_AWAIT_POW_SIGN;
			}
			else if (c == ')') {
				bracket_counter--;
				if (bracket_counter < 0) {
					state = STATE_ERROR;
				}
				else {
					state = STATE_OPERATOR;
				}
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/') {
				state = STATE_INIT;
			}
			else {
				state = STATE_ERROR;
			}
			break;
		case STATE_VAR:
			if (isalpha(c) || c == '_' || isdigit(c)) {
				state = STATE_VAR;
			}
			else if (c == ')') {
				bracket_counter--;
				if (bracket_counter < 0) {
					state = STATE_ERROR;
				}
				else {
					state = STATE_OPERATOR;
				}
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/') {
				state = STATE_INIT;
			}
			else {
				state = STATE_ERROR;
			}
			break;
		case STATE_NUM_INT:
			if (c == ')') {
				bracket_counter--;
				if (bracket_counter < 0) {
					state = STATE_ERROR;
				}
				else {
					state = STATE_OPERATOR;
				}
			}
			else if (isdigit(c)) {
				state = STATE_NUM_INT;
			}
			else if (c == '.') {
				state = STATE_NUM_DOUBLE;
			}
			else if (c == 'x' || c == 'X') {
				state = STATE_X_AWAIT_POW_SIGN;
			}
			else if (c == 'y' || c == 'Y') {
				state = STATE_Y_AWAIT_POW_SIGN;
			}
			else if (c == 'z' || c == 'Z') {
				state = STATE_Z_AWAIT_POW_SIGN;
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/') {
				state = STATE_INIT;
			}
			else {
				state = STATE_ERROR;
			}
			break;
		case STATE_X_AWAIT_POW_SIGN:
			if (c == '^') {
				state = STATE_X_POW;
			}
			else if (c == 'y' || c == 'Y') {
				state = STATE_Y_AWAIT_POW_SIGN;
			}
			else if (c == 'z' || c == 'Z') {
				state = STATE_Z_AWAIT_POW_SIGN;
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/') {
				state = STATE_INIT;
			}
			else if (c == ')') {
				bracket_counter--;
				if (bracket_counter < 0) {
					state = STATE_ERROR;
				}
				else {
					state = STATE_OPERATOR;
				}
			}
			else {
				state = STATE_ERROR;
			}
			break;
		case STATE_X_POW:
			if (isdigit(c)) {
				state = STATE_X_AFTER_POW;
			}
			else {
				state = STATE_ERROR;
			}
			break;
		case STATE_X_AFTER_POW :
			if (c == 'y' || c == 'Y') {
				state = STATE_Y_AWAIT_POW_SIGN;
			}
			else if (c == 'z' || c == 'Z') {
				state = STATE_Z_AWAIT_POW_SIGN;
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/') {
				state = STATE_INIT;
			}
			else if (c == ')') {
				bracket_counter--;
				if (bracket_counter < 0) {
					state = STATE_ERROR;
				}
				else {
					state = STATE_OPERATOR;
				}
			}
			else {
				state = STATE_ERROR;
			}
			break;
		case STATE_Y_AWAIT_POW_SIGN:
			if (c == '^') {
				state = STATE_Y_POW;
			}
			else if (c == 'z' || c == 'Z') {
				state = STATE_Z_AWAIT_POW_SIGN;
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/') {
				state = STATE_INIT;
			}
			else if (c == ')') {
				bracket_counter--;
				if (bracket_counter < 0) {
					state = STATE_ERROR;
				}
				else {
					state = STATE_OPERATOR;
				}
			}
			else {
				state = STATE_ERROR;
			}
			break;
		case STATE_Y_POW:
			if (isdigit(c)) {
				state = STATE_Y_AFTER_POW;
			}
			else {
				state = STATE_ERROR;
			}
			break;
		case STATE_Y_AFTER_POW:
			if (c == 'z' || c == 'Z') {
				state = STATE_Z_AWAIT_POW_SIGN;
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/') {
				state = STATE_INIT;
			}
			else if (c == ')') {
				bracket_counter--;
				if (bracket_counter < 0) {
					state = STATE_ERROR;
				}
				else {
					state = STATE_OPERATOR;
				}
			}
			else {
				state = STATE_ERROR;
			}
			break;
		case STATE_Z_AWAIT_POW_SIGN:
			if (c == '^') {
				state = STATE_Z_POW;
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/') {
				state = STATE_INIT;
			}
			else if (c == ')') {
				bracket_counter--;
				if (bracket_counter < 0) {
					state = STATE_ERROR;
				}
				else {
					state = STATE_OPERATOR;
				}
			}
			else {
				state = STATE_ERROR;
			}
			break;
		case STATE_Z_POW:
			if (isdigit(c)) {
				state = STATE_OPERATOR;
			}
			else {
				state = STATE_ERROR;
			}
			break;
		case STATE_Z_AFTER_POW:
			if (c == ')') {
				bracket_counter--;
				if (bracket_counter < 0) {
					state = STATE_ERROR;
				}
				else {
					state = STATE_OPERATOR;
				}
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/') {
				state = STATE_INIT;
			}
			else {
				state = STATE_ERROR;
			}
			break;
		case STATE_ERROR:
			throw exception("Syntax error: invalid expression.");
		}

	}
	if (bracket_counter) {
		state = STATE_ERROR;
	}
	if (state == STATE_INIT || state == STATE_X_POW || state == STATE_Y_POW || state == STATE_Z_POW) {
		state = STATE_ERROR;
	}
	if (state == STATE_ERROR) {
		throw exception("Syntax error: invalid expression.");
	}
}

vector<Term> Parser::get_terms(string expr) {
	int state = STATE_INIT;
	vector<Term> terms;
	string term;

	double coef = 0;
	int x_pow = 0, y_pow = 0, z_pow = 0;

	for (char c : expr) {
		switch (state) {
		case STATE_INIT:
			if (c == '(') {
				terms.push_back(Term(c));
			}
			else if (isdigit(c)) {		//is a number
				term.push_back(c);
				state = STATE_NUM_INT;
			}
			else if (isalpha(c) || c == '_') {
				if (c == 'x' || c == 'X') {
					term.push_back('1');
					coef = 1;
					state = STATE_X_AWAIT_POW_SIGN;
				}
				else if (c == 'y' || c == 'Y') {
					term.push_back('1');
					coef = 1;
					state = STATE_Y_AWAIT_POW_SIGN;
				}
				else if (c == 'z' || c == 'Z') {
					term.push_back('1');
					coef = 1;
					state = STATE_Z_AWAIT_POW_SIGN;
				}
				else {
					term.push_back(c);
					state = STATE_VAR;
				}
			}
			break;
		case STATE_OPERATOR:
			if (c == ')') {
				if (!term.empty())
					terms.push_back(Term(term));
				term.clear();
				terms.push_back(Term(c));
				state = STATE_OPERATOR;
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
				if (!term.empty())
					terms.push_back(Term(term));
				term.clear();
				terms.push_back(Term(c));
				state = STATE_INIT;
			}
			break;
		case STATE_NUM_DOUBLE:
			if (isdigit(c)) {
				term.push_back(c);
				state = STATE_NUM_DOUBLE;
			}
			else if (c == 'x' || c == 'X') {
				coef = stod(term);
				state = STATE_X_AWAIT_POW_SIGN;
			}
			else if (c == 'y' || c == 'Y') {
				coef = stod(term);
				state = STATE_Y_AWAIT_POW_SIGN;
			}
			else if (c == 'z' || c == 'Z') {
				coef = stod(term);
				state = STATE_Z_AWAIT_POW_SIGN;
			}
			else if (c == ')') {
				if (!term.empty()) {
					coef = stod(term);
					Polynom p(Monom(coef, x_pow, y_pow, z_pow));
					terms.push_back(Term(p));
					coef = 0;
				}
				term.clear();
				terms.push_back(Term(c));
				state = STATE_OPERATOR;
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
				if (!term.empty()) {
					coef = stod(term);
					Polynom p(Monom(coef, x_pow, y_pow, z_pow));
					terms.push_back(Term(p));
					coef = 0;
				}
				term.clear();
				terms.push_back(Term(c));
				state = STATE_INIT;
			}
			break;
		case STATE_VAR:
			if (isalpha(c) || c == '_' || isdigit(c)) {
				term.push_back(c);
				state = STATE_VAR;
			}
			else if (c == ')') {
				if (!term.empty())
					terms.push_back(Term(term));
				term.clear();
				terms.push_back(Term(c));
				state = STATE_OPERATOR;
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
				if (!term.empty())
					terms.push_back(Term(term));
				term.clear();
				terms.push_back(Term(c));
				state = STATE_INIT;
			}
			break;
		case STATE_NUM_INT:
			if (c == ')') {
				if (!term.empty()) {
					coef = stod(term);
					Polynom p(Monom(coef, x_pow, y_pow, z_pow));
					terms.push_back(Term(p));
					coef = 0;
				}
				term.clear();
				terms.push_back(Term(c));
				state = STATE_OPERATOR;
			}
			else if (c == 'x' || c == 'X') {
				coef = stod(term);
				state = STATE_X_AWAIT_POW_SIGN;
			}
			else if (c == 'y' || c == 'Y') {
				coef = stod(term);
				state = STATE_Y_AWAIT_POW_SIGN;
			}
			else if (c == 'z' || c == 'Z') {
				coef = stod(term);
				state = STATE_Z_AWAIT_POW_SIGN;
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
				if (!term.empty()) {
					coef = stod(term);
					Polynom p(Monom(coef, x_pow, y_pow, z_pow));
					terms.push_back(Term(p));
					coef = 0;
				}
				term.clear();
				terms.push_back(Term(c));
				state = STATE_INIT;
			}
			else if (isdigit(c)) {
				term.push_back(c);
				state = STATE_NUM_INT;
			}
			else if (c == '.') {
				term.push_back(c);
				state = STATE_NUM_DOUBLE;
			}
			break;
		case STATE_X_AWAIT_POW_SIGN:
			if (c == '^') {
				state = STATE_X_POW;
			}
			else if (c == 'y' || c == 'Y') {
				x_pow = 1;
				state = STATE_Y_AWAIT_POW_SIGN;
			}
			else if (c == 'z' || c == 'Z') {
				x_pow = 1;
				state = STATE_Z_AWAIT_POW_SIGN;
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
				if (!term.empty()) {
					x_pow = 1;
					Polynom p(Monom(coef, x_pow, y_pow, z_pow));
					terms.push_back(Term(p));
					coef = 0;
					x_pow = 0;
				}
				term.clear();
				terms.push_back(Term(c));
				state = STATE_INIT;
			}
			else if (c == ')') {
				if (!term.empty()) {
					x_pow = 1;
					Polynom p(Monom(coef, x_pow, y_pow, z_pow));
					terms.push_back(Term(p));
					coef = 0;
					x_pow = 0;
				}
				term.clear();
				terms.push_back(Term(c));
				state = STATE_OPERATOR;
			}
			break;
		case STATE_X_POW:
			x_pow = c - '0';
			state = STATE_X_AFTER_POW;
			break;
		case STATE_X_AFTER_POW:
			if (c == 'y' || c == 'Y') {
				state = STATE_Y_AWAIT_POW_SIGN;
			}
			else if (c == 'z' || c == 'Z') {
				state = STATE_Z_AWAIT_POW_SIGN;
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
				if (!term.empty()) {
					Polynom p(Monom(coef, x_pow, y_pow, z_pow));
					terms.push_back(Term(p));
					coef = 0;
					x_pow = 0;
				}
				term.clear();
				terms.push_back(Term(c));
				state = STATE_INIT;
			}
			else if (c == ')') {
				if (!term.empty()) {
					Polynom p(Monom(coef, x_pow, y_pow, z_pow));
					terms.push_back(Term(p));
					coef = 0;
					x_pow = 0;
				}
				term.clear();
				terms.push_back(Term(c));
				state = STATE_OPERATOR;
			}
			break;
		case STATE_Y_AWAIT_POW_SIGN:
			if (c == '^') {
				state = STATE_Y_POW;
			}
			else if (c == 'z' || c == 'Z') {
				y_pow = 1;
				state = STATE_Z_AWAIT_POW_SIGN;
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
				if (!term.empty()) {
					y_pow = 1;
					Polynom p(Monom(coef, x_pow, y_pow, z_pow));
					terms.push_back(Term(p));
					coef = 0;
					x_pow = 0;
					y_pow = 0;
				}
				term.clear();
				terms.push_back(Term(c));
				state = STATE_INIT;
			}
			else if (c == ')') {
				if (!term.empty()) {
					y_pow = 1;
					Polynom p(Monom(coef, x_pow, y_pow, z_pow));
					terms.push_back(Term(p));
					coef = 0;
					x_pow = 0;
					y_pow = 0;
				}
				term.clear();
				terms.push_back(Term(c));
				state = STATE_OPERATOR;
			}
			break;
		case STATE_Y_POW:
			y_pow = c - '0';
			state = STATE_Y_AFTER_POW;
			break;
		case STATE_Y_AFTER_POW:
			if (c == 'z' || c == 'Z') {
				state = STATE_Z_AWAIT_POW_SIGN;
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
				if (!term.empty()) {
					Polynom p(Monom(coef, x_pow, y_pow, z_pow));
					terms.push_back(Term(p));
					coef = 0;
					x_pow = 0;
					y_pow = 0;
				}
				term.clear();
				terms.push_back(Term(c));
				state = STATE_INIT;
			}
			else if (c == ')') {
				if (!term.empty()) {
					Polynom p(Monom(coef, x_pow, y_pow, z_pow));
					terms.push_back(Term(p));
					coef = 0;
					x_pow = 0;
					y_pow = 0;
				}
				term.clear();
				terms.push_back(Term(c));
				state = STATE_OPERATOR;
			}
			break;
		case STATE_Z_AWAIT_POW_SIGN:
			if (c == '^') {
				state = STATE_Z_POW;
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
				if (!term.empty()) {
					z_pow = 1;
					Polynom p(Monom(coef, x_pow, y_pow, z_pow));
					terms.push_back(Term(p));
					coef = 0;
					x_pow = 0;
					y_pow = 0;
					z_pow = 0;
				}
				term.clear();
				terms.push_back(Term(c));
				state = STATE_INIT;
			}
			else if (c == ')') {
				if (!term.empty()) {
					z_pow = 1;
					Polynom p(Monom(coef, x_pow, y_pow, z_pow));
					terms.push_back(Term(p));
					coef = 0;
					x_pow = 0;
					y_pow = 0;
					z_pow = 0;
				}
				term.clear();
				terms.push_back(Term(c));
				state = STATE_OPERATOR;
			}
			break;
		case STATE_Z_POW:
		{
			z_pow = c - '0';
			Polynom p(Monom(coef, x_pow, y_pow, z_pow));
			terms.push_back(Term(p));
			coef = 0;
			x_pow = 0;
			y_pow = 0;
			z_pow = 0;
			term.clear();
			state = STATE_Z_AFTER_POW;
			break;
		}
		case STATE_Z_AFTER_POW:
			if (c == ')') {
				terms.push_back(Term(c));
				state = STATE_OPERATOR;
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
				terms.push_back(Term(c));
				state = STATE_INIT;
			}
			break;
		}
	}
	if (!term.empty()) {
		if (state == STATE_NUM_DOUBLE || state == STATE_NUM_INT) {
			coef = stod(term);
			Polynom p(Monom(coef, x_pow, y_pow, z_pow));
			terms.push_back(Term(p));
		}
		else if (state == STATE_X_AWAIT_POW_SIGN) {
			x_pow = 1;
			Polynom p(Monom(coef, x_pow, y_pow, z_pow));
			terms.push_back(Term(p));
		}
		else if (state == STATE_Y_AWAIT_POW_SIGN) {
			y_pow = 1;
			Polynom p(Monom(coef, x_pow, y_pow, z_pow));
			terms.push_back(Term(p));
		}
		else if (state == STATE_Z_AWAIT_POW_SIGN) {
			z_pow = 1;
			Polynom p(Monom(coef, x_pow, y_pow, z_pow));
			terms.push_back(Term(p));
		}
		else if (state == STATE_X_AFTER_POW || state == STATE_Y_AFTER_POW || state == STATE_Z_AFTER_POW) {
			Polynom p(Monom(coef, x_pow, y_pow, z_pow));
			terms.push_back(Term(p));
		}
		else {
			terms.push_back(Term(term));
		}
	}
	return terms;
}