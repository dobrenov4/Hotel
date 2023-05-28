//Dimitar Dobrenov - 9MI0800108  - FMI

#include"room.h"

//constructors
Room::Room():
status(true), roomNumber(0), numberOfBeds(0), numberOfGuests(0), from(), to(), note(){}
Room::Room(const bool s,const short rn,const short nob, const short nog, const Date &F, const Date &T, const std::string n):
status(s), roomNumber(rn), numberOfBeds(nob), numberOfGuests(nog), from(F), to(T), note(n)
{
    if(this->from>this->to)Swap(this->from,this->to);
}
Room::Room(const Room &R):
status(R.status), roomNumber(R.roomNumber), numberOfBeds(R.numberOfBeds), numberOfGuests(R.numberOfGuests), from(R.from), to(R.to), note(R.note){}
//operators
Room &Room::operator=(const Room &R)
{
    if(this!=&R)
    {
        this->status=R.status;
        this->roomNumber=R.roomNumber;
        this->numberOfBeds=R.numberOfBeds;
        this->numberOfGuests=R.numberOfGuests;
        this->from=R.from;
        this->to=R.to;
        this->note=R.note;
    }
    return *this;
}
bool Room::operator==(const Room &R)
{
    if(this->status==R.status &&
       this->roomNumber==R.roomNumber &&
       this->numberOfBeds==R.numberOfBeds &&
       this->numberOfGuests==R.numberOfGuests &&
       this->from==R.from &&
       this->to==R.to && 
       this->note==R.note) return true;
    else return false;
}
bool Room::operator!=(const Room &R)
{
    if(*this==R)return false;
    else return true;
}
//core methods
bool Room::CheckAvailable() //checks if the room is available for use or not
{
    if(this->status==true &&
       this->numberOfGuests==0 &&
       this->from.getYear()==0 &&
       this->from.getMonth()==1 &&
       this->from.getDay()==1 &&
       this->to.getYear()==0 &&
       this->to.getMonth()==1 &&
       this->to.getDay()==1 &&
       this->note=="") return true;
    else return false;
}
void Room::Clear() //sets the room back to default value 
{
    this->status=true;
    this->roomNumber=0;
    this->numberOfBeds=0;
    this->numberOfGuests=0;
    this->from.Clear();
    this->to.Clear();
    this->note.clear();
}
void Room::Vacate() //makes the room available for use again (keeps roomNumber and numberOfBeds)
{
    this->status=true;
    this->numberOfGuests=0;
    this->from.Clear();
    this->to.Clear();
    this->note.clear();
}
//getters and setters
bool Room::getStatus() const
{
    return this->status;
}
short Room::getRoomNumber() const
{
    return this->roomNumber;
}
short Room::getNumberOfBeds() const
{
    return this->numberOfBeds;
}
short Room::getNumberOfGuests() const
{
    return this->numberOfGuests;
}
Date Room::GetFrom() const
{
    return this->from;
}
Date Room::GetTo() const
{
    return this->to;
}
std::string Room::GetNote() const
{
    return this->note;
}
void Room::setStatus(const bool s)
{
    this->status=s;
}
void Room::setRoomNumber(const short rn)
{
    this->roomNumber=rn;
}
void Room::setNumberOfBeds(const short nob)
{
    this->numberOfBeds=nob;
}
void Room::setNumberOfGuests(const short nog)
{
    if(this->numberOfBeds<=nog) this->numberOfGuests=this->numberOfBeds;
    else this->numberOfGuests=nog;
}
void Room::setFrom(const Date&F)
{
    this->from=F;
}
void Room::setTo(const Date &T)
{
    this->to=T;
}
void Room::setNote(const std::string n)
{
    this->note=n;
}
//friends
void SwapStats(Room &R1, Room &R2) // swaps 2 room's stats (keeps roomNumber and numberOfBeds)
{
    std::swap(R1.status, R2.status);
    std::swap(R1.numberOfGuests, R2.numberOfGuests);
    Swap(R1.from, R2.from);
    Swap(R1.to, R2.to);
    std::swap(R1.note, R2.note);
}
void Swap(Room &R1, Room &R2) //swaps all stats between 2 rooms
{
    std::swap(R1.status, R2.status);
    std::swap(R1.roomNumber, R2.roomNumber);
    std::swap(R1.numberOfBeds, R2.numberOfBeds);
    std::swap(R1.numberOfGuests, R2.numberOfGuests);
    Swap(R1.from, R2.from);
    Swap(R1.to, R2.to);
    std::swap(R1.note, R2.note);
}