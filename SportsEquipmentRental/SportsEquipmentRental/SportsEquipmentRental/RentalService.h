#pragma once
#include "Magazine.h"
#include "Equipment.h"

class RentalService
{
protected:
	void saveEquipmentToFile(Equipment& equipment, fstream& equipmentSaver);
	void addNewEquipment(Magazine& magazine);
	void displayMagazineCapacity(Magazine* magazine);
	void updateEquipment(Magazine& magazine);
	void deleteEquipment(Magazine& magazine);
	void displayEquipment();
	void displayRentsWith30DayPassed();
	void handleRefund();
	void handleRent();
	void findEquipmentByName();
	void findEquipmentByBorrowerName();
	void displayBorrowedEquipment();
	void displayNotBorrowedEquipment();

	Equipment updateEquipmentValues(unsigned long int id);
	void updateEquipmentToFileOptional(Equipment& equipment, fstream& fileManager);
	void saveEquipmentToFileOptional(Equipment& updatedEquipment, Equipment& equipmentToUpdate, ofstream& tempFileManager);
};




