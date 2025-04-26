#include "interface.h"
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <ctime>
#include <chrono>

COORD pos = { 0, 0 };
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int startup() {
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
	int choice = 0;
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
	std::cout << "Help text." << std::endl;
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