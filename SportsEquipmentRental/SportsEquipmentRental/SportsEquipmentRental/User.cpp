#include "User.h"
#include <vector>

User::User():
	id(0),
	name("n"),
	lastName("n"),
	mail("n"),
	role("USER"),
	password("n"),
	rentCount (0),
	maximumBorrowQuantity(3)
	
{
	borrowedEquipmentId.reserve(maximumBorrowQuantity);
}

User::User(unsigned long int id, string name, string mail, string role, string password)
{
	this->id = id;
	this->name = name;
	this->mail = mail;
	this->role = role;
	this->password = password;
}

User::~User() {
	borrowedEquipmentId.clear();
}

User::User(const User& user) {

	
	this->id = user.getId();
	this->name = user.getName();

	this->lastName = user.getLastName();
	this->mail = user.getMail();
	this->role = user.getRole();
	this->password = user.getPassword();
	this->rentCount = user.getRentCount();
	this->borrowedEquipmentId = user.getBorowedEquipmentId();
	
}


User User::operator=(const User& user)
{
	this->id = user.getId();
	this->name = user.getName();
	this->lastName = user.getLastName();
	this->mail = user.getMail();
	this->role = user.getRole();
	this->password = user.getPassword();
	this->rentCount = user.getRentCount();
	this->borrowedEquipmentId = user.getBorowedEquipmentId();

	return  *this;
}


void User::setid(unsigned long int id)
{
	this->id = id;
}

void User::setName(string name)
{
	this->name = name;
}

void User::setMail(string mail)
{
	this->mail = mail;
}

void User::setRole(string role)
{
	this->role = role;
}

void User::setPassword(string password)
{
	this->password = password;
}

void User::setRentCount(int rentCount)
{
	this->rentCount = rentCount;
}

void User::setBorrowedEquipmentId(vector<int> borrowedEquipmentId)
{
	this->borrowedEquipmentId = borrowedEquipmentId;
}

unsigned long int User::getId() const
{
	return this->id;
}

string User::getName()	const
{
	return this->name;
}

string User::getMail() const
{
	return this->mail;
}

string User::getRole() const
{
	return this->role;
}
 
string User::getPassword() const
{
	return this->password;
}

int User::getRentCount() const
{
	return this->rentCount;
}

vector<int> User::getBorowedEquipmentId() const
{
	return this->borrowedEquipmentId;
}

void User::setLastName(string lastName)
{
	this->lastName = lastName;
}


string User::getLastName() const
{
	return this->lastName;
}

void User::setMaximumBorrowQuantity(int maximumBorrowQuantity)
{
	this->maximumBorrowQuantity = maximumBorrowQuantity;
}

int User::getMaximumBorrowQuantity()
{
	return this->maximumBorrowQuantity;
}

void User::incrementRentCount()
{
	this->rentCount++;
}

void User::decrementRentCount()
{
	this->rentCount--;
}




void User::setUser()
{
	
	cout << "Write first name" << endl;
	cin >> this->name;
	cout << "Write last name" << endl;
	cin >> this->lastName;
	cout << "Write mail" << endl;
	cin >> this->mail;
	cout << "Write password" << endl;
	cin >> this->password;
	
}




ostream& operator<<(ostream& wyjscie, const User& user)
{
	cout << "-----------------------" << endl;
	cout << "Id: " << user.id << endl;
	cout << "Name: " << user.name << endl;
	cout << "Last name:" << user.lastName << endl;
	cout << "Mail: " << user.mail << endl;
	cout << "Role: " << user.role << endl;
	cout << "Rent count: " << user.rentCount << endl;
	if (user.rentCount > 0) {
		cout << "Id of rented equipment:" << endl;
		for (int i = 0; i < user.rentCount; i++) {
			cout <<  user.borrowedEquipmentId[i] << endl;
		}
	}
	cout << "-----------------------" << endl << endl;

	return wyjscie;
}
