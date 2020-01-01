#include "RentalService.h"
#include "Magazine.h"
#include "Equipment.h"
#include "ColorPrinter.h"
#include <fstream>


void RentalService::addNewEquipment(Magazine& magazine)
{
	if (magazine.magazineIsFull()) {
		ColorPrinter::printTone("Magazine is full, can't add more equipment", ColorPrinter::RED);
		return;
	}

	fstream equipmentSaver;
	equipmentSaver.open("equipment.txt",ios::out | ios::app);

	if (equipmentSaver.is_open()) {

		Equipment equipment;
		equipment.setEquipmentData();
		equipment.setId(magazine.getActualCapacity() + 1);
		this->saveEquipmentToFile(equipment, equipmentSaver);
		magazine.incrementActualCapacity();
		ColorPrinter::printTone("Equipment added", ColorPrinter::GREEN);
		equipmentSaver.close();
		equipment.~Equipment();
	} else {
		ColorPrinter::printTone("Couldn't open file", ColorPrinter::RED);
	}
}

void RentalService::displayMagazineCapacity(Magazine* magazine) {
	
	if (magazine->getActualCapacity() == magazine->getMaximumCapacity()) {
		ColorPrinter::printTone("Magazine is full", ColorPrinter::RED);
	} else if (magazine->getActualCapacity() > 40) {
		ColorPrinter::printTone("Magazine is almost full", ColorPrinter::ORANGE);
		ColorPrinter::printTone("Quantity: " + to_string(magazine->getActualCapacity()) + "/" + to_string(magazine->getMaximumCapacity()), ColorPrinter::ORANGE);
	} else if (magazine->getActualCapacity() > 0) {
		ColorPrinter::printTone("Magazine have a lot of space", ColorPrinter::BLUE);
		ColorPrinter::printTone("Quantity: " + to_string(magazine->getActualCapacity()) + "/" + to_string(magazine->getMaximumCapacity()), ColorPrinter::BLUE);
	} else if(magazine->getActualCapacity() == 0){
		ColorPrinter::printTone("Magazine is empty", ColorPrinter::GREEN);
	}
}

void RentalService::updateEquipment(Magazine& magazine)
{
	fstream equipmentFileManager;
		equipmentFileManager.open("equipment.txt", ios::in);

		if (equipmentFileManager.is_open()) {
			unsigned long int id;

			ColorPrinter::printTone("Update equipment", ColorPrinter::BLUE);
			ColorPrinter::printTone("Write equipment id", ColorPrinter::BLUE);
			std::cin >> id;
			
			Equipment equipment = updateEquipmentValues(id);

			this->updateEquipmentToFileOptional(equipment, equipmentFileManager);
		} else {
			ColorPrinter::printTone("Couldn't open file", ColorPrinter::RED);
		}

}

void RentalService::deleteEquipment(Magazine& magazine)
{
	fstream equipmentFileManager;
	equipmentFileManager.open("equipment.txt", ios::in);

	if (equipmentFileManager.is_open()) {
		unsigned long int id;

		ColorPrinter::printTone("Delete equipment", ColorPrinter::BLUE);
		ColorPrinter::printTone("Write equipment id", ColorPrinter::BLUE);
		std::cin >> id;
		
		bool decrementCapacity = deleteEquipmentById(id,equipmentFileManager);

		if (decrementCapacity) {
			magazine.decrementActualCapacity();
		}
	} else {
		ColorPrinter::printTone("Couldn't open file", ColorPrinter::RED);
	}
}

void RentalService::displayEquipment()
{
	fstream equipmenFileManager;
	equipmenFileManager.open("equipment.txt", ios::in);

	if (equipmenFileManager.is_open()) {

		string line = "";
		string day = "";
		string month = "";
		string year = "";

		while (getline(equipmenFileManager, line)) {

			if (!line.empty()) {
				cout << "Id: " << line << endl;

				getline(equipmenFileManager, line);
				cout << "Name: " << line << endl;

				getline(equipmenFileManager, line);
				cout << "Type: " << line << endl;

				getline(equipmenFileManager, line);
				cout << "Borrower: " << line << endl;


				getline(equipmenFileManager, line);
				cout << "Rental price :" << line << endl;

				getline(equipmenFileManager, day);
				getline(equipmenFileManager, month);
				getline(equipmenFileManager, year);
				cout << "Rental date: " << day << "-" << month << "-" << year << endl;

				getline(equipmenFileManager, line);
				cout << "Rented: " << line << endl << endl;
			}
		}
	}
	else {
		ColorPrinter::printTone("Couldn't open file", ColorPrinter::RED);
	}
	equipmenFileManager.close();
}

void RentalService::displayRentsWith30DayPassed()
{
	fstream equipmentFileManager;
	equipmentFileManager.open("equipment.txt", ios::in);

	if (equipmentFileManager.is_open()) {

		int entityCounter = 0;
		string line = "";
		string day = "";
		string month = "";
		string year = "";

		while (getline(equipmentFileManager, line)) {

			if (!line.empty()) {
				Equipment equipment = Equipment();

				getline(equipmentFileManager, line);
				equipment.setName(line);

				getline(equipmentFileManager, line);
				equipment.setType(line);

				getline(equipmentFileManager, line);
				equipment.setBorrower(line);

				getline(equipmentFileManager, line);
				equipment.setRentalPrice(stoi(line));

				getline(equipmentFileManager, day);
				getline(equipmentFileManager, month);
				getline(equipmentFileManager, year);
				equipment.setRentalDate(Date(stoi(day), stoi(month), stoi(year)));

				getline(equipmentFileManager, line);
				equipment.setRented(stoi(line));

				if (equipment.getRented() && Date::the30DayHasPassed(equipment.getRentalDate()) && equipment.getRentalDate().getYear() != 0) {
					cout << "Name: " << equipment.getName() << endl;
					cout << "Borrower: " << equipment.getBorrower() << endl;
					cout << "Rental price: " << equipment.getRentalPrice() << endl;
					cout << "Rental date: " << equipment.getRentalDate().getDay() << "-" <<
						equipment.getRentalDate().getMonth() << "-" <<
						equipment.getRentalDate().getYear() << endl;
					equipment.~Equipment();
				}
			}
		} if (entityCounter == 0) {
			ColorPrinter::printTone("no rents longer than 30 days in database", ColorPrinter::GREEN);
		}
	} else {
		ColorPrinter::printTone("Couldn't open file", ColorPrinter::RED);
	}
	equipmentFileManager.close();
}

void RentalService::handleRefund()
{
	fstream equipmentFileManager;
	equipmentFileManager.open("equipment.txt", ios::in);

	if (equipmentFileManager.is_open()) {
		unsigned long int id;

		ColorPrinter::printTone("Rent equipment", ColorPrinter::BLUE);
		ColorPrinter::printTone("Write equipment id", ColorPrinter::BLUE);
		std::cin >> id;

		Equipment equipment = updateRefundValues(id);

		this->updateEquipmentToFileOptional(equipment, equipmentFileManager);
	}
	else {
		ColorPrinter::printTone("Couldn't open file", ColorPrinter::RED);
	}
}

void RentalService::handleRent()
{
	fstream equipmentFileManager;
	equipmentFileManager.open("equipment.txt", ios::in);

	if (equipmentFileManager.is_open()) {
		unsigned long int id;

		ColorPrinter::printTone("Rent equipment", ColorPrinter::BLUE);
		ColorPrinter::printTone("Write equipment id", ColorPrinter::BLUE);
		std::cin >> id;

		Equipment equipment = updateRentValues(id);

		this->updateEquipmentToFileOptional(equipment, equipmentFileManager);
	} else {
		ColorPrinter::printTone("Couldn't open file", ColorPrinter::RED);
	}
}

void RentalService::findEquipmentByName()
{
	fstream equipmentFileManager;
	equipmentFileManager.open("equipment.txt", ios::in);

	if (equipmentFileManager.is_open()) {
		string name;

		ColorPrinter::printTone("Find equipment by name", ColorPrinter::BLUE);
		ColorPrinter::printTone("Write equipment name", ColorPrinter::BLUE);
		std::cin >> name;

		this->displayEquipmentByName(name, equipmentFileManager);
		equipmentFileManager.close();

	} else {
		ColorPrinter::printTone("Couldn't open file", ColorPrinter::RED);
	}
}

void RentalService::findEquipmentByBorrowerName()
{
	fstream equipmentFileManager;
	equipmentFileManager.open("equipment.txt", ios::in);

	if (equipmentFileManager.is_open()) {
		string borrowerName;

		ColorPrinter::printTone("Find equipment by name", ColorPrinter::BLUE);
		ColorPrinter::printTone("Write equipment name", ColorPrinter::BLUE);
		std::cin >> borrowerName;

		this->displayEquipmentByBorrowerName(borrowerName, equipmentFileManager);
		equipmentFileManager.close();
	}
	else {
		ColorPrinter::printTone("Couldn't open file", ColorPrinter::RED);
	}
}

void RentalService::displayBorrowedEquipment()
{
	fstream equipmentFileManager;
	equipmentFileManager.open("equipment.txt", ios::in);

	if (equipmentFileManager.is_open()) {

		int entityCounter = 0;
		string line = "";
		string day = "";
		string month = "";
		string year = "";

		while (getline(equipmentFileManager, line)) {

			if (!line.empty()) {
				Equipment equipment = Equipment();

				equipment.setId(stoul(line));

				getline(equipmentFileManager, line);
				equipment.setName(line);

				getline(equipmentFileManager, line);
				equipment.setType(line);

				getline(equipmentFileManager, line);
				equipment.setBorrower(line);

				getline(equipmentFileManager, line);
				equipment.setRentalPrice(stoi(line));

				getline(equipmentFileManager, day);
				getline(equipmentFileManager, month);
				getline(equipmentFileManager, year);
				equipment.setRentalDate(Date(stoi(day), stoi(month), stoi(year)));

				getline(equipmentFileManager, line);
				equipment.setRented(stoi(line));

				if (equipment.getRented() == true) {
					cout << "Id:" << equipment.getId() << endl;
					cout << "Name: " << equipment.getName() << endl;
					cout << "Type: " << equipment.getType() << endl;
					cout << "Borrower: " << equipment.getBorrower() << endl;
					cout << "Rental price: " << equipment.getRentalPrice() << endl;
					cout << "Rental date: " << equipment.getRentalDate().getDay() << "-" <<
						equipment.getRentalDate().getMonth() << "-" <<
						equipment.getRentalDate().getYear() << endl << endl;
					equipment.~Equipment();
					entityCounter++;
				}
			}
		} if (entityCounter == 0) {
			ColorPrinter::printTone("No rents saved", ColorPrinter::GREEN);
		}
	}
	else {
		ColorPrinter::printTone("Couldn't open file", ColorPrinter::RED);
	}
	equipmentFileManager.close();
}

void RentalService::displayNotBorrowedEquipment()
{
	fstream equipmentFileManager;
	equipmentFileManager.open("equipment.txt", ios::in);

	if (equipmentFileManager.is_open()) {

		int entityCounter = 0;
		string line = "";
		string day = "";
		string month = "";
		string year = "";

		while (getline(equipmentFileManager, line)) {

			if (!line.empty()) {
				Equipment equipment = Equipment();

				equipment.setId(stoul(line));

				getline(equipmentFileManager, line);
				equipment.setName(line);

				getline(equipmentFileManager, line);
				equipment.setType(line);

				getline(equipmentFileManager, line);
				equipment.setBorrower(line);

				getline(equipmentFileManager, line);
				equipment.setRentalPrice(stoi(line));

				getline(equipmentFileManager, day);
				getline(equipmentFileManager, month);
				getline(equipmentFileManager, year);
				equipment.setRentalDate(Date(stoi(day), stoi(month), stoi(year)));

				getline(equipmentFileManager, line);
				equipment.setRented(stoi(line));

				if (equipment.getRented() == false) {
					cout << "Id:" << equipment.getId() << endl;
					cout << "Type :" << equipment.getType() << endl;
					cout << "Name: " << equipment.getName() << endl;
					cout << "Borrower: " << equipment.getBorrower() << endl;
					cout << "Rental price: " << equipment.getRentalPrice() << endl;
					cout << "Rental date: " << equipment.getRentalDate().getDay() << "-" <<
						equipment.getRentalDate().getMonth() << "-" <<
						equipment.getRentalDate().getYear() << endl << endl;
					equipment.~Equipment();
					entityCounter++;
				}
			}
		} if (entityCounter == 0) {
			ColorPrinter::printTone("No rents saved", ColorPrinter::GREEN);
		}
	}
	else {
		ColorPrinter::printTone("Couldn't open file", ColorPrinter::RED);
	}
	equipmentFileManager.close();
}

Equipment RentalService::updateEquipmentValues(unsigned long int id)
{
	Equipment equipment = Equipment();

	ColorPrinter::printTone("Write name", ColorPrinter::GREY, false);
	string name;
	cin >> name;
	ColorPrinter::printTone("Write type", ColorPrinter::GREY, false);
	string type;
	cin >> type;
	ColorPrinter::printTone("Write Rental price", ColorPrinter::GREY, false);
	double rentalPrice;
	cin >> rentalPrice;

	equipment.setId(id);
	equipment.setName(name);
	equipment.setType(type);
	equipment.setRentalPrice(rentalPrice);

	return equipment;
}

void RentalService::updateEquipmentToFileOptional(Equipment& equipment, fstream& fileManager)
{
	fstream tempFileManager;
	tempFileManager.open("equipment_temp.txt", ios::out | ios::app);

	//each equipment takes 11 lines in txt file
	const unsigned int linesToNextEquipment = 11;
	const unsigned int shiftToNextId = 10;
	unsigned int currentLine = 1;
	bool equipmentUpdated = false;
	string line = "";
	string day = "";
	string month = "";
	string year = "";

	while (getline(fileManager, line)) {
		bool isThisLineId = currentLine % shiftToNextId == 1;
		bool isThisEquipmentIdToUpdate = line.compare(to_string(equipment.getId())) == 0;

		if (isThisLineId && isThisEquipmentIdToUpdate) {

			Equipment equipmentToUpdate = Equipment();

			getline(fileManager, line);
			equipmentToUpdate.setName(line);

			getline(fileManager, line);
			equipmentToUpdate.setType(line);

			getline(fileManager, line);
			equipmentToUpdate.setBorrower(line);

			getline(fileManager, line);
			equipmentToUpdate.setRentalPrice(stoi(line));

			getline(fileManager, day);
			getline(fileManager, month);
			getline(fileManager, year);
			equipmentToUpdate.setRentalDate(Date(stoi(day), stoi(month), stoi(year)));

			getline(fileManager, line);
			equipmentToUpdate.setRented(stoi(line));

			this->saveEquipmentToFileOptional(equipment, equipmentToUpdate, tempFileManager);
			equipmentUpdated = true;
			equipmentToUpdate.~Equipment();
			
		} else if (line.empty()) {
			tempFileManager << endl;
		} else {
			tempFileManager << line << endl;
		}
		currentLine++;
	}

	if (equipmentUpdated) {
		ColorPrinter::printTone("Equipment updated", ColorPrinter::GREEN);
	} else {
		ColorPrinter::printTone("Equipment not found", ColorPrinter::RED);
	}
	
	fileManager.close();
	tempFileManager.close();



	remove("equipment.txt");
	rename("equipment_temp.txt", "equipment.txt");

}

void RentalService::saveEquipmentToFileOptional(Equipment& updatedEquipment, Equipment& equipmentToUpdate, fstream& tempFileManager)
{
	tempFileManager << updatedEquipment.getId() << endl;

	if (updatedEquipment.getName().empty()) {
		tempFileManager << equipmentToUpdate.getName() << endl;
	}
	else {
		tempFileManager << updatedEquipment.getName() << endl;
	}

	if (updatedEquipment.getType().empty()) {
		tempFileManager << equipmentToUpdate.getType() << endl;
	}
	else {
		tempFileManager << updatedEquipment.getType() << endl;
	}

	if (updatedEquipment.getBorrower().empty()) {
		tempFileManager << equipmentToUpdate.getBorrower() << endl;
	}
	else {
		tempFileManager << updatedEquipment.getBorrower() << endl;
	}

	if (updatedEquipment.getRentalPrice() == 0.0) {
		tempFileManager << equipmentToUpdate.getRentalPrice() << endl;
	}
	else {
		tempFileManager << updatedEquipment.getRentalPrice() << endl;
	}

	if (updatedEquipment.getRentalDate().getYear() == 0) {
		tempFileManager << equipmentToUpdate.getRentalDate().getDay() << endl;
		tempFileManager << equipmentToUpdate.getRentalDate().getMonth() << endl;
		tempFileManager << equipmentToUpdate.getRentalDate().getYear() << endl;
	}
	else {
		tempFileManager << updatedEquipment.getRentalDate().getDay() << endl;
		tempFileManager << updatedEquipment.getRentalDate().getMonth() << endl;
		tempFileManager << updatedEquipment.getRentalDate().getYear() << endl;
	}

	tempFileManager << updatedEquipment.getRented() << endl;
}

	void RentalService::saveEquipmentToFile(Equipment& equipment, fstream & equipmentSaver)
	{
		equipmentSaver << equipment.getId() << endl;
		equipmentSaver << equipment.getName() << endl;
		equipmentSaver << equipment.getType() << endl;
		equipmentSaver << equipment.getBorrower() << endl;
		equipmentSaver << equipment.getRentalPrice() << endl;
		equipmentSaver << equipment.getRentalDate().getDay() << endl;
		equipmentSaver << equipment.getRentalDate().getMonth() << endl;
		equipmentSaver << equipment.getRentalDate().getYear() << endl;
		equipmentSaver << equipment.getRented() << endl << endl;
	}

	bool RentalService::deleteEquipmentById(unsigned long int id, fstream& fileManager) {

		fstream tempFileManager;
		tempFileManager.open("equipment_temp.txt", ios::out | ios::app);

		//each equipment takes 11 lines in txt file
		const unsigned int linesToNextEquipment = 11;
		const unsigned int shiftToNextId = 10;
		unsigned int currentLine = 1;
		bool equipmentDeleted = false;
		bool rented = false;
		string line = "";
		string day = "";
		string month = "";
		string year = "";
		string decrementedId = "";

		while (getline(fileManager, line)) {
			bool isThisLineId = currentLine % shiftToNextId == 1;
			bool isThisEquipmentIdToUpdate = line.compare(to_string(id)) == 0;

			if (isThisLineId && isThisEquipmentIdToUpdate) {

				Equipment equipmentToDelete = Equipment();
				equipmentToDelete.setId(stoul(line));

				getline(fileManager, line);
				equipmentToDelete.setName(line);

				getline(fileManager, line);
				equipmentToDelete.setType(line);

				getline(fileManager, line);
				equipmentToDelete.setBorrower(line);

				getline(fileManager, line);
				equipmentToDelete.setRentalPrice(stoi(line));

				getline(fileManager, day);
				getline(fileManager, month);
				getline(fileManager, year);
				equipmentToDelete.setRentalDate(Date(stoi(day), stoi(month), stoi(year)));

				getline(fileManager, line);
				equipmentToDelete.setRented(stoi(line));
				if (equipmentToDelete.getRented() == 1) {
					rented = true;
					saveEquipmentToFile(equipmentToDelete, tempFileManager);
					equipmentToDelete.~Equipment();
				} else {
					equipmentToDelete.~Equipment();
					equipmentDeleted = true;
				}
			}
			else if (line.empty()) {
				tempFileManager << endl;
			}
			else if (!equipmentDeleted){
				tempFileManager << line << endl;
			}
			currentLine++;
		}

		while(getline(fileManager,line)){
		bool isThisLineId = currentLine % shiftToNextId == 1;
						if (isThisLineId) {
							string value = line;
							decrementedId = decrementIdFromString(value);
							tempFileManager << decrementedId << endl;
						} else {
						tempFileManager << line << endl;
						}	
				
				currentLine++;
			}

			if (equipmentDeleted) {
				ColorPrinter::printTone("Equipment deleted", ColorPrinter::GREEN);
			} else if (!equipmentDeleted && !rented){
				ColorPrinter::printTone("Equipment not found", ColorPrinter::RED);
			} else {
				ColorPrinter::printTone("Cannot delete rented equipment", ColorPrinter::RED);
			}


			fileManager.close();
			tempFileManager.close();

			remove("equipment.txt");
			rename("equipment_temp.txt", "equipment.txt");

			return equipmentDeleted;
	}
	
	string RentalService::decrementIdFromString(string line)
	{
		unsigned long int intValue = stoul(line);
		intValue--;
		return to_string(intValue);
	}

	void RentalService::displayEquipmentByName(string name, fstream& equipmentFileManager) {

		string line = "";
		string day = "";
		string month = "";
		string year = "";

		while (getline(equipmentFileManager, line)) {

			if (!line.empty()) {
				Equipment equipment = Equipment();

				getline(equipmentFileManager, line);
				equipment.setName(line);

				getline(equipmentFileManager, line);
				equipment.setType(line);

				getline(equipmentFileManager, line);
				equipment.setBorrower(line);

				getline(equipmentFileManager, line);
				equipment.setRentalPrice(stoi(line));

				getline(equipmentFileManager, day);
				getline(equipmentFileManager, month);
				getline(equipmentFileManager, year);
				equipment.setRentalDate(Date(stoi(day), stoi(month), stoi(year)));

				getline(equipmentFileManager, line);
				equipment.setRented(stoi(line));

				if (equipment.getName().compare(name))
					cout << "Name: " << equipment.getName() << endl;
				cout << "Borrower: " << equipment.getBorrower() << endl;
				cout << "Rental price: " << equipment.getRentalPrice() << endl;
				cout << "Rental date: " << equipment.getRentalDate().getDay() << "-" <<
					equipment.getRentalDate().getDay() << "-" <<
					equipment.getRentalDate().getDay() << endl;
				equipment.~Equipment();
			}
		}
	}

	void RentalService::displayEquipmentByBorrowerName(string borrowerName, fstream& equipmentFileManager) {
		string line = "";
		string day = "";
		string month = "";
		string year = "";

		while (getline(equipmentFileManager, line)) {

			if (!line.empty()) {
				Equipment equipment = Equipment();

				getline(equipmentFileManager, line);
				equipment.setName(line);

				getline(equipmentFileManager, line);
				equipment.setType(line);

				getline(equipmentFileManager, line);
				equipment.setBorrower(line);

				getline(equipmentFileManager, line);
				equipment.setRentalPrice(stoi(line));

				getline(equipmentFileManager, day);
				getline(equipmentFileManager, month);
				getline(equipmentFileManager, year);
				equipment.setRentalDate(Date(stoi(day), stoi(month), stoi(year)));

				getline(equipmentFileManager, line);
				equipment.setRented(stoi(line));

				if (equipment.getBorrower().compare(borrowerName)) {
					cout << "Name: " << equipment.getName() << endl;
					cout << "Borrower: " << equipment.getBorrower() << endl;
					cout << "Rental price: " << equipment.getRentalPrice() << endl;
					cout << "Rental date: " << equipment.getRentalDate().getDay() << "-" <<
						equipment.getRentalDate().getDay() << "-" <<
						equipment.getRentalDate().getDay() << endl;
					equipment.~Equipment();
				}
			}
		}
	}

	Equipment RentalService::updateRentValues(unsigned long int id) {

		Equipment equipment = Equipment();

		ColorPrinter::printTone("Write borrower name", ColorPrinter::GREY, false);
		string borrowerName;
		cin >> borrowerName;
		
		equipment.setId(id);
		equipment.setName("");
		equipment.setType("");
		equipment.setBorrower(borrowerName);
		equipment.setRentalPrice(0.0);
		equipment.setRentalDate(Date());
		equipment.setRented(true);

		return equipment;
	}

	Equipment RentalService::updateRefundValues(unsigned long int id) {

		Equipment equipment = Equipment();
		
		equipment.setId(id);
		equipment.setName("");
		equipment.setType("");
		equipment.setBorrower("n");
		equipment.setRentalPrice(0.0);
		equipment.setRentalDate(Date(1,1,0));
		equipment.setRented(false);

		return equipment;
	}