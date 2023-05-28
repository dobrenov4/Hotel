//Dimitar Dobrenov - 9MI0800108  - FMI

#include"date.h"

//constructors
Date::Date(): year(0), month(1), day(1){}
Date::Date(const std::string &d) //a constructor that takes a string in order to make a date
{
    if(CheckDateValidity(d)==false)
    {
        this->year=0;
        this->month=1;
        this->day=1;
    }
    else
    {
        if(d.length()==8)
        {
            this->year=(d[0]-'0')*1000+(d[1]-'0')*100+(d[2]-'0')*10+(d[3]-'0');
            this->month=(d[4]-'0')*10+(d[5]-'0');
            this->day=(d[6]-'0')*10+(d[7]-'0');
        }
        else 
        {
            this->year=(d[0]-'0')*1000+(d[1]-'0')*100+(d[2]-'0')*10+(d[3]-'0');
            this->month=(d[5]-'0')*10+(d[6]-'0');
            this->day=(d[8]-'0')*10+(d[9]-'0');
        }
    }
}
Date::Date(const Date &D)
{
    this->year=D.year;
    this->month=D.month;
    this->day=D.day;
}

//operators
Date &Date::operator=(const Date &D)
{
    if(this!=&D)
    {
        this->year=D.year;
        this->month=D.month;
        this->day=D.day;
    }
    return *this;
}
bool Date::operator==(const Date &D) const
{
    if(this->day==D.day && this->month==D.month && this->year==D.year)return true;
    else return false;
}
bool Date::operator!=(const Date &D) const
{
    if(*this==D)return false;
    else return true;
}
bool Date::operator>(const Date &D) const
{
    if(this->year>D.year)return true;
    else
    {
        if(this->year<D.year)return false;
        else
        {
            if(this->month>D.month)return true;
            else
            {
                if(this->month<D.month)return false;
                else
                {
                    if(this->day>D.day)return true;
                    else return false;
                }
            }
        }
    }
}
bool Date::operator<(const Date &D) const
{
    if(*this>D || *this==D)return false;
    else return true;

}
bool Date::operator>=(const Date &D) const
{
    if(*this>D || *this==D)return true;
    else return false;
}
bool Date::operator<=(const Date &D) const
{
    if(*this<D || *this==D)return true;
    else return false; 
}

std::istream &operator>>(std::istream &is, Date &D)
{
    std::string in;
    is>>in;
    if(CheckDateValidity(in)==true)
    {
        D.Set(in);
    }
    return is;
}
std::ostream& operator<<(std::ostream &os, const Date &D)
{
    if(D.getYear()<1000)os<<'0';
    if(D.getYear()<100)os<<'0';
    if(D.getYear()<10)os<<'0';
    os<<D.getYear()<<'-';
    if(D.getMonth()<10)os<<'0';
    os<<D.getMonth()<<'-';
    if(D.getDay()<10)os<<'0';
    os<<D.getDay();
    return os;
}
//core methods
bool Date::Set(const std::string &d) //sets a new date (also checks validity)
{
    if(CheckDateValidity(d)==false) return false;
    else
    {
        if(d.length()==8)
        {
            this->year=(d[0]-'0')*1000+(d[1]-'0')*100+(d[2]-'0')*10+(d[3]-'0');
            this->month=(d[4]-'0')*10+(d[5]-'0');
            this->day=(d[6]-'0')*10+(d[7]-'0');
        }
        else 
        {
            this->year=(d[0]-'0')*1000+(d[1]-'0')*100+(d[2]-'0')*10+(d[3]-'0');
            this->month=(d[5]-'0')*10+(d[6]-'0');
            this->day=(d[8]-'0')*10+(d[9]-'0');
        }
        return true;
    }
}
void Date::Clear() //sets the date back to default value (0000-01-01)
{
    this->year=0;
    this->month=1;
    this->day=1;
}
//getters
short Date::getYear() const
{
    return this->year;
}

short Date::getMonth() const
{
    return this->month;
}
short Date::getDay() const
{
    return this->day;
}
//helpful tools
bool CheckLeapYear(const int y) //checks if the integer represents a leap year
{
    if(y%4!=0 || (y%100==0 && y%400!=0))return false;
    else return true;
}
bool CheckDateValidity(const std::string d) //checks if the string represents a valid date in ISO-8601 format
{
    if(d.length()!=8 && d.length()!=10)return false;
    short yy=0, mm=0, dd=0;
    if(d.length()==8)
    {
        for(short i=0; i<7; i++) if(d[i]<'0' || d[i]>'9')return false;
        yy=(d[0]-'0')*1000+(d[1]-'0')*100+(d[2]-'0')*10+(d[3]-'0');
        mm=(d[4]-'0')*10+(d[5]-'0');
        dd=(d[6]-'0')*10+(d[7]-'0');
    }
    if(d.length()==10)
    {
        for(short i=0; i<7; i++)
        {
            if(i==4 || i==7)i++;
            if(d[i]<'0' || d[i]>'9')return false;
        }
        yy=(d[0]-'0')*1000+(d[1]-'0')*100+(d[2]-'0')*10+(d[3]-'0');
        mm=(d[5]-'0')*10+(d[6]-'0');
        dd=(d[8]-'0')*10+(d[9]-'0');
    }
    if(dd>31 || mm>12 || dd<1 || mm<1 || yy>9999)return false;
    if(dd==31 && (mm==2 || mm==4 || mm==6 || mm==9 || mm==11))return false;
    if(mm==2 && dd>29)return false;
    if(mm==2 && dd==29 && CheckLeapYear(yy)==false)return false;
    return true;
}
int NumberOfDaysBetween(const Date D1,const Date D2) //gets the days that have passed between 2 dates
{
    int days_passed_1=0, days_passed_2=0;
    days_passed_1=D1.getDay();
    for(int i=D1.getMonth()-1; i>=1; i--)
    {
        if(i==2 && CheckLeapYear(D1.getYear())==true)days_passed_1=days_passed_1+29;
        else if(i==2)days_passed_1=days_passed_1+28;
        if(i==1 || i==3 || i==5 || i==7 || i==8 || i==10 || i==12)days_passed_1=days_passed_1+31;
        if(i==4 || i==6 || i==9 || i==11)days_passed_1=days_passed_1+30;
    }
    days_passed_1=days_passed_1+D1.getYear()*365;
    days_passed_1=days_passed_1+(D1.getYear()/4);
    days_passed_1=days_passed_1-(D1.getYear()/100);
    days_passed_1=days_passed_1+(D1.getYear()/400);
    days_passed_2=D2.getDay();
    for(int i=D2.getMonth()-1; i>=1; i--)
    {
        if(i==2 && CheckLeapYear(D2.getYear())==true)days_passed_2=days_passed_2+29;
        else if(i==2)days_passed_2=days_passed_2+28;
        if(i==1 || i==3 || i==5 || i==7 || i==8 || i==10 || i==12)days_passed_2=days_passed_2+31;
        if(i==4 || i==6 || i==9 || i==11)days_passed_2=days_passed_2+30;
    }
    days_passed_2=days_passed_2+D1.getYear()*365;
    days_passed_2=days_passed_2+(D1.getYear()/4);
    days_passed_2=days_passed_2-(D1.getYear()/100);
    days_passed_2=days_passed_2+(D1.getYear()/400);
    if(days_passed_1>days_passed_2)std::swap(days_passed_1,days_passed_2);
    return days_passed_2-days_passed_1;
}
Date TodaY() //gives today's date in IOS-8601 format
{   //code for this was taken form: https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm#
    time_t now = time(0);
    tm *ltm = localtime(&now);
    short y=1900+ltm->tm_year, m=1+ltm->tm_mon, d=ltm->tm_mday;
    std::string stringPlh=std::to_string(y);
    if(m<10) stringPlh=stringPlh+'0';
    stringPlh=stringPlh+std::to_string(m);
    if(d<10) stringPlh=stringPlh+'0';
    stringPlh=stringPlh+std::to_string(d);
    Date today(stringPlh);
    return today;
}
//friends
void Swap(Date &D1, Date &D2)
{
    std::swap(D1.year, D2.year);
    std::swap(D1.month, D2.month);
    std::swap(D1.day, D2.day);
}
