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


unsigned long int Equipment::getId() const
{
	return this->id;
}


string Equipment::getName() const
{
	return this->name;
}


string Equipment::getType() const
{
	return this->type;
}


double Equipment::getRentalPrice() const
{
	return this->rentalPrice;
}


bool Equipment::getRented() const
{
	return this->rented;
}


Date Equipment::getRentalDate() const
{
	return this->rentalDate;
}


string Equipment::getBorrower() const
{
	return this->borrower;
}

ostream& operator<<(ostream& output, const Equipment& equipment)
{
	ColorPrinter::printTone("-------------------------------------", ColorPrinter::YELLOW); 
	cout << endl;
	cout << "   Id: " << equipment.id << endl;
	cout << "   Type: " << equipment.type << endl;
	cout << "   Name: " << equipment.name << endl;
	cout << "   Borrower: " << equipment.borrower << endl;
	cout << "   Rental price: " << equipment.rentalPrice << endl;
	cout << "   Rental date: " << equipment.rentalDate;
	cout << "   Rented: " << equipment.rented << endl << endl;
	ColorPrinter::printTone("-------------------------------------", ColorPrinter::YELLOW);
	return output;
}
