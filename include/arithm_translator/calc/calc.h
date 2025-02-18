#pragma once
#include "stack.h"
#include <vector>
#include <map>
#include "parser.h"
class Calc
{
public:
	static double Calculate(std::vector<Term>& post_str, std::vector<double>& operands);
};