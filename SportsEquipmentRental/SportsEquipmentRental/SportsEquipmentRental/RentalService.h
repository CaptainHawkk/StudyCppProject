#pragma once
#include "Magazine.h"
#include "Equipment.h"
#include "LoginService.h"

class RentalService: LoginService
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
	void findEquipmentByBorrowerMail();
	void displayBorrowedEquipment();
	void displayNotBorrowedEquipment();
	void displayMagazineCapacity(Magazine* magazine);
	void addUserToFile();
	void displayAllUsers();
	void displayUserByMail();
	void findEquipmentByType();
	void updateUser();
	void displayUserEquipment(User& user);
	void deleteUserByMail();
	void updateUserValues(User& user);
	void findEquipmentWithCostHigherThan();
	void findEquipmentWithCostLowerThan();
	
private:
	string decrementIdFromString(string line);
	void displayEquipmentByBorrowerName(string name, fstream& equipmentFileManager);
	void displayEquipmentByName(string name, fstream& equipmentFileManager);
	Equipment updateRentValues(unsigned long int id);
	Equipment findEquipmentById(unsigned long int id);
	Equipment updateRefundValues(unsigned long int id);
	Equipment updateEquipmentValues(unsigned long int id);
	Equipment getEquipmentFromFile(fstream& equipmentFileManager, string& line);
	void updateEquipmentToFileOptional(Equipment& equipment, fstream& fileManager);
	void saveEquipmentToFileOptional(Equipment& updatedEquipment, Equipment& equipmentToUpdate, fstream& tempFileManager);
	void saveEquipmentToFile(Equipment& equipment, fstream& equipmentSaver);
	bool deleteEquipmentById(unsigned long int id, fstream& fileManager);
	void updateEquipmentToFileIfNotRented(Equipment& equipment, fstream& equipmentFileManager);
	void updateEquipmentToFileIfRented(Equipment& equipment, fstream& equipmentFileManager);	
	bool mailIsUnique(string mail);
	void displayEquipmentByType(string type, fstream& equipmentFileManager);
	void displayEquipmentWithPriceHigher(double price, fstream& equipmentFileManager);
	void displayEquipmentWithPriceLower(double price, fstream& equipmentFileManager);
	void displayEquipmentById(int id);
	void updateUserValuesOriginal(User& user);
	void saveUserToFileOptional(fstream& userFileManager, User& user, User& oldUser);
	


};




