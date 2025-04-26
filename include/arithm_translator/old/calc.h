#pragma once
#include "stack.h"
#include <vector>
#include <map>
#include "parser.h"
#include "polinom.h"
class Calc
{
public:
	static Polynom Calculate(std::vector<Term::Type>& post_str, std::vector<Polynom>& operands, std::vector<std::string>& operators);
};