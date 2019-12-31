#define _CRT_SECURE_NO_WARNINGS
#include "ColorPrinter.h"

void ColorPrinter::printTone(const string text, const Color color, bool clearConsole)
{
	const HANDLE consoleHandler = GetStdHandle(STD_OUTPUT_HANDLE);
	const int white = Color::DEFAULT;
	const int number = color;

	if (clearConsole) {
		system("CLS");
	}

	SetConsoleTextAttribute(consoleHandler, color);
	cout << text << endl;
	SetConsoleTextAttribute(consoleHandler, white);
}

