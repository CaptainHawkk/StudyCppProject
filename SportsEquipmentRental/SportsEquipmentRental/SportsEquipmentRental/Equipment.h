#pragma once
#include "Date.h"
#include <string>

using namespace std;

class Equipment
{
	unsigned long int id;
	string name;
	string type;
	string borrower;
	double rentalPrice;
	Date rentalDate;
	bool rented;

public:

	Equipment();
	~Equipment();

	void setEquipmentData();

	void setId(unsigned long int id);
	void setName(string name);
	void setType(string type);
	void setRentalPrice(double rentalPrice);
	void setRented(bool rented);
	void setRentalDate(Date date);
	void setBorrower(string borrower);
	
	unsigned long int getId();
	string getName();
	string getType();
	double getRentalPrice();
	bool getRented();
	Date getRentalDate();
	string getBorrower();

	friend ostream& operator<< (ostream& wyjscie, const Equipment& equipment);


};

