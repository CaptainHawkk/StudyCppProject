#include "ColorPrinter.h"
#include "RentalService.h"
#include "LoginService.h"
#pragma once
class RentalController:RentalService
{
public:
	void printMainMenuAdmin();
	int choseOption();
	void optionControllerAdmin(int option);
	void optionControllerUser(int option, User& user);
	void printMainMenuUser();
};

