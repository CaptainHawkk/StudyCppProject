#include "RentalController.h"
#include "Magazine.h"
#include "LoginController.h"



void RentalController::printMainMenuAdmin()
{
	ColorPrinter::printTone("		   MAIN MENU", ColorPrinter::GREEN);
	ColorPrinter::printTone("----------------------------------------------", ColorPrinter::GREEN);
	cout << endl;

	ColorPrinter::printTone("          CHOSE YOUR OPTION", ColorPrinter::YELLOW);
	ColorPrinter::printTone("-------------------------------------", ColorPrinter::YELLOW);
	cout << endl;

	cout << endl;
	ColorPrinter::printTone("------------------------------------", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 1. Add new equipment", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 2. Update equipment", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 3. Delete equipment", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 4. Display equipment", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 5. Display rents with 30 days passed", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 6. Handle the refund", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 7. Rent equipment", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 8. Find equipment by name", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 9. Find equipment by borrower mail", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 10. Find equipment by type", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 11. Find equipment with cost higher than given", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 12. Find equipment with cost lower than given", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 13. Display borrowed equipment", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 14. Display not borrowed", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 15. Display magazine capacity", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 16. Add new User", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 17. Update User", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 18. Display user by e-mail", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 19. Delete user by id", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 20. Display all users", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 21. Quit", ColorPrinter::CYAN);
	ColorPrinter::printTone("--------------------------------------", ColorPrinter::CYAN);
	cout << endl;
}	

int RentalController::choseOption()
{
	int number;
	ColorPrinter::printTone("WRITE A NUMBER", ColorPrinter::PURPLE, false);
	cin >> number;

	return number;
}


void RentalController::optionControllerAdmin(int option)
{
	Magazine magazine = Magazine();
	
	if (option == 1) {
		RentalController::addNewEquipment(magazine); 
	} else if (option == 2) {
		RentalController::updateEquipment(magazine); 
	} else if (option == 3) {
		RentalController::deleteEquipment(magazine); 
	} else if (option == 4) {
		RentalController::displayEquipment(); 
	} else if (option == 5) {
		RentalController::displayRentsWith30DayPassed(); 
	} else if (option == 6) {
		RentalController::handleRefund(); 
	} else if (option == 7) {
		RentalController::handleRent();
	} else if (option == 8) {
		RentalController::findEquipmentByName(); 
	} else if (option == 9) {
		RentalController::findEquipmentByBorrowerMail(); 
	} else if (option == 10) {
		RentalController::findEquipmentByType(); 
	}else if (option == 11) {
		RentalController::findEquipmentWithCostHigherThan(); 
	}else if (option == 12) {
		RentalController::findEquipmentWithCostLowerThan(); 
	}else if (option == 13) {
		RentalController::displayBorrowedEquipment(); 
	} else if (option == 14) {
		RentalController::displayNotBorrowedEquipment(); 
	} else if (option == 15) {
		RentalController::displayMagazineCapacity(&magazine); 
	} else if (option == 16) {
		RentalController::addUserToFile();
	} else if (option == 17) {
		RentalController::updateUser();
	} else if (option == 18) {
		RentalController::displayUserByMail();
	} else if (option == 19) {
		RentalController::deleteUserByMail();
	} else if (option == 20) {
		RentalController::displayAllUsers();
	} else if (option == 21) {
		ColorPrinter::printTone("Loging out", ColorPrinter::CYAN);
		ColorPrinter::printTone("Good bye!", ColorPrinter::CYAN);
		Sleep(2500);
		return;
	} else {
		ColorPrinter::printTone("WRONG NUMBER", ColorPrinter::RED);
	}
}


void RentalController::optionControllerUser(int option, User& user)
{
	if (option == 1) {
		cout << user;
	} else if (option == 2) {
		RentalController::updateUserValues(user);
	} else if (option == 3) {
		RentalController::displayUserEquipment(user);
	} else if (option == 4) {
		RentalController::displayNotBorrowedEquipment();
	} else if (option == 5) {
		ColorPrinter::printTone("Loging out", ColorPrinter::CYAN);
		ColorPrinter::printTone("Good bye!", ColorPrinter::CYAN);
		Sleep(2500);
	}
}


void RentalController::printMainMenuUser()
{

	ColorPrinter::printTone("		   MAIN MENU", ColorPrinter::GREEN,true);
	ColorPrinter::printTone("----------------------------------------------", ColorPrinter::GREEN);
	cout << endl;

	ColorPrinter::printTone("          CHOSE YOUR OPTION", ColorPrinter::YELLOW);
	ColorPrinter::printTone("-------------------------------------", ColorPrinter::YELLOW);
	cout << endl;

	cout << endl;
	ColorPrinter::printTone("------------------------------------", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 1. Display your details", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 2. Update your account", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 3. Display your borrowed equipment", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 4. Display equipment you can borrow", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 5. Logout", ColorPrinter::CYAN);
	ColorPrinter::printTone("------------------------------------", ColorPrinter::CYAN);
	cout << endl;
}
