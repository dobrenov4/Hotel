//Dimitar Dobrenov - 9MI0800108  - FMI

#ifndef date_H
#define date_H
#include<string>
#include<iostream>
#include<ctime>

class Date //a date class that works only with ISO-8601 format
{
    private:
    //member-data
    short year;
    short month;
    short day;

    public:
    //constructors
    Date();
    Date(const std::string &d);
    Date(const Date &D);
    //operators
    Date &operator=(const Date &D);
    bool operator==(const Date &D) const;
    bool operator!=(const Date &D) const;
    bool operator>(const Date &D) const;
    bool operator<(const Date &D) const;
    bool operator>=(const Date &D) const;
    bool operator<=(const Date &D) const;
    friend std::istream &operator>>(std::istream &is, Date &D);
    friend std::ostream &operator<<(std::ostream &os, const Date &D);
    //core methods
    bool Set(const std::string &d); //sets a new date (also checks validity)
    void Clear(); //sets the date back to default value (0000-01-01)
    //getters
    short getYear() const;
    short getMonth() const;
    short getDay() const;
    //friends
    friend void Swap(Date &D1, Date &D2);
    //destructor
    ~Date()=default;
};

//helpful tools
bool CheckLeapYear(const int y); //checks if the integer represents a leap year
bool CheckDateValidity(const std::string d); //checks if the string represents a valid date in ISO-8601 format
int NumberOfDaysBetween(const Date D1, const Date D2); //gets the days that have passed between 2 dates
Date TodaY(); //gives today's date in IOS-8601 format

#endif