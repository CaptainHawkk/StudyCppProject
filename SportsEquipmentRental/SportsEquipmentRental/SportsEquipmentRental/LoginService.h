#pragma once
#include <iostream>
#include "User.h"
#include <optional>

using namespace std;

class LoginService
{
protected:
	void saveUserToFile(User& user);
	User getUserFromFile(fstream& userFileManager, string& line);
	void copyUserFromFile(fstream& userFileManager, string& line, User* user);
public:
	User findUserByMail(string mail);
};

