#include "LoginService.h"
#include <iostream>
#include <string>
#include <fstream>
#include "ColorPrinter.h"
#include <cstdlib>
#include "IdController.h"

using namespace std;

void LoginService::saveUserToFile(User& user)
{
	fstream userFileManager;

	IdController idController;

	userFileManager.open("users.txt", ios::out | ios::app);

	if (userFileManager.is_open()) {
		userFileManager << idController.getUserNextId() << endl;
		idController.incrementUserNextId();
		userFileManager << user.getName() << endl;
		userFileManager << user.getLastName() << endl;
		userFileManager << user.getMail() << endl;
		userFileManager << user.getRole() << endl;
		userFileManager << user.getPassword() << endl;
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
		ColorPrinter::printTone("User saved successfully", ColorPrinter::GREEN);
	}
	else {
		ColorPrinter::printTone("Couldn't open file", ColorPrinter::RED);
	}

	userFileManager.close();
	idController.~IdController();
}

User LoginService::getUserFromFile(fstream& userFileManager, string& line)
{
	User user = User();

	user.setid(stoul(line));

	getline(userFileManager, line);
	user.setName(line);

	getline(userFileManager, line);
	user.setLastName(line);

	getline(userFileManager, line);
	user.setMail(line);

	getline(userFileManager, line);
	user.setRole(line);

	getline(userFileManager, line);
	user.setPassword(line);

	getline(userFileManager, line);
	user.setRentCount(stoi(line));

	getline(userFileManager, line);
	user.setMaximumBorrowQuantity(stoi(line));

	if (user.getRentCount() > 0) {

		vector<int> idArray;
		idArray.reserve(user.getMaximumBorrowQuantity());

		for (int i = 0; i < user.getRentCount() ; i++) {
			getline(userFileManager, line);
			idArray.push_back(stoi(line));
		}
		user.setBorrowedEquipmentId(idArray);
		idArray.clear();
	}
	return user;
}


User LoginService::findUserByMail(string mail)
{
	fstream userFileManager;
	userFileManager.open("users.txt", ios::in);

	string line = "";
	User user = User();
	bool userFound = false;


	if (userFileManager.is_open()) {
		while (getline(userFileManager, line)) {

			if (!line.empty()) {

				user = getUserFromFile(userFileManager, line);

				if (user.getMail().compare(mail) == 0) {
					userFound = true;
					break;
				}
			}
		}

		if (userFound) {
			ColorPrinter::printTone("User found", ColorPrinter::GREEN);
			userFileManager.close();
			return user;
		}
		else
		{
			ColorPrinter::printTone("User not found", ColorPrinter::RED);
			user.~User();
			User empty = User();
			userFileManager.close();
			return empty;
		}
	}
	else {
		ColorPrinter::printTone("Couldn't open file", ColorPrinter::RED);
	}

	userFileManager.close();
	user.~User();
	User empty = User();
	return empty;
}
void LoginService::copyUserFromFile(fstream& userFileManager, string& line, User* user)
{
	User newUser = User();

	newUser.setid(stoul(line));

	getline(userFileManager, line);
	newUser.setName(line);

	getline(userFileManager, line);
	newUser.setLastName(line);

	getline(userFileManager, line);
	newUser.setMail(line);

	getline(userFileManager, line);
	newUser.setRole(line);

	getline(userFileManager, line);
	newUser.setPassword(line);

	getline(userFileManager, line);
	newUser.setRentCount(stoi(line));

	getline(userFileManager, line);
	newUser.setMaximumBorrowQuantity(stoi(line));

	if (newUser.getRentCount() > 0) {

		vector<int> idArray;
		idArray.reserve(newUser.getMaximumBorrowQuantity());
		

		for (int i = 0; i < newUser.getRentCount(); i++) {
			
			getline(userFileManager, line);
			idArray.push_back(stoi(line));
			

		}
		newUser.setBorrowedEquipmentId(idArray);
			
		idArray.clear();
	}
	
	*user = newUser;
}