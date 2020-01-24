#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "RentalController.h"
#include "Magazine.h"
#include "LoginController.h"

using namespace std;

int main() {

	LoginController loginController = LoginController();

	string response;
	
	while (true) {
		loginController.loginInitializer();
	}
	/*while (true) {
		rentalController.printMainMenu();
		int number;
		number = rentalController.choseOption();
		rentalController.optionController(number);
		system("pause");
		system("cls");
	}*/

	return 0;
}