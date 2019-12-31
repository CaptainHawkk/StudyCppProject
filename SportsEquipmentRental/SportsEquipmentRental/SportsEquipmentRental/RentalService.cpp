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
		}


}

void RentalService::deleteEquipment(Magazine& magazine)
{
}

void RentalService::displayEquipment()
{
}

void RentalService::displayRentsWith30DayPassed()
{
}

void RentalService::handleRefund()
{
}

void RentalService::handleRent()
{
}

void RentalService::findEquipmentByName()
{
}

void RentalService::findEquipmentByBorrowerName()
{
}

void RentalService::displayBorrowedEquipment()
{
}

void RentalService::displayNotBorrowedEquipment()
{
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
	ofstream tempFileManager;
	tempFileManager.open("equipment_temp.txt");

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

	void RentalService::saveEquipmentToFileOptional(Equipment& updatedEquipment, Equipment& equipmentToUpdate, ofstream& tempFileManager)
	{
		tempFileManager << updatedEquipment.getId() << endl;

		if (updatedEquipment.getName().empty()) {
			tempFileManager << equipmentToUpdate.getName() << endl;
		} else {
			tempFileManager << updatedEquipment.getName() << endl;
		}

		if (updatedEquipment.getType().empty()) {
			tempFileManager << equipmentToUpdate.getType() << endl;
		} else {
			tempFileManager << updatedEquipment.getType() << endl;
		}

		if (updatedEquipment.getBorrower().empty()) {
			tempFileManager << equipmentToUpdate.getBorrower() << endl;
		} else {
			tempFileManager << updatedEquipment.getBorrower() << endl;
		}

		if (updatedEquipment.getRentalPrice() == 0.0) {
			tempFileManager << equipmentToUpdate.getRentalPrice() << endl;
		} else {
			tempFileManager << updatedEquipment.getRentalPrice() << endl;
		}

		if (updatedEquipment.getRentalDate().getYear() == 0) {
			tempFileManager << equipmentToUpdate.getRentalDate().getDay() << endl;
			tempFileManager << equipmentToUpdate.getRentalDate().getMonth() << endl;
			tempFileManager << equipmentToUpdate.getRentalDate().getYear() << endl;
		} else {
			tempFileManager << updatedEquipment.getRentalDate().getDay() << endl;
			tempFileManager << updatedEquipment.getRentalDate().getMonth() << endl;
			tempFileManager << updatedEquipment.getRentalDate().getYear() << endl;
		}

		tempFileManager << equipmentToUpdate.getRented() << endl;
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
	
	