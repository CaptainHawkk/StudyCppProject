#pragma once
#include <iostream>
#include <vector>

using namespace std;

class User
{
	unsigned long int id;
	string name;
	string lastName;
	string mail;
	string role;
	string password;
	int rentCount;
	int maximumBorrowQuantity = 3;
	vector<int> borrowedEquipmentId;

public:

	User();
	User(unsigned long int id,
		string name,
		string mail,
		string role,
		string password);
	~User();
	User(const User& user);
	User operator=(const User& user);

	
	void setid(unsigned long int id);
	void setName(string name);
	void setMail(string mail);
	void setRole(string role);
	void setPassword(string password);
	void setRentCount(int rentCount);
	void setBorrowedEquipmentId(vector<int> borrowedEquipmentId);

	unsigned long int getId() const;
	string getName() const;
	string getMail() const;
	string getRole() const;
	string getPassword() const;
	int getRentCount() const;
	vector<int> getBorowedEquipmentId() const;
	string getLastName() const;
	void incrementRentCount();
	void decrementRentCount();
	void setMaximumBorrowQuantity(int maximumBorrowQuantity);
	int getMaximumBorrowQuantity();
	void setUser();
	void setLastName(string lastName);
	

	friend ostream& operator<< (ostream& wyjscie, const User& user);
};

