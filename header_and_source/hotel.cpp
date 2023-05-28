#include"hotel.h"

//helpful tools
int IntLen(int X) //finds how many digits are in the integer
{
    int len=1;
    while(X/10>0)
    {
        len++;
        X=X/10;
    }
    return len;
}
//constructors
Hotel::Hotel()
{
    this->size=0;
    this->rooms=new Room[0];
}
Hotel::Hotel(const Hotel &H)
{
    this->size=H.size;
    this->rooms=new Room[this->size];
    for(int i=0; i<=this->size-1; i++)this->rooms[i]=H.rooms[i];
}
//operators
Hotel &Hotel::operator=(const Hotel &H)
{
    if(this!=&H)
    {
        this->size=H.size;
        delete[] this->rooms;
        this->rooms=new Room[this->size];
        for(int i=0; i<=this->size-1; i++)this->rooms[i]=H.rooms[i];
    }
    return *this;
}
Room &Hotel::operator[](int n)
{
    if(n<0)n=0;
    if(n>this->size-1)n=this->size-1;
    return this->rooms[n];
}
//core methods
void Hotel::StatusRefresh() //checks which rooms' "out of order status" has expired and refreshes them
{
    for(int i=0; i<=this->size-1; i++)
    {   
        if(this->rooms[i].GetTo()<this->rooms[i].GetFrom())
        {
            Date datePlh(this->rooms[i].GetTo());
            this->rooms[i].setTo(this->rooms[i].GetFrom());
            this->rooms[i].setFrom(datePlh);
        }
        if(this->rooms[i].GetTo()<TodaY()) this->rooms[i].Vacate();
    }
}
void Hotel::Sort() //sorts the rooms array by roomNumber
{
    for(int i=0; i<=this->size-1; i++)
    {
        for(int j=0; j<=this->size-1; j++)
        {
            if(this->rooms[i].getRoomNumber()>this->rooms[j].getRoomNumber()) Swap(this->rooms[i], this->rooms[j]);
        }
    }
}
void Hotel::Clear() //clears all info
{
    this->size=0;
    delete[] this->rooms;
    this->rooms=new Room[0];
}
int Hotel::getSize() //gets the number of rooms in the hotel
{
    return this->size;
}
bool Hotel::AddRoom(const Room &R) //adds a new room to the hotel
{
    if(this->CheckIfRoomExists(R.getRoomNumber())==true)return false;
    else
    {
        this->size++;
        Room *plh=new Room[this->size];
        for(int i=0; i<=this->size-2; i++)plh[i]=this->rooms[i];
        plh[this->size-1]=R;
        delete[] this->rooms;
        this->rooms=plh;
        return true;
    }
}
bool Hotel::RemoveRoom(const short rn) //removes a room (uses the roomNumber to find the room)
{
    if(this->CheckIfRoomExists(rn)==true)
    {
        this->size--;
        Room *plh=new Room[this->size];
        int i=0;
        for(; this->rooms[i].getRoomNumber()!=rn; i++)plh[i]=this->rooms[i];
        for(; i<=this->size-1; i++)plh[i]=this->rooms[i+1];
        delete[] this->rooms;
        this->rooms=plh;
        return true;
    }
    else return false;
}
int Hotel::FindRoom(const short rn) //finds a room's position in the rooms array (uses the roomNumber to find the room) (returns -1 if the room doesn't exist)
{
    for(int i=0; i<=this->size-1;i++)if(this->rooms[i].getRoomNumber()==rn)return i;
    return -1;
}
bool Hotel::CheckIfRoomExists(const short rn) //checks if a room with this roomNumber exists in the rooms array
{
    for(int i=0; i<=this->size-1; i++)if(this->rooms[i].getRoomNumber()==rn)return true;
    return false;
}
//files
bool Hotel::ReadFromBin(const std::string FilePath) //reads all info from a binary file (with a given path to the file)
{
    std::fstream f;
    f.open(FilePath, std::ios::in | std::ios::binary);
    if(f.is_open())
    {
        this->Clear();
        int LOOPSIZE=0, intPlh=0;
        bool boolPlh=false;
        short shortPlh=0;
        char *charPlh=nullptr;
        std::string stringPlh="";
        Room roomPlh;
        f.read(reinterpret_cast<char*>(&LOOPSIZE), sizeof(int));
        for(int i=1; i<=LOOPSIZE; i++)
        {
            f.read(reinterpret_cast<char*>(&boolPlh), sizeof(bool));
            roomPlh.setStatus(boolPlh);

            f.read(reinterpret_cast<char*>(&shortPlh), sizeof(short));
            roomPlh.setRoomNumber(shortPlh);
            f.read(reinterpret_cast<char*>(&shortPlh), sizeof(short));
            roomPlh.setNumberOfBeds(shortPlh);
            f.read(reinterpret_cast<char*>(&shortPlh), sizeof(short));
            roomPlh.setNumberOfGuests(shortPlh);

            f.read(reinterpret_cast<char*>(&shortPlh), sizeof(short));
            if(shortPlh<1000)stringPlh=stringPlh+'0';
            if(shortPlh<100)stringPlh=stringPlh+'0';
            if(shortPlh<10)stringPlh=stringPlh+'0';
            stringPlh=stringPlh+std::to_string(shortPlh);
            f.read(reinterpret_cast<char*>(&shortPlh), sizeof(short));
            if(shortPlh<10)stringPlh=stringPlh+'0';
            stringPlh=stringPlh+std::to_string(shortPlh);
            f.read(reinterpret_cast<char*>(&shortPlh), sizeof(short));
            if(shortPlh<10)stringPlh=stringPlh+'0';
            stringPlh=stringPlh+std::to_string(shortPlh);
            roomPlh.setFrom(stringPlh);
            stringPlh="";

            f.read(reinterpret_cast<char*>(&shortPlh), sizeof(short));
            if(shortPlh<1000)stringPlh=stringPlh+'0';
            if(shortPlh<100)stringPlh=stringPlh+'0';
            if(shortPlh<10)stringPlh=stringPlh+'0';
            stringPlh=stringPlh+std::to_string(shortPlh);
            f.read(reinterpret_cast<char*>(&shortPlh), sizeof(short));
            if(shortPlh<10)stringPlh=stringPlh+'0';
            stringPlh=stringPlh+std::to_string(shortPlh);
            f.read(reinterpret_cast<char*>(&shortPlh), sizeof(short));
            if(shortPlh<10)stringPlh=stringPlh+'0';
            stringPlh=stringPlh+std::to_string(shortPlh);
            roomPlh.setTo(stringPlh);
            stringPlh="";

            f.read(reinterpret_cast<char*>(&intPlh), sizeof(int));
            charPlh=new char[intPlh];
            f.read(reinterpret_cast<char*>(charPlh), sizeof(char)*intPlh);
            stringPlh=charPlh;
            roomPlh.setNote(stringPlh);
            delete[]charPlh;
            stringPlh="";

            this->AddRoom(roomPlh);
            roomPlh.Clear();
        }
        f.close();
        return true;
    }
    else return false;
}
bool Hotel::WriteToBin(const std::string FilePath) //writes all info on a binary file (with a given path to the file)
{
    std::fstream f;
    f.open(FilePath, std::ios::out | std::ios::binary | std::ios::trunc);
    if(f.is_open())
    {
        int intPlh=this->size;
        bool boolPlh=false;
        short shortPlh=0;
        char *charPlh=nullptr;
        f.write(reinterpret_cast<const char*>(&intPlh), sizeof(int));
        for(int i=0; i<=this->size-1; i++)
        {
            boolPlh=this->rooms[i].getStatus();
            f.write(reinterpret_cast<const char*>(&boolPlh), sizeof(bool));

            shortPlh=this->rooms[i].getRoomNumber();
            f.write(reinterpret_cast<const char*>(&shortPlh), sizeof(short)); 
            shortPlh=this->rooms[i].getNumberOfBeds();
            f.write(reinterpret_cast<const char*>(&shortPlh), sizeof(short));
            shortPlh=this->rooms[i].getNumberOfGuests();
            f.write(reinterpret_cast<const char*>(&shortPlh), sizeof(short));

            shortPlh=this->rooms[i].GetFrom().getYear();
            f.write(reinterpret_cast<const char*>(&shortPlh), sizeof(short));
            shortPlh=this->rooms[i].GetFrom().getMonth();
            f.write(reinterpret_cast<const char*>(&shortPlh), sizeof(short));
            shortPlh=this->rooms[i].GetFrom().getDay();
            f.write(reinterpret_cast<const char*>(&shortPlh), sizeof(short));

            shortPlh=this->rooms[i].GetTo().getYear();
            f.write(reinterpret_cast<const char*>(&shortPlh), sizeof(short));
            shortPlh=this->rooms[i].GetTo().getMonth();
            f.write(reinterpret_cast<const char*>(&shortPlh), sizeof(short));
            shortPlh=this->rooms[i].GetTo().getDay();
            f.write(reinterpret_cast<const char*>(&shortPlh), sizeof(short));

            intPlh=this->rooms[i].GetNote().length()+1;
            f.write(reinterpret_cast<const char*>(&intPlh), sizeof(int));
            charPlh=new char[intPlh];
            for(int j=0; j<=intPlh-2; j++)charPlh[j]=this->rooms[i].GetNote()[j];
            charPlh[intPlh-1]='\0';
            f.write(reinterpret_cast<const char*>(charPlh), sizeof(char)*intPlh);
            delete[] charPlh;
        }
        f.close();
        return true;
    }
    else return false;
}
//console and txt file output
bool Hotel::TxtPrintAll(const std::string FilePath) //prints all info on a txt file (with a given path to the file)
{
    std::fstream f;
    f.open(FilePath, std::ios::out | std::ios::trunc);
    if(f.is_open())
    {
        f<<"All rooms: "<<this->size<<'\n';
        f<<"|   Status   | Room Number | Beds | Guests | Occupied from | Occupied To | Note"<<'\n';
        f<<"------------------------------------------------------------------------"<<'\n';
        for(int i=0; i<=this->size-1; i++)
        {
            f<<'|';
            if(this->rooms[i].getStatus()==true) f<<" operational";
            else f<<"out of order";
            f<<'|';
            for(short j=1; j<=12-IntLen(this->rooms[i].getRoomNumber()) ;j++) f<<' ';
            f<<this->rooms[i].getRoomNumber();
            f<<" |";
            for(short j=1; j<=5-IntLen(this->rooms[i].getNumberOfBeds()) ;j++) f<<' ';
            f<<this->rooms[i].getNumberOfBeds();
            f<<" |";
            for(short j=1; j<=7-IntLen(this->rooms[i].getNumberOfGuests()) ;j++) f<<' ';
            f<<this->rooms[i].getNumberOfGuests();
            f<<" |    "<<this->rooms[i].GetFrom()<<" |  "<<this->rooms[i].GetTo()<<" | "<<this->rooms[i].GetNote()<<'\n';
        }
        f.close();
        return true;
    }
    else return false;
}
void Hotel::ConsolePrintAll() //prints all info on the console
{
    std::cout<<"All rooms: "<<this->size<<std::endl;
    std::cout<<"------------------------------------------------------------------------"<<std::endl;
    std::cout<<"|   Status   | Room Number | Beds | Guests | Occupied from | Occupied To | Note"<<std::endl;
    std::cout<<"------------------------------------------------------------------------"<<std::endl;
    for(int i=0; i<=this->size-1; i++)
    {   
        std::cout<<'|';
        if(this->rooms[i].getStatus()==true) std::cout<<" operational";
        else std::cout<<"out of order";
        std::cout<<'|';
        for(short j=1; j<=12-IntLen(this->rooms[i].getRoomNumber()) ;j++) std::cout<<' ';
        std::cout<<this->rooms[i].getRoomNumber();
        std::cout<<" |";
        for(short j=1; j<=5-IntLen(this->rooms[i].getNumberOfBeds()) ;j++) std::cout<<' ';
        std::cout<<this->rooms[i].getNumberOfBeds();
        std::cout<<" |";
        for(short j=1; j<=7-IntLen(this->rooms[i].getNumberOfGuests()) ;j++) std::cout<<' ';
        std::cout<<this->rooms[i].getNumberOfGuests();
        std::cout<<" |    "<<this->rooms[i].GetFrom()<<" |  "<<this->rooms[i].GetTo()<<" | "<<this->rooms[i].GetNote()<<std::endl;
    }
}
//destructor
Hotel::~Hotel()
{
    delete[] this->rooms;
}