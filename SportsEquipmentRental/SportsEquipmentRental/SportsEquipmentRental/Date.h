#pragma once
class Date
{
	unsigned short day;
	unsigned short month;
	unsigned short year;
public:

	Date();
	Date(unsigned short day, unsigned short month, unsigned short year);
	~Date();

	void setDate(unsigned short day, unsigned short month, unsigned short year);
	void printDate();
	void dateValidator();

	static bool the30DayHasPassed(Date date);

	void setDay(int day);
	void setMonth(int month);
	void setYear(int year);
	int getDay();
	int getMonth();
	int getYear();
};

