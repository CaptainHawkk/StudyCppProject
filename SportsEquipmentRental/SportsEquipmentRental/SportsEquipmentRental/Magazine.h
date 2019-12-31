#pragma once
#include <string>
#include <fstream>

using namespace std;

class Magazine
{
	string name = "SportEquipmentMagazine";
	int maximumCapacity = 50;
	int actualCapacity = 0;

	void getMagazineDataFromFile();

public:

	Magazine();

	~Magazine();


	int getMaximumCapacity();
	int getActualCapacity();
	void setActualCapacity(int actualCapacity);
	void incrementActualCapacity();
	void decrementActualCapacity();
	string getName();
	
	bool magazineIsFull();
};

