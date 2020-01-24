#include "RentalService.h"
#include "Magazine.h"
#include "Equipment.h"
#include "ColorPrinter.h"
#include <fstream>
#include "User.h"
#include "IdController.h"


void RentalService::addNewEquipment(Magazine& magazine)
{
	IdController idController;

	if (magazine.magazineIsFull()) {
		ColorPrinter::printTone("Magazine is full, can't add more equipment", ColorPrinter::RED);
		return;
	}

	fstream equipmentSaver;
	equipmentSaver.open("equipment.txt",ios::out | ios::app);

	if (equipmentSaver.is_open()) {

		Equipment equipment;
		equipment.setEquipmentData();
		equipment.setId(idController.getEquipmentNextId());
		idController.incrementEquipmentNextId();
		this->saveEquipmentToFile(equipment, equipmentSaver);
		magazine.incrementActualCapacity();
		ColorPrinter::printTone("Equipment added", ColorPrinter::GREEN);
		equipmentSaver.close();
		equipment.~Equipment();
	} else {
		ColorPrinter::printTone("Couldn't open file", ColorPrinter::RED);
	}

	idController.~IdController();
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

			this->updateEquipmentToFileIfNotRented(equipment, equipmentFileManager);
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

		if (decrementCapacity == 1) {
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
		while (getline(equipmenFileManager, line)) {

			if (!line.empty()) {

				Equipment equipment = getEquipmentFromFile(equipmenFileManager, line);
				cout << equipment << endl;
				equipment.~Equipment();
				
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

		while (getline(equipmentFileManager, line)) {

			if (!line.empty()) {
				Equipment equipment = getEquipmentFromFile(equipmentFileManager,line);

				if (equipment.getRented() && Date::the30DayHasPassed(equipment.getRentalDate()) && equipment.getRentalDate().getYear() != 0) {
					cout << equipment << endl;
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

		this->updateEquipmentToFileIfRented(equipment, equipmentFileManager);
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

		this->updateEquipmentToFileIfNotRented(equipment, equipmentFileManager);
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

void RentalService::findEquipmentByBorrowerMail()
{
	fstream equipmentFileManager;
	equipmentFileManager.open("equipment.txt", ios::in);

	if (equipmentFileManager.is_open()) {
		string borrowerName;

		ColorPrinter::printTone("Find equipment by Borrower name", ColorPrinter::BLUE);
		ColorPrinter::printTone("Write Borrower name", ColorPrinter::BLUE);
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

		while (getline(equipmentFileManager, line)) {

			if (!line.empty()) {
				Equipment equipment = getEquipmentFromFile(equipmentFileManager,line);

				if (equipment.getRented() == true) {
					cout <<  equipment << endl;
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


		while (getline(equipmentFileManager, line)) {

			if (!line.empty()) {
				Equipment equipment = getEquipmentFromFile(equipmentFileManager, line);

				if (equipment.getRented() == false) {
					cout << equipment << endl;
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

Equipment RentalService::getEquipmentFromFile(fstream& equipmentFileManager, string& line)
{
	string day = "", month = "", year = "";

	Equipment equipmentfromFile = Equipment();
	equipmentfromFile.setId(stoul(line));

	getline(equipmentFileManager, line);
	equipmentfromFile.setName(line);

	getline(equipmentFileManager, line);
	equipmentfromFile.setType(line);

	getline(equipmentFileManager, line);
	equipmentfromFile.setBorrower(line);

	getline(equipmentFileManager, line);
	equipmentfromFile.setRentalPrice(stoul(line));

	getline(equipmentFileManager, day);
	getline(equipmentFileManager, month);
	getline(equipmentFileManager, year);
	equipmentfromFile.setRentalDate(Date(stoi(day), stoi(month), stoi(year)));

	getline(equipmentFileManager, line);
	equipmentfromFile.setRented(stoul(line));

	return equipmentfromFile;
}

void RentalService::updateEquipmentToFileOptional(Equipment& equipment, fstream& fileManager)
{
	fstream tempFileManager;
	tempFileManager.open("equipment_temp.txt", ios::in | ios::app);

	//each equipment takes 11 lines in txt file
	const unsigned int linesToNextEquipment = 11;
	const unsigned int shiftToNextId = 10;
	unsigned int currentLine = 1;
	bool equipmentUpdated = false;
	bool success;
	string line = "";
	string day = "";
	string month = "";
	string year = "";

	while (getline(fileManager, line)) {
		bool isThisLineId = currentLine % shiftToNextId == 1;
		bool isThisEquipmentIdToUpdate = line.compare(to_string(equipment.getId())) == 0;

		if (isThisLineId && isThisEquipmentIdToUpdate) {

			Equipment equipmentToUpdate = getEquipmentFromFile(fileManager,line);
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



	success = remove("equipment.txt");
	success = rename("equipment_temp.txt", "equipment.txt");

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
		bool success;
		string line = "";
		string decrementedId = "";

		while (getline(fileManager, line)) {
			bool isThisLineId = currentLine % shiftToNextId == 1;
			bool isThisEquipmentIdToUpdate = (line == to_string(id)) == 1;

			if (isThisLineId && isThisEquipmentIdToUpdate) {

				Equipment equipmentToDelete = getEquipmentFromFile(fileManager,line);
				//currentLine += 8;

				if (equipmentToDelete.getRented() == 1) {
					rented = true;
					saveEquipmentToFile(equipmentToDelete, tempFileManager);
					equipmentToDelete.~Equipment();
				} else {
					equipmentToDelete.~Equipment();
					equipmentDeleted = true;
					currentLine++;
					getline(fileManager, line); // zeby ominê³o puste pole po usuniêciu
					break;
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

				if (line.empty()) {
					tempFileManager << endl;
				}
				else {
					Equipment equipmentToDelete = getEquipmentFromFile(fileManager, line);
					int oldId = equipmentToDelete.getId();
					equipmentToDelete.setId(oldId - 1);
					saveEquipmentToFile(equipmentToDelete, tempFileManager);
					equipmentToDelete.~Equipment();
					getline(fileManager, line);
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

			success = remove("equipment.txt");
			success = rename("equipment_temp.txt", "equipment.txt");

			return equipmentDeleted;
	}

	void RentalService::updateEquipmentToFileIfNotRented(Equipment& equipment, fstream& equipmentFileManager)
	{
		fstream tempFileManager;
		tempFileManager.open("equipment_temp.txt", ios::out | ios::app);

		//each equipment takes 11 lines in txt file
		const unsigned int linesToNextEquipment = 11;
		const unsigned int shiftToNextId = 10;
		unsigned int currentLine = 1;
		bool equipmentUpdated = false;
		bool equipmentRented = false;
		bool success;
		string line = "";

		while (getline(equipmentFileManager, line)) {
			bool isThisLineId = currentLine % shiftToNextId == 1;
			bool isThisEquipmentIdToUpdate = line.compare(to_string(equipment.getId())) == 0;

			if (isThisLineId && isThisEquipmentIdToUpdate) {

				Equipment equipmentToUpdate = getEquipmentFromFile(equipmentFileManager, line);
				if (equipmentToUpdate.getRented() == 0) {
					User borrower = findUserByMail(equipment.getBorrower());
					if (borrower.getRentCount() < borrower.getMaximumBorrowQuantity()) {
						vector<int> idArray = borrower.getBorowedEquipmentId();
						idArray.push_back(equipmentToUpdate.getId());
						borrower.setBorrowedEquipmentId(idArray);
						borrower.incrementRentCount();
						updateUserValuesOriginal(borrower);
						this->saveEquipmentToFileOptional(equipment, equipmentToUpdate, tempFileManager);
						equipmentUpdated = true;
						equipmentToUpdate.~Equipment();
					}
					else {
						this->saveEquipmentToFile(equipmentToUpdate, tempFileManager);
						equipmentRented = true;
						equipmentToUpdate.~Equipment();
					}
					borrower.~User();
				} else {
					this->saveEquipmentToFile(equipmentToUpdate, tempFileManager);
					equipmentRented = true;
					equipmentToUpdate.~Equipment();
				}
			} else if (line.empty()) {
				tempFileManager << endl;
			} else {
				tempFileManager << line << endl;
			}
			currentLine++;
		}

		if (equipmentUpdated) {
			ColorPrinter::printTone("Equipment updated", ColorPrinter::GREEN);
		} else if(equipmentRented){
			ColorPrinter::printTone("Cannot update rented equipment", ColorPrinter::RED);
		} else {
			ColorPrinter::printTone("Equipment not found", ColorPrinter::RED);
		}

		equipmentFileManager.close();
		tempFileManager.close();



		success = remove("equipment.txt");
		success = rename("equipment_temp.txt", "equipment.txt");

	}

	void RentalService::updateEquipmentToFileIfRented(Equipment& equipment, fstream& equipmentFileManager)
	{
		fstream tempFileManager;
		tempFileManager.open("equipment_temp.txt", ios::out | ios::app);

		//each equipment takes 11 lines in txt file
		const unsigned int linesToNextEquipment = 11;
		const unsigned int shiftToNextId = 10;
		unsigned int currentLine = 1;
		bool equipmentUpdated = false;
		bool equipmentNotRented = false;
		bool success;
		vector<int> idArray;
		string line = "";

		while (getline(equipmentFileManager, line)) {
			bool isThisLineId = currentLine % shiftToNextId == 1;
			bool isThisEquipmentIdToUpdate = line.compare(to_string(equipment.getId())) == 0;

			if (isThisLineId && isThisEquipmentIdToUpdate) {

				Equipment equipmentToUpdate = getEquipmentFromFile(equipmentFileManager, line);
				if (equipmentToUpdate.getRented() == 1) {
					User borrower = findUserByMail(equipmentToUpdate.getBorrower());
					for (int i = 0; borrower.getRentCount(); i++) {
						if (borrower.getBorowedEquipmentId().at(i) == equipmentToUpdate.getId()) {
							idArray = borrower.getBorowedEquipmentId();
							idArray.erase(idArray.begin()+i);
							borrower.setBorrowedEquipmentId(idArray);
							borrower.decrementRentCount();
							updateUserValuesOriginal(borrower);
						}
					}
					this->saveEquipmentToFileOptional(equipment, equipmentToUpdate, tempFileManager);
					equipmentUpdated = true;
					equipmentToUpdate.~Equipment();
				}
				else {
					this->saveEquipmentToFile(equipmentToUpdate, tempFileManager);
					equipmentNotRented = true;
					equipmentToUpdate.~Equipment();
				}
			}
			else if (line.empty()) {
				tempFileManager << endl;
			}
			else {
				tempFileManager << line << endl;
			}
			currentLine++;
		}

		if (equipmentUpdated) {
			ColorPrinter::printTone("Equipment updated", ColorPrinter::GREEN);
		}
		else if (equipmentNotRented) {
			ColorPrinter::printTone("Cannot refund not borrowed equipment", ColorPrinter::RED);
		}
		else {
			ColorPrinter::printTone("Equipment not found", ColorPrinter::RED);
		}

		equipmentFileManager.close();
		tempFileManager.close();



		remove("equipment.txt");
		success = rename("equipment_temp.txt", "equipment.txt");

	}
	
	string RentalService::decrementIdFromString(string line)
	{
		int intValue = stoul(line);
		intValue--;
		return to_string(intValue);
	}

	void RentalService::displayEquipmentByName(string name, fstream& equipmentFileManager) {

		string line = "";
		int EntityCounter = 0;

		while (getline(equipmentFileManager, line)) {

			if (!line.empty()) {
				Equipment equipment = getEquipmentFromFile(equipmentFileManager, line);
		
				if (equipment.getName() == name){
					cout << equipment << endl;
					equipment.~Equipment();
					EntityCounter++;
				} else {
					equipment.~Equipment();
				}
			}
		}

		if (EntityCounter == 0) {
			ColorPrinter::printTone("Equipment with this name doesn't exist", ColorPrinter::RED);
		}
	}

	void RentalService::displayEquipmentByBorrowerName(string borrowerName, fstream& equipmentFileManager) {

		string line = "";
		int EntityCounter = 0;

		while (getline(equipmentFileManager, line)) {

			if (!line.empty()) {

				Equipment equipment = getEquipmentFromFile(equipmentFileManager,line);

				if (equipment.getBorrower() == borrowerName) {
					cout << equipment << endl;
					equipment.~Equipment();
					EntityCounter++;
				} else {
					equipment.~Equipment();
				}
			}
		}

		if (EntityCounter == 0) {
			ColorPrinter::printTone("Borrower with this name doesn't exist", ColorPrinter::RED);
		}
	}

	Equipment RentalService::updateRentValues(unsigned long int id) {

		Equipment equipment = Equipment();

		ColorPrinter::printTone("Write borrower mail", ColorPrinter::GREY, false);
		string borrowerMail;
		cin >> borrowerMail;
		
		equipment.setId(id);
		equipment.setName("");
		equipment.setType("");
		equipment.setBorrower(borrowerMail);
		equipment.setRentalPrice(0.0);
		equipment.setRentalDate(Date());
		equipment.setRented(true);
			

		return equipment;
	}

	Equipment RentalService::findEquipmentById(unsigned long int id)
	{
		fstream equipmentFileManager;
		equipmentFileManager.open("equipment.txt", ios::in);

		string line = "";
		Equipment equipment;

		if (equipmentFileManager.is_open()) {
			while (getline(equipmentFileManager, line)) {

				if (!line.empty()) {
					equipment = getEquipmentFromFile(equipmentFileManager, line);
					if (equipment.getId() == id) {
						equipmentFileManager.close();
						return equipment;
					}
				}
			}
		}

		equipmentFileManager.close();
		Equipment eq = Equipment();
		return eq;
	}

	Equipment RentalService::updateRefundValues(unsigned long int id) {

		Equipment equipment = Equipment();
		
		equipment = findEquipmentById(id);

			equipment.setId(id);
			equipment.setName("");
			equipment.setType("");
			equipment.setBorrower("n");
			equipment.setRentalPrice(0.0);
			equipment.setRentalDate(Date(1, 1, 0));
			equipment.setRented(false);
		
		return equipment;
	}

	void RentalService::addUserToFile()
	{
		User user = User();
		user.setUser();

		if (mailIsUnique(user.getMail())) {
			saveUserToFile(user);
		}
		else {
			ColorPrinter::printTone("Cannot create user, email already exist", ColorPrinter::RED);
		}
	}


	bool RentalService::mailIsUnique(string mail)
	{
		User user = User();
		user = findUserByMail(mail);
		
		if (user.getMail().compare(mail) == 0) {
			return false;
		}
		else {
			return true;
		}
	}


	void RentalService::displayAllUsers()
	{
		fstream userFileManager;
		userFileManager.open("users.txt", ios::in);
		if (userFileManager.is_open()) {

			string line = "";
			User user = User();

			while (getline(userFileManager, line)) {

				if (!line.empty()) {
					copyUserFromFile(userFileManager, line, &user);
					cout << user;
				}				
			}
			userFileManager.close();
			user.~User();
		}

		userFileManager.close();

	}
	


	void RentalService::displayUserByMail()
	{
		string mail = "";

		ColorPrinter::printTone("Write user mail", ColorPrinter::BLUE);
		cin >> mail;
		User user = findUserByMail(mail);
		if (user.getMail().compare(mail) == 0) {
			cout << user << endl;
		}
	}


	void RentalService::updateUser()
	{
		string mail;
		ColorPrinter::printTone("Write user mail", ColorPrinter::BLUE);
		cin >> mail;
		User user;
		user = findUserByMail(mail);
		if (user.getId() == 0) {
			ColorPrinter::printTone("User not found", ColorPrinter::RED);
		}
		else {
			user.setUser();
			if (mailIsUnique(user.getMail())) {
				updateUserValuesOriginal(user);
			}
			else {
				ColorPrinter::printTone("Mail not unique", ColorPrinter::RED);
			}
		}
	}



	void RentalService::deleteUserByMail()
	{
		ColorPrinter::printTone("Write mail user to delete", ColorPrinter::BLUE);
		string mail;
		cin >> mail;

		fstream userFileManager;
		fstream userTempFileManager;
		userFileManager.open("users.txt", ios::in);
		userTempFileManager.open("users_temp.txt", ios::out | ios::app);

		bool userDeleted = false;
		string line = "";
		User userFromFile;

		while (getline(userFileManager, line)) {

			if (!line.empty()) {
				userFromFile = getUserFromFile(userFileManager, line);
				if (userFromFile.getMail().compare(mail) == 0 && userFromFile.getRentCount() == 0) {
					ColorPrinter::printTone("User deleted", ColorPrinter::GREEN);
					userDeleted = true;
				}
				else if (userFromFile.getMail().compare(mail) == 0 && userFromFile.getRentCount() > 0) {
					ColorPrinter::printTone("Cannot delete user with rents", ColorPrinter::GREEN);
					saveUserToFileOptional(userTempFileManager, userFromFile, userFromFile);
				}
				else {
					saveUserToFileOptional(userTempFileManager, userFromFile, userFromFile);
				}
			}
		}

		if (!userDeleted) {
			ColorPrinter::printTone("User not found", ColorPrinter::RED);
		}
		userFileManager.close();
		userTempFileManager.close();

		remove("users.txt");
		rename("users_temp.txt", "users.txt");
	}


	void RentalService::displayUserEquipment(User& user)
	{
		Equipment equipment;

		for (int i = 0; i < user.getRentCount(); i++) {
			displayEquipmentById(user.getBorowedEquipmentId()[i]);
		}
	}


	void RentalService::displayEquipmentById(int id)
	{
		fstream equipmentFileManager;
		equipmentFileManager.open("equipment.txt", ios::in);

		string line = "";
		Equipment equipment;

		if (equipmentFileManager.is_open()) {
			while (getline(equipmentFileManager, line)) {

				if (!line.empty()) {
					equipment = getEquipmentFromFile(equipmentFileManager, line);
					if (equipment.getId() == id) {
						cout << equipment << endl;
					}
				}
			}
		}

		equipmentFileManager.close();
	}


	void RentalService::updateUserValues(User& user)
	{
		ColorPrinter::printTone("Write new values", ColorPrinter::BLUE);
		user.setUser();


		fstream userFileManager;
		fstream userTempFileManager;
		userFileManager.open("users.txt", ios::in);
		userTempFileManager.open("users_temp.txt", ios::out | ios::app);

		string line = "";
		User userFromFile;

		while (getline(userFileManager, line)) {

			if (!line.empty()) {
				userFromFile = getUserFromFile(userFileManager, line);
				if (userFromFile.getId() == user.getId()) {
					saveUserToFileOptional(userTempFileManager, user, userFromFile);
				}
				else {
					saveUserToFileOptional(userTempFileManager, userFromFile, userFromFile);
				}
			}
		}

		userFileManager.close();
		userTempFileManager.close();

		remove("users.txt");
		rename("users_temp.txt", "users.txt");
	}

	void RentalService::updateUserValuesOriginal(User& user)
	{
		
		fstream userFileManager;
		fstream userTempFileManager;
		userFileManager.open("users.txt", ios::in);
		userTempFileManager.open("users_temp.txt", ios::out | ios::app);

		string line = "";
		User userFromFile;

		while (getline(userFileManager, line)) {

			if (!line.empty()) {
				userFromFile = getUserFromFile(userFileManager, line);
				if (userFromFile.getId() == user.getId()) {
					saveUserToFileOptional(userTempFileManager, user, userFromFile);
				}
				else {
					saveUserToFileOptional(userTempFileManager, userFromFile, userFromFile);
				}
			}
		}
		userFileManager.close();
		userTempFileManager.close();

		remove("users.txt");
		rename("users_temp.txt", "users.txt");
	}

	void RentalService::saveUserToFileOptional(fstream& userFileManager, User& user, User& oldUser)
	{
			
			userFileManager << user.getId() << endl;
			if (user.getName().empty()) {
				userFileManager << oldUser.getName() << endl;
			} else {
				userFileManager << user.getName() << endl;
			}

			if (user.getLastName().empty()) {
				userFileManager << oldUser.getName() << endl;
			} else {
				userFileManager << user.getLastName() << endl;
			}
			
			if (user.getMail().empty()) {
				userFileManager << oldUser.getMail() << endl;
			} else {
				userFileManager << user.getMail() << endl;
			}
			
			userFileManager << user.getRole() << endl;

			if (user.getPassword().empty()) {
				userFileManager << oldUser.getPassword() << endl;
			}
			else {
				userFileManager << user.getPassword() << endl;
			}
			userFileManager << user.getRentCount() << endl;
			userFileManager << user.getMaximumBorrowQuantity() << endl;
			if (user.getRentCount() > 0) {
				for (int i = 0; i < user.getRentCount(); i++) {
					userFileManager << user.getBorowedEquipmentId()[i] << endl;
				}
				userFileManager << endl;
			}
			else {
				userFileManager << endl;
			}
			//ColorPrinter::printTone("User saved successfully", ColorPrinter::GREEN);
	}


	void RentalService::findEquipmentByType()
	{
		fstream equipmentFileManager;
		equipmentFileManager.open("equipment.txt", ios::in);

		if (equipmentFileManager.is_open()) {
			string type;

			ColorPrinter::printTone("Find equipment by Type", ColorPrinter::BLUE);
			ColorPrinter::printTone("Write Type", ColorPrinter::BLUE);
			std::cin >> type;

			this->displayEquipmentByType(type, equipmentFileManager);
			equipmentFileManager.close();
		}
		else {
			ColorPrinter::printTone("Couldn't open file", ColorPrinter::RED);
		}
	}


	void RentalService::findEquipmentWithCostHigherThan()
	{

		fstream equipmentFileManager;
		equipmentFileManager.open("equipment.txt", ios::in);

		if (equipmentFileManager.is_open()) {
			double price;

			ColorPrinter::printTone("Find equipment with price higher than given", ColorPrinter::BLUE);
			ColorPrinter::printTone("Write price", ColorPrinter::BLUE);
			std::cin >> price;

			this->displayEquipmentWithPriceHigher(price, equipmentFileManager);
			equipmentFileManager.close();
		}
		else {
			ColorPrinter::printTone("Couldn't open file", ColorPrinter::RED);
		}
	}


	void RentalService::findEquipmentWithCostLowerThan()
	{
		fstream equipmentFileManager;
		equipmentFileManager.open("equipment.txt", ios::in);

		if (equipmentFileManager.is_open()) {
			double price;

			ColorPrinter::printTone("Find equipment with price lower than given", ColorPrinter::BLUE);
			ColorPrinter::printTone("Write price", ColorPrinter::BLUE);
			std::cin >> price;

			this->displayEquipmentWithPriceLower(price, equipmentFileManager);
			equipmentFileManager.close();
		}
		else {
			ColorPrinter::printTone("Couldn't open file", ColorPrinter::RED);
		}
	}


	void RentalService::displayEquipmentByType(string type, fstream& equipmentFileManager)
	{
		string line = "";
		int EntityCounter = 0;

		while (getline(equipmentFileManager, line)) {

			if (!line.empty()) {

				Equipment equipment = getEquipmentFromFile(equipmentFileManager, line);

				if (equipment.getType() == type) {
					cout << equipment << endl;
					equipment.~Equipment();
					EntityCounter++;
				}
				else {
					equipment.~Equipment();
				}
			}
		}

		if (EntityCounter == 0) {
			ColorPrinter::printTone("Equipment with this type doesn't exist", ColorPrinter::RED);
		}
	}


	void RentalService::displayEquipmentWithPriceHigher(double price, fstream& equipmentFileManager)
	{
		string line = "";
		int EntityCounter = 0;

		while (getline(equipmentFileManager, line)) {

			if (!line.empty()) {

				Equipment equipment = getEquipmentFromFile(equipmentFileManager, line);

				if (equipment.getRentalPrice() >= price) {
					cout << equipment << endl;
					equipment.~Equipment();
					EntityCounter++;
				}
				else {
					equipment.~Equipment();
				}
			}
		}

		if (EntityCounter == 0) {
			ColorPrinter::printTone("Equipment with this condition doesn't exist", ColorPrinter::RED);
		}
	}


	void RentalService::displayEquipmentWithPriceLower(double price, fstream& equipmentFileManager)
	{
		string line = "";
		int EntityCounter = 0;

		while (getline(equipmentFileManager, line)) {

			if (!line.empty()) {

				Equipment equipment = getEquipmentFromFile(equipmentFileManager, line);

				if (equipment.getRentalPrice() <= price) {
					cout << equipment << endl;
					equipment.~Equipment();
					EntityCounter++;
				}
				else {
					equipment.~Equipment();
				}
			}
		}

		if (EntityCounter == 0) {
			ColorPrinter::printTone("Equipment with this condition doesn't exist", ColorPrinter::RED);
		}
	}
