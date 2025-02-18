#pragma once

#include <iostream>
#include "parser.h"
#include <map>
#include "converter.h"
#include "calc.h"
#include "interface.h"
class Connect
{
public:
	static void connection();
	static void handler(std::map<std::string, double>& values, std::vector<Term>& terms);
};
