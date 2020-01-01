#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "RentalController.h"
#include "Magazine.h"

using namespace std;

int main() {

	RentalController rentalController;
	
	while (true) {
		rentalController.printMainMenu();
		int number;
		number = rentalController.choseOption();
		rentalController.optionController(number);
		system("pause");
		system("cls");
	}

	return 0;
}