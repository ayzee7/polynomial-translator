#pragma once
#include <iostream>
#include <windows.h>
class Interface
{
public:
	static void print_ch(const char& ch);
	static void set_color(int color);
	static void print_red_ch(const char& ch);
	static void delete_ch();
	static void clear_console();
	static void instraction();
};