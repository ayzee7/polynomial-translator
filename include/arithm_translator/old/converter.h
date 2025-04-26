#pragma once
#include <iostream>
#include "stack.h"
#include "parser.h"
#include <vector>
#include <map>
#include <string>

class Converter
{
	
public:
	static std::vector<Term> conv(std::vector<Term> inp, std::vector<double>& operands,std::map<std::string,double>& values);
};