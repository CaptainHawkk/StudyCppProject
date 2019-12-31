#include "Magazine.h"
#include <iostream>



void Magazine::getMagazineDataFromFile()
{
	ifstream savedEquipment;
	int magazineItemsQuantity = 0;
	string line = "";

	savedEquipment.open("equipment.txt");
	while (getline(savedEquipment, line)) {
		if (line.empty()) {
			magazineItemsQuantity++;
		}
	}
	std::cout << magazineItemsQuantity << endl;
	this->setActualCapacity(magazineItemsQuantity);
}

Magazine::Magazine()
{
	this->getMagazineDataFromFile();
}

Magazine::~Magazine()
{
}

int Magazine::getMaximumCapacity()
{
	return this->maximumCapacity;
}


int Magazine::getActualCapacity()
{
	return this->actualCapacity;
}


void Magazine::setActualCapacity(int actualCapacity)
{
	this->actualCapacity = actualCapacity;
}


void Magazine::incrementActualCapacity()
{
	this->setActualCapacity(this->getActualCapacity() + 1);
}


void Magazine::decrementActualCapacity()
{
	this->setActualCapacity(this->getActualCapacity() - 1);
}


string Magazine::getName()
{
	return name;
}


bool Magazine::magazineIsFull()
{
	if (this->actualCapacity == this->maximumCapacity)
		return true;
	else
		return false;
}
