#pragma once
#include "LoginService.h"
#include <optional>

class LoginController:LoginService
{

public:
	LoginController();
	string loginYourAccount(string mail, string password);
	void loginInitializer();
	void printLoginMenu();
};

