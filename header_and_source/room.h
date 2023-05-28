#ifndef room_H
#define room_H
#include"date.h"

class Room //a class that represents
{
    private:
    //member-data
    bool status;
    short roomNumber;
    short numberOfBeds;
    short numberOfGuests;
    Date from; //the beginning date of occupation or use
    Date to; //the ending date of occupation or use
    std::string note;
    public:
    //constructors
    Room();
    Room(const bool s,const short rn,const short nob, const short nog, const Date &F, const Date &T, const std::string n);
    Room(const Room &R);
    //operators
    Room &operator=(const Room &R);
    bool operator==(const Room &R);
    bool operator!=(const Room &R);
    //core methods
    bool CheckAvailable(); //checks if the room is available for use or not
    void Clear(); //sets the room back to default value 
    void Vacate(); //makes the room available for use again (keeps roomNumber and numberOfBeds)
    //getters and setters
    bool getStatus() const;
    short getRoomNumber() const;
    short getNumberOfBeds() const;
    short getNumberOfGuests() const;
    Date GetFrom() const;
    Date GetTo() const;
    std::string GetNote() const;
    void setStatus(const bool s);
    void setRoomNumber(const short rn);
    void setNumberOfBeds(const short nob);
    void setNumberOfGuests(const short nog);
    void setFrom(const Date &F);
    void setTo(const Date &T);
    void setNote(const std::string n);
    //friends
    friend void SwapStats(Room &R1, Room &R2); //swaps 2 room's stats (keeps roomNumber and numberOfBeds)
    friend void Swap(Room &R1, Room &R2); //swaps all stats between 2 rooms
    //destructor
    ~Room()=default;
};

#endif
