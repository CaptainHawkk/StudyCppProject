#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <windows.h>
#include <iostream>

using namespace std;

class ColorPrinter
{
public:
	enum Color : int {
		ORANGE = 6,
		GREY = 8,
		BLUE = 9,
		GREEN = 10,
		CYAN = 11,
		RED = 12,
		PURPLE = 13,
		YELLOW = 14,
		DEFAULT = 15
	};
	
	static void printTone(const string text, const Color color = Color::DEFAULT, bool clearConsole = false);
};