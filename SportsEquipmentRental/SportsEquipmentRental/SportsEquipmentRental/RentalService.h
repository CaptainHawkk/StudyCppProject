#pragma once
#include "Magazine.h"
#include "Equipment.h"

class RentalService
{
protected:
	void addNewEquipment(Magazine& magazine);
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
	void displayMagazineCapacity(Magazine* magazine);

	
private:
	string decrementIdFromString(string line);
	void displayEquipmentByBorrowerName(string name, fstream& equipmentFileManager);
	void displayEquipmentByName(string name, fstream& equipmentFileManager);
	Equipment updateRentValues(unsigned long int id);
	Equipment updateRefundValues(unsigned long int id);
	Equipment updateEquipmentValues(unsigned long int id);
	void updateEquipmentToFileOptional(Equipment& equipment, fstream& fileManager);
	void saveEquipmentToFileOptional(Equipment& updatedEquipment, Equipment& equipmentToUpdate, fstream& tempFileManager);
	void saveEquipmentToFile(Equipment& equipment, fstream& equipmentSaver);
	bool deleteEquipmentById(unsigned long int id, fstream& fileManager);

};




