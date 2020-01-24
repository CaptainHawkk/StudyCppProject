#pragma once
#include <fstream>
#include <string>

using namespace std;

class IdController
{
	unsigned long int userNextId;
	unsigned long int equipmentNextId;
public:

	IdController();
	~IdController();

	int getUserNextId();
	int getEquipmentNextId();
	void setUserNextId(unsigned long int id);
	void setEquipmentNextId(unsigned long int id);


	void incrementUserNextId();
	void incrementEquipmentNextId();
};



