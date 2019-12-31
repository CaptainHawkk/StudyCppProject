#include "ColorPrinter.h"
#include "RentalService.h"
#pragma once
class RentalController:RentalService
{
public:
	void printMainMenu();
	int choseOption();
	void optionController(int option);

	
};

