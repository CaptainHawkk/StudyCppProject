#include "Equipment.h"
#include <iostream>
#include "ColorPrinter.h"


Equipment::Equipment()
{
	this->id = 0;
	this->name = "n";
	this->type = "n";
	this->borrower = "n";
	this->rentalPrice = 0.0;
	this->rentalDate = Date(1,1,0);
	this->rented = false;
}

Equipment::~Equipment()
{
}

void Equipment::setEquipmentData()
{
	ColorPrinter::printTone("Write name", ColorPrinter::GREY, false);
	cin >> name;
	ColorPrinter::printTone("Write type", ColorPrinter::GREY, false);
	cin >> type;
	ColorPrinter::printTone("Write Rental price", ColorPrinter::GREY, false);
	cin >> rentalPrice;
	rented = false;
	rentalDate = Date(1,1,0);
	borrower = "n";
}


void Equipment::setId(unsigned long int id)
{
	this->id = id;
}


void Equipment::setName(string name)
{
	this->name = name;
}


void Equipment::setType(string type)
{
	this->type = type;
}


void Equipment::setRentalPrice(double rentalPrice)
{
	this->rentalPrice = rentalPrice;
}


void Equipment::setRented(bool rented)
{
	this->rented = rented;
}


void Equipment::setRentalDate(Date rentalDate)
{
	this->rentalDate = rentalDate;
}


void Equipment::setBorrower(string borrower)
{
	this->borrower = borrower;
}


unsigned long int Equipment::getId()
{
	return this->id;
}


string Equipment::getName()
{
	return this->name;
}


string Equipment::getType()
{
	return this->type;
}


double Equipment::getRentalPrice()
{
	return this->rentalPrice;
}


bool Equipment::getRented()
{
	return this->rented;
}


Date Equipment::getRentalDate()
{
	return this->rentalDate;
}


string Equipment::getBorrower()
{
	return this->borrower;
}
