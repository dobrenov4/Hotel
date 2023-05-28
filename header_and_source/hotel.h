#ifndef hotel_H
#define hotel_H
#include<fstream>
#include"room.h"

class Hotel
{
    private:
    //member-data
    int size;
    Room *rooms;

    public:
    //constructors
    Hotel();
    Hotel(const Hotel &H);
    //operators
    Hotel &operator=(const Hotel &H);
    Room &operator[](int n);
    //core methods
    void StatusRefresh(); //checks which rooms' "out of order status" has expired and refreshes them
    void Sort(); //sorts the rooms array by roomNumber
    void Clear(); //clears all info
    int getSize(); //gets the number of rooms in the hotel
    bool AddRoom(const Room &R); //adds a new room to the hotel
    bool RemoveRoom(const short rn); //removes a room (uses the roomNumber to find the room)
    int FindRoom(const short rn); //finds a room's position in the rooms array (uses the roomNumber to find the room)
    bool CheckIfRoomExists(const short rn); //checks if a room with this roomNumber exists in the rooms array
    //binary files
    bool ReadFromBin(const std::string FilePath); //reads all info from a binary file (with a given path to the file)
    bool WriteToBin(const std::string FilePath); //writes all info on a binary file (with a given path to the file)
    //console and txt file output
    bool TxtPrintAll(const std::string FilePath); //prints all info on a txt file (with a given path to the file)
    void ConsolePrintAll(); //prints all info on the console
    //destructor
    ~Hotel();
};

//helpful tools
int IntLen(int X); //finds how many digits are in the integer

#endif