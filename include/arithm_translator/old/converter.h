#pragma once
#include <iostream>
#include "stack.h"
#include "parser.h"
#include <vector>
#include <map>
#include <string>
#include "polinom.h"
class Converter
{
	
public:
	static std::vector<Term::Type> Converter::conv(std::vector<Term> inp, std::vector<Polynom>& operands, std::vector<std::string> operators, std::map<std::string, Polynom>& values);

};