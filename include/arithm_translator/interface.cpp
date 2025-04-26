#include "interface.h"
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <ctime>
#include <chrono>

COORD pos = { 0, 0 };
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

char startup() {
	auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::cout << "Polynomial Translator (" << strtok(std::ctime(&time), "\n") << ")" << std::endl;
	std::cout << "Choose container type:" << std::endl;
	std::cout << "1. Ordered Table" << std::endl;
	std::cout << "2. Unordered Table" << std::endl;
	std::cout << "3. AVL-Tree" << std::endl;
	std::cout << "4. RB-Tree" << std::endl;
	std::cout << "5. Address Hash Table" << std::endl;
	std::cout << "6. Chain Hash Table" << std::endl;
	std::cout << "Your input: ";
	char choice = 0;
	std::cin >> choice;
	return choice;
	
}

std::string await_input() {
	std::string user_input;
	SetConsoleTextAttribute(hConsole, 13);
	std::cout << ">>>";
	SetConsoleTextAttribute(hConsole, 7);
	std::getline(std::cin, user_input);
	return user_input;
}

void output_line(std::string str) {
	std::cout << str << std::endl;
}

void output_help() {
	std::cout << "Welcome to Polynomial Translator.\n"
		<< "This program is designed to calculate arithmetical expressions with polynoms.\n"
		<< "In order to start calculations, simply input the expression in console.\n" 
		<< "Program will output the result after you press ENTER.\n"
		<< "In expression, integer and floating-point numbers, arithmetical signs(\'+\', \'-\', \'*\', \'/\') and brackets can be used.\n"
		<< "To input a floating-point number, use \'.\' divider.\n"
		<< "You can use math variables in polynoms.\n"
		<< "In order to do so, use \'x\', \'y\' and \'z\' letters with corresponding powers, divided by \'^\'.\n"
		<< "Example: x^2 y^3 z^4\n"
		<< "You can use powers in range from 0 to 9.\n"
		<< "You do not have to use all math variables (if it has a power of 0) nor powers (if a math variable has a power of 1).\n"
		<< "You can use program variables to save result of calculated expression.\n"
		<< "To declare a program variable, you must provide it with a name and a value, divided by equal sign \'=\'.\n"
		<< "Example: a = 1\n"
		<< "You cannot save multiple values using one program variable.\n"
		<< "To delete declared program variable, use keyword \"delete\" with a name of a variable you need to delete.\n"
		<< "Example: delete a\n"
		<< "If expression contains errors, a message will appear in console, providing additional context." << std::endl;
}

void output_error(std::exception error) {
	SetConsoleTextAttribute(hConsole, 12);
	std::cout << error.what() << std::endl;
	SetConsoleTextAttribute(hConsole, 7);
}

void output_result(Polynom& result) {
	SetConsoleTextAttribute(hConsole, 11);
	result.printout();
	SetConsoleTextAttribute(hConsole, 7);
}