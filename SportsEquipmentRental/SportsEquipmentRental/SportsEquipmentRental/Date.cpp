#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"
#include <ctime>
#include <iostream>
#include <string>



Date::Date()
{
    time_t t = time(0);   // get time now
    tm* now = localtime(&t);
    this->year = (now->tm_year + 1900);
    this->month = (now->tm_mon + 1);
    this->day = now->tm_mday;
      
}

Date::Date(unsigned short day, unsigned short month, unsigned short year)
{
    this->day = day;
    this->month = month;
    this->year = year;
    dateValidator();
}

Date::~Date()
{
}

void Date::setDate(unsigned short day, unsigned short month, unsigned short year)
{
	this->day = day;
	this->month = month;
	this->year = year;
    dateValidator();
}


void Date::printDate()
{
    std::cout << day << "-" << month << "-" << year << std::endl;
}


void Date::dateValidator()
{
    unsigned short d_day;
    unsigned short d_month;
    unsigned short d_year;
    
    d_day = day;
    d_month = month;
    d_year = year;


    //month validation
    if (d_month > 12) {
        d_month = 12;
    }
    else if (d_month < 1) {
        d_month = 1;
    }

    //day validation including leap-year
    if (d_month == 1 || d_month == 3 || d_month == 5 || d_month == 7 || d_month == 8 || d_month == 10 || d_month == 12) {
        if (d_day > 31) {
            d_day = 31;
        }
        else if(d_day < 1){
            d_day = 1;
        }
    }
    else if (d_month == 4 || d_month == 6 || d_month == 9 || d_month == 11)
    {
        if (d_day > 30) {
            d_day = 30;
        }
        else if (d_day < 1) {
            d_day = 1;
        }
    }
    else
    {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            if (d_day > 29) {
                d_day = 29;
            }
            else if (d_day < 1) {
                d_day = 1;
            }
        }
        else
        {
            if (d_day > 28) {
                d_day = 28;
            }
            else if (d_day < 1) {
                d_day = 1;
            }
        }
    }

    this->day = d_day;
    this->month = d_month;
    this->year = d_year;
}



 bool Date::the30DayHasPassed(Date date)
{
    unsigned short today_day;
    unsigned short today_month;
    unsigned short today_year;

    time_t t = time(0);   // get time now
    tm* now = localtime(&t);
    today_year = (now->tm_year + 1900);
    today_month = (now->tm_mon + 1);
    today_day = now->tm_mday;

    //first checkout if equal
    if (today_year == date.year) {
        if (today_month == date.month) {
            if (today_day == date.day) {
                return false; 
            }
            //longer than 1 month
        } else if ((today_month - date.month) > 1) {
            return true;
            //equal 1 month
        } else if ((today_month - date.month) == 1) {
                //find out if more than 30 days
            if (today_day  - date.day <= 0) { 
                return false; 
            } else {
                return true;
            } 
        } else return false;
    }

    //December a January
    else if (today_year == (date.year + 1)) {
        //find out  
        if ((today_year == 12) && (date.month == 1)) {
            //check out if 30 day oassed
            if ((today_day - date.day) <= 0) {
                return false; 
            } else {
                return true;
            }
            //check out if lack is more than month
        } else if (((today_month + 12) - date.month) > 1) {
            return true;
        } else {
            return false;
        }
    }

    //longer than year
    else if (today_year > date.year + 1) {
        return true;
    }

    //rental in future?
    else if (today_year < date.year) {
        return false;
    }

    else {
        return true;
    }

}


void Date::setDay(int day)
{
    this->day = day;
}


void Date::setMonth(int month)
{
    this->month = month;
}


void Date::setYear(int year)
{
    this->year = year;
}



int Date::getDay()
{
    return this->day;
}


int Date::getMonth()
{
    return this->month;
}


int Date::getYear()
{
    return this->year;
}

ostream& operator<<(ostream& output, const Date& date)
{
    cout << date.day << "-" << date.month << "-" << date.year << endl;
    return output;
}
