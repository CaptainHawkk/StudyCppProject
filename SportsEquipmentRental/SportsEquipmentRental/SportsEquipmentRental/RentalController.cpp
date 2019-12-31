#include "RentalController.h"
#include "Magazine.h"



void RentalController::printMainMenu()
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
	ColorPrinter::printTone(" 9. Find equipment by borrower name", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 10. Display borrowed equipment", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 11. Display not borrowed", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 12. Display magazine capacity", ColorPrinter::CYAN);
	ColorPrinter::printTone(" 13. Quit", ColorPrinter::CYAN);
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


void RentalController::optionController(int option)
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
		RentalController::findEquipmentByBorrowerName();
	} else if (option == 10) {
		RentalController::displayBorrowedEquipment();
	} else if (option == 11) {
		RentalController::displayNotBorrowedEquipment();
	} else if (option == 12) {
		RentalController::displayMagazineCapacity(&magazine);
	} else if (option == 13) {
		exit(1);
	} else {
		ColorPrinter::printTone("WRONG NUMBER", ColorPrinter::RED);
	}
}
