//#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H


#include "polinom.h"
#include <exception>
#include <string>

int startup();

std::string await_input();

void output_line(std::string str);

void output_help();

void output_error(std::exception error);

void output_result(Polynom& result);

#endif