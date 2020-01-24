#include "LoginController.h"
#include <iostream>
#include <fstream>
#include "User.h"
#include <string>
#include "ColorPrinter.h"
#include "RentalController.h"
#include <stdlib.h>


using namespace std;

LoginController::LoginController()
{
	fstream userFileManager;
	userFileManager.open("users.txt", ios::in);

	bool adminAccountExist = false;
	User user;
	user = User();
	string line = "";

	if (userFileManager.is_open()) {
		while (getline(userFileManager, line)) {

			if (!line.empty()) {

				user = getUserFromFile(userFileManager, line);

				if (user.getRole().compare("ADMIN") == 0) {
					ColorPrinter::printTone("Inicialization complete, admin account exist", ColorPrinter::GREEN);
					adminAccountExist = true;
					break;
				}
			}
		}
	} else {
		ColorPrinter::printTone("Couldn't open file",ColorPrinter::RED);
	}

	userFileManager.close();

		if (!adminAccountExist)
		{
			ColorPrinter::printTone("Inicialization complete, admin account not found, creating new one",ColorPrinter::GREEN);
			user.~User();
			User user;
			user.setUser();
			user.setRole("ADMIN");
			this->saveUserToFile(user);
		} 
		user.~User();
	

	userFileManager.close();

	ColorPrinter::printTone("", ColorPrinter::DEFAULT,true);
	//check out data base for admin account
	//if not exist then create it
}

string LoginController::loginYourAccount(string mail, string password)
{

	User user = User();

	user = findUserByMail(mail);

	//cout << user << endl;

	if (user.getMail().compare("n") == 0) {
		ColorPrinter::printTone("Wrong login or password", ColorPrinter::RED);
		return "ABORT";
	}
	if (user.getMail().compare(mail) == 0 && user.getPassword().compare(password) == 0) {
		if (user.getRole().compare("ADMIN") == 0) {
			ColorPrinter::printTone("Loged as Admin", ColorPrinter::GREEN);
			ColorPrinter::printTone("Welcome", ColorPrinter::GREEN);
			Sleep(1000);
			system("CLS");
			return "ADMIN";
		}
		else {
			ColorPrinter::printTone("Loged as User", ColorPrinter::GREEN);
			ColorPrinter::printTone("Welcome!", ColorPrinter::GREEN);
			Sleep(1000);
			system("CLS");
			return "USER";
		}
	}
	else
	{
		ColorPrinter::printTone("Wrong login or password", ColorPrinter::RED);
		return "ABORT";
	}
}
	


void LoginController::loginInitializer()
{
	RentalController rentalController;

	int number = 0;
	int loginNumber = 0;

	string mail = "";
	string password = "";
	string response = "";

	printLoginMenu();
	loginNumber = rentalController.choseOption();
	if (loginNumber == 1) {


		ColorPrinter::printTone("write your e-mail", ColorPrinter::BLUE);
		cin >> mail;
		ColorPrinter::printTone("write your password", ColorPrinter::BLUE);
		cin >> password;
		response = this->loginYourAccount(mail, password);

		cout << response << endl;
		if (response.compare("ABORT") == 0) {
			return;
		}
		else if (response.compare("ADMIN") == 0) {
			while (number != 21) {
				rentalController.printMainMenuAdmin();
				number = rentalController.choseOption();
				rentalController.optionControllerAdmin(number);
				system("pause");
				system("CLS");
			}
		}
		else if (response.compare("USER") == 0) {
			User user = findUserByMail(mail);
			while (number != 5) {
				rentalController.printMainMenuUser();
				number = rentalController.choseOption();
				rentalController.optionControllerUser(number, user);
				system("pause");
				system("CLS");
			}
		}
	}
	else if (loginNumber == 2) {
		exit(1);
	}
	else {
		ColorPrinter::printTone("Wrong number", ColorPrinter::RED,true);
	}
}



void LoginController::printLoginMenu()
{
	ColorPrinter::printTone("----------------------------", ColorPrinter::GREEN);
	ColorPrinter::printTone("	Welcome", ColorPrinter::GREEN);
	ColorPrinter::printTone("----------------------------", ColorPrinter::GREEN);
	cout << endl;
	ColorPrinter::printTone("----------------------------", ColorPrinter::YELLOW);
	ColorPrinter::printTone("What do you want to do", ColorPrinter::YELLOW);
	ColorPrinter::printTone("----------------------------", ColorPrinter::YELLOW);
	cout << endl;
	ColorPrinter::printTone("----------------------------", ColorPrinter::CYAN);
	ColorPrinter::printTone("1. Login", ColorPrinter::CYAN);
	ColorPrinter::printTone("2. Quit", ColorPrinter::CYAN);
	ColorPrinter::printTone("----------------------------", ColorPrinter::CYAN);

}
