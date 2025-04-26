//#pragma once
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "parser.h"
#include "Stack.h"
#include "polinom.h"

template <class TCont>
class Calculator {

	int priority(string term) {
		int ret = 0;
		if (term == "+" || term == "-") {
			ret = 0;
		}
		if (term == "*" || term == "/") {
			ret = 1;
		}
		return ret;
	}
public:
	
	Polynom calculate(vector<Term> terms, TCont& cont) {
		Stack<Term> operands;
		vector<Term> polish_form;

		for (auto term : terms) {
			if (term.get_type() == Term::Type::POLYNOM) {
				polish_form.push_back(term);
			}
			else if (term.get_type() == Term::Type::VAR) {
				auto it = cont.find(term.get_value());
				if (it == cont.end()) {
					string error_text = "Runtime error: there is no such variable \'" + term.get_value() + "\'.";
					throw exception(error_text.c_str());
				}
				else {
					polish_form.push_back(it.value());
				}
			}
			else if (term.get_type() == Term::Type::CLOSE_BRACKET) {
				while (operands.top().get_type() != Term::Type::OPEN_BRACKET) {
					polish_form.push_back(operands.pop());
				}
				operands.pop();
			}
			else if (term.get_type() == Term::Type::OPEN_BRACKET) {
				operands.push(term);
			}
			else {
				if (operands.empty()) {
					operands.push(term);
				}
				else {
					while (!operands.empty()) {
						if (priority(operands.top().get_value()) >= priority(term.get_value()) && operands.top().get_type() != Term::Type::OPEN_BRACKET)
							polish_form.push_back(operands.pop());
						else break;
					}
					operands.push(term);
				}
			}
		}
		while (!operands.empty()) {
			polish_form.push_back(operands.pop());
		}

		Polynom res;
		Stack<Polynom> stack;
		for (auto elem : polish_form) {
			if (elem.get_type() == Term::Type::POLYNOM) {
				stack.push(elem.get_polynom());
			}
			else {
				Polynom second = stack.pop();
				Polynom first = stack.pop();
				char oper = elem.get_value()[0];
				switch (oper) {
				case '+':
					stack.push(first + second);
					break;
				case '-':
					stack.push(first - second);
					break;
				case '*':
					stack.push(first * second);
					break;
				case '/':
					if (second == Polynom(Monom(0, 0, 0, 0))) {
						throw exception("Runtime error: Cannot divide by zero.");
					}
					stack.push(first / second);
					break;
				}
			}
		}
		res = stack.top();
		return res;
	}
};

#endif