#include "interface.h"
void Interface::instraction()
{
	std::cout << "Translator of arithmenic expressions  version 2" << std::endl;
	std::cout << "Features:" << std::endl;
	std::cout << "1. Calculate arithmetic expressions," << std::endl;
	std::cout << "2. Print a number or a variable," << std::endl;
	std::cout << "3. Create variables," << std::endl;
	std::cout << "4. Assign an expression values or numbers to variables," << std::endl;
	std::cout << "5. Perform calculations with variables," << std::endl;
	std::cout << "6. Assign an expression with variable to itself," << std::endl;
	std::cout << std::endl;
	std::cout << "1. To calculate the value of an arithmetic expression, you must enter it in a string without using spaces.\n"
		<< "2. If you make a mistake, the incorrect place will be highlighted in red.\n"
		<< "3. If a special character, such as a space, escape, or others, is entered, a blank space will appear.\n"
		<< "4. In case of an error, you need to delete the incorrect characters using the backspace key and continue entering the expression.\n"
		<< "5. To calculate the entered expression, you must press enter.\n"
		<< "6. If a red question mark appears when pressing Enter, you need to double-check the expression; there may be an error in it.\n"
		<< "7. When creating a variable, it is important to note that its name must consist of lowercase and uppercase Latin letters (one or more).\n"
		<< "8. To solve an expression with variables, you must first initialize all used variables, otherwise, you will see a message that the variable does not exist.\n"
		<< "9. To print a value of variable just type the name of variable.\n"
		<< "10. Follow the instructions when using the application.\n";
	std::cout << std::endl;
	std::cout << "Enter yout expression below:" << std::endl;
}
void Interface::print_ch(const char& ch)
{
	std::cout << ch;
}
void Interface:: set_color(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}
void Interface::print_red_ch(const char& ch)
{
	set_color(12);//red
	std::cout << ch;
	set_color(7);//white
}
void Interface::delete_ch()
{
	std::cout << "\b \b";
}
void Interface::clear_console()
{
	system("cls");
}