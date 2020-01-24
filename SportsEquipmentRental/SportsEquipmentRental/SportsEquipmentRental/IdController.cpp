#include "IdController.h"


IdController::IdController() {
	fstream userIdFileManager;
	fstream equipmentIdFileManager;

	userIdFileManager.open("userId.txt", ios::in);
	equipmentIdFileManager.open("equipmentId.txt", ios::in);

	string line = "";

	if (userIdFileManager.is_open()) {

		getline(userIdFileManager, line);
		this->userNextId = stoul(line);
	}
	else {
		this->userNextId = 1;
	}

	if (equipmentIdFileManager.is_open()) {

		getline(equipmentIdFileManager, line);
		this->equipmentNextId = stoul(line);
	}
	else
		this->equipmentNextId = 1;

	userIdFileManager.close();
	equipmentIdFileManager.close();

}

IdController::~IdController() {
	fstream userIdFileManager;
	fstream equipmentIdFileManager;


	userIdFileManager.open("userId_temp.txt", ios::out);
	equipmentIdFileManager.open("equipmentId_temp.txt", ios::out);

	if (userIdFileManager.is_open()) {

		userIdFileManager << this->userNextId;
	}

	if (equipmentIdFileManager.is_open()) {

		equipmentIdFileManager << this->equipmentNextId;
	}

	userIdFileManager.close();
	equipmentIdFileManager.close();

	remove("userId.txt");
	remove("equipmentId.txt");
	rename("userId_temp.txt", "userId.txt");
	rename("equipmentId_temp.txt", "equipmentId.txt");

}

int IdController::getUserNextId()
{
	return this->userNextId;
}


int IdController::getEquipmentNextId()
{
	return this->equipmentNextId;
}


void IdController::setUserNextId(unsigned long int id)
{
	this->userNextId = id;
}


void IdController::setEquipmentNextId(unsigned long int id)
{
	this->equipmentNextId = id;
}


void IdController::incrementUserNextId()
{
	this->userNextId++;
}


void IdController::incrementEquipmentNextId()
{
	this->equipmentNextId++;
}
