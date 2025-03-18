#include "interface.h"

void Interface::print_ch(const char& ch)
{
	std::cout << ch;
}

void Interface::clear_console()
{
	system("cls");
}