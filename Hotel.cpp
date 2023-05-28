//Dimitar Dobrenov - 9MI0800108  - FMI

#include"header_and_source\\hotel.h"

const std::string defaultFilePath="", ADMIN_PASSWORD="admin"; //(a default file path), (an administrator password)

void LineSpacer() //just a spacer for consistency
{
std::cout<<"-------------------------------------------------------------------"<<'\n';
}
void SmallLineSpacer() //small spacer for consistency
{
std::cout<<"------------------------------"<<'\n';
}
void Intro() //an into for extra style
{
std::cout<<"admin password: "<<ADMIN_PASSWORD<<'\n';
std::cout<<"-------------------------------------------------------------------"<<'\n';
std::cout<<"---------------------------   WELCOME   ---------------------------"<<'\n';
}
int CommandToInt(std::string S) //takes the command and gives out an integer (makes working with the commands easier)
{
    if(S=="Exit" || S=="exit")return 0;
    if(S=="help")             return 1;
    if(S=="open")             return 2;
    if(S=="close")            return 3;
    if(S=="save")             return 4;
    if(S=="save as")          return 5;

    if(S=="checkin")          return 6;
    if(S=="availability")     return 7;
    if(S=="checkout")         return 8;
    if(S=="report")           return 9;
    if(S=="find")             return 10;
    if(S=="find!")            return 11;
    if(S=="unavailable")      return 12;
    if(S=="return to use")    return 13;

    if(S=="show all info")    return 14;
    if(S=="print all info")   return 15;

    if(S=="add room")         return 16;
    if(S=="remove room")      return 17;

    return -100;
}

int main()
{
    std::string currentFilePath=defaultFilePath, command="exit"; //(the path to the currently opened file), (the current command)
    Hotel hotel; //the main working object (form class Hotel)

    Intro();

    do{ //the main loop of the program
        //command="exit";
        LineSpacer();
        std::cout<<"Enter command:";
        std::getline(std::cin, command);
        switch(CommandToInt(command))
        {
            //core commands:
            case 0: //exit
            {
                LineSpacer();
                std::cout<<"---  EXIT  ---"<<std::endl;
                LineSpacer();
                break;
            }

            case 1: //help
            {
                LineSpacer();
                std::cout<<"Available commands:"<<std::endl;
                std::cout<<"exit            | exits the program"<<std::endl;
                std::cout<<"help            | shows list of available commands"<<std::endl;
                std::cout<<"open            | opens a data file"<<std::endl;
                std::cout<<"close           | closes the data file "<<std::endl;
                std::cout<<"save            | saves to the current data file"<<std::endl;
                std::cout<<"save as         | saves to a new data file"<<std::endl;
                std::cout<<"checkin         | checks in new guests"<<std::endl;
                std::cout<<"availability    | shows a list with all available rooms on a given date"<<std::endl;
                std::cout<<"checkout        | checks out guests"<<std::endl;
                std::cout<<"report          | shows a report for room use in a give period"<<std::endl;
                std::cout<<"find            | shows a list of free rooms in a given period"<<std::endl;
                std::cout<<"find!           | temporarily disabled (a lot of undefined behaviour) "<<std::endl;
                std::cout<<"unavailable     | makes a room unavailable until further specified"<<std::endl;
                std::cout<<"return to use   | returns an unavailable room back to use"<<std::endl;
                std::cout<<"show all info   | shows a list of all the info in the system"<<std::endl;
                std::cout<<"print all info  | saves all info in the system in a text file"<<std::endl;
                std::cout<<"---  -------------------------------------------  ---"<<std::endl;
                std::cout<<"Administrator commands (admin password is required):"<<std::endl;
                std::cout<<"add room        | adds a new room to the hotel"<<std::endl;
                std::cout<<"remove room     | removes a room from the hotel"<<std::endl;
                break;
            }

            case 2: //open
            {
                LineSpacer();
                std::cout<<"Enter file path:";
                std::getline(std::cin, currentFilePath);
                if(hotel.ReadFromBin(currentFilePath)==true) std::cout<<"---  FILE OPENED SUCCESSFULLY  ---"<<std::endl;
                else std::cout<<"---  FAILED TO OPEN FILE  ---"<<std::endl;
                break;
            }

            case 3: //close
            {
                LineSpacer();
                if(currentFilePath=="")std::cout<<"---  NO FILE IS OPENED  ---"<<std::endl;
                else
                {
                    std::cout<<"You are about to close the working file. Are you sure [Y/N]? ";
                    char checker='n';
                    std::cin>>checker;
                    std::cin.ignore();
                    if(checker=='Y' || checker=='y')
                    {
                        hotel.Clear();
                        currentFilePath="";
                        std::cout<<"---  FILE CLOSED  ---"<<std::endl;
                    }
                    else 
                    {
                        std::cout<<"--- OPERATION ABORTED - GOING BACK TO MAIN MENU ---"<<std::endl;
                    }
                }
                break;
            }

            case 4: //save
            {
                LineSpacer();
                if(currentFilePath=="") std::cout<<"---  NO FILE IS OPENED  ---"<<std::endl;
                else
                {
                    hotel.StatusRefresh();
                    if(hotel.WriteToBin(currentFilePath)==true) std::cout<<"---  SAVED SUCCESSFULLY  ---"<<std::endl;
                    else std::cout<<"---  FAILED TO SAVE  ---"<<std::endl;
                }
                break;
            }

            case 5: //save as
            {
                LineSpacer();
                std::string temporaryFilePath="";
                std::cout<<"Enter file path:";
                std::getline(std::cin, temporaryFilePath);
                hotel.StatusRefresh();
                if(hotel.WriteToBin(temporaryFilePath)==true) std::cout<<"---  SAVED TO THE FILE SUCCESSFULLY  ---"<<std::endl;
                else std::cout<<"---  FAILED TO SAVE TO THE FILE  ---"<<std::endl;
                break;
            }

            //other commands:
            case 6: //checkin
            {
                hotel.StatusRefresh();
                LineSpacer();
                short rn=0, nog=0;
                std::string stringPlh="";
                Date datePlh;
                std::cout<<"Enter room number (enter [0] to abort):";
                std::cin>>rn;
                while(hotel.CheckIfRoomExists(rn)==false && rn!=0)
                {
                    std::cout<<"Room does NOT exist. Enter room number (enter [0] to abort):";
                    std::cin>>rn;
                }
                std::cin.ignore();
                if(rn!=0)
                {
                    if(hotel[hotel.FindRoom(rn)].getNumberOfGuests()>0 || hotel[hotel.FindRoom(rn)].getStatus()==false)
                        std::cout<<"--- ROOM IS IN USE OR OUT OF ORDER ---"<<std::endl; 
                    else
                    {
                        SmallLineSpacer();
                        std::cout<<"Enter checkin date (yyyy-mm-dd):";
                        std::cin>>stringPlh;
                        while(CheckDateValidity(stringPlh)==false)
                        {
                            std::cout<<"Invalid date. Enter new checkin date (yyyy-mm-dd):";
                            std::cin>>stringPlh;
                        }
                        std::cin.ignore();
                        datePlh.Set(stringPlh);
                        hotel[(hotel.FindRoom(rn))].setFrom(datePlh);

                        SmallLineSpacer();
                        std::cout<<"Enter checkout date (yyyy-mm-dd):";
                        std::cin>>stringPlh;
                        while(CheckDateValidity(stringPlh)==false)
                        {
                            std::cout<<"Invalid date. Enter new checkout date (yyyy-mm-dd)";
                            std::cin>>stringPlh;
                        }
                        std::cin.ignore();
                        datePlh.Set(stringPlh);
                        hotel[(hotel.FindRoom(rn))].setTo(datePlh);
                        
                        SmallLineSpacer();
                        std::cout<<"Enter number of guests (enter [0] for MAX):";
                        std::cin>>nog;
                        while(nog<0 || nog>hotel[(hotel.FindRoom(rn))].getNumberOfBeds())
                        {
                            std::cout<<"Invalid number of guests. Enter new number (MAX is:"<<hotel[(hotel.FindRoom(rn))].getNumberOfBeds()<<"):";
                            std::cin>>nog;
                        }
                        std::cin.ignore();
                        if(nog==0)nog=hotel[(hotel.FindRoom(rn))].getNumberOfBeds();
                        hotel[(hotel.FindRoom(rn))].setNumberOfGuests(nog);

                        SmallLineSpacer();
                        std::cout<<"Enter note:"<<std::endl;
                        std::getline(std::cin, stringPlh);
                        hotel[(hotel.FindRoom(rn))].setNote(stringPlh);

                        SmallLineSpacer();
                        std::cout<<"---  CHECKIN IS DONE ---"<<std::endl;
                    }
                }
                else std::cout<<"---  OPERATION ABORTED SUCCESSFULLY  ---"<<std::endl;
                break;
            }

            case 7: //availability
            {
                LineSpacer();
                std::string stringPlh="0";
                Date datePlh;
                std::cout<<"Enter date (enter [0] for today's date):";
                std::cin>>stringPlh;
                while(CheckDateValidity(stringPlh)==false && stringPlh!="0")
                {
                    std::cout<<"Invalid date. Enter new date (enter [0] for today's date):";
                    std::cin>>stringPlh;
                }
                std::cin.ignore();

                if(stringPlh=="0")datePlh=TodaY();
                else datePlh.Set(stringPlh);

                SmallLineSpacer();
                std::cout<<"The free rooms on "<<datePlh<<" are:"<<'\n'<<"| ";
                for(int i=0, j=1; i<=hotel.getSize()-1; i++)
                {
                    if(datePlh<hotel[i].GetFrom() || hotel[i].GetTo()<datePlh)
                    { 
                        std::cout<<hotel[i].getRoomNumber()<<" | ";
                        j++;
                        if(j>=10)
                        {
                            j=1;
                            std::cout<<'\n'<<"| ";
                        }
                    }
                }
                std::cout<<std::endl;
                break;
            }

            case 8: //checkout
            {
                hotel.StatusRefresh();
                LineSpacer();
                short rn=0;
                std::cout<<"Enter room number (enter [0] to abort):";
                std::cin>>rn;
                while(hotel.CheckIfRoomExists(rn)==false && rn!=0)
                {
                    std::cout<<"Room does NOT exist. Enter room number (enter [0] to abort):";
                    std::cin>>rn;
                }
                std::cin.ignore();
                if(rn!=0)
                {
                    if(hotel[hotel.FindRoom(rn)].getStatus()==false) std::cout<<"---  ROOM IS OUT OF ORDER  ---";
                    else
                    {
                        hotel[hotel.FindRoom(rn)].Vacate();
                        std::cout<<"---  CHECKOUT IS DONE  ---"<<std::endl;
                    }
                }
                else std::cout<<"---  OPERATION ABORTED SUCCESSFULLY  ---"<<std::endl;
                break;
            }

            case 9: //report
            {
                hotel.StatusRefresh();
                LineSpacer();
                std::string stringPlh="0";
                Date PeriodBegin, PeriodEnd, CalcBegin, CalcEnd;


                std::cout<<"Enter beginning date:";
                std::cin>>stringPlh;
                while(CheckDateValidity(stringPlh)==false)
                {
                    std::cout<<"Invalid date. Enter beginning new date:";
                    std::cin>>stringPlh;
                }
                std::cin.ignore();
                PeriodBegin.Set(stringPlh);

                SmallLineSpacer();
                std::cout<<"Enter end date:";
                std::cin>>stringPlh;
                while(CheckDateValidity(stringPlh)==false)
                {
                    std::cout<<"Invalid date. Enter new end date:";
                    std::cin>>stringPlh;
                }
                std::cin.ignore();
                PeriodEnd.Set(stringPlh);

                if(PeriodBegin>PeriodEnd)Swap(PeriodBegin, PeriodEnd);

                SmallLineSpacer();
                std::cout<<"Room usage from "<<PeriodBegin<<" to "<<PeriodEnd<<" is:"<<std::endl;
                for(int i=0; i<=hotel.getSize()-1; i++)
                {
                    if(hotel[i].GetTo()<PeriodBegin) std::cout<<"| "<<hotel[i].getRoomNumber()<<" | 0 - days used"<<std::endl;
                    else
                    {
                        if(hotel[i].GetFrom()>PeriodEnd) std::cout<<"| "<<hotel[i].getRoomNumber()<<" | 0 - days used"<<std::endl;
                        else 
                        {
                            if(PeriodBegin<hotel[i].GetTo() && PeriodBegin>hotel[i].GetFrom())
                                std::cout<<"| "<<hotel[i].getRoomNumber()<<" | "<<NumberOfDaysBetween(PeriodBegin, hotel[i].GetTo())<<" - days used"<<std::endl;
                            else std::cout<<"| "<<hotel[i].getRoomNumber()<<" | "<<NumberOfDaysBetween(PeriodEnd, hotel[i].GetFrom())<<" - days used"<<std::endl;
                        }
                    }
                }

                break;
            }

             case 10: //find
            {
                hotel.StatusRefresh();
                LineSpacer();
                int roomIndex=0;
                short neededBeds=0;
                std::string stringPlh="0";
                Date PeriodBegin, PeriodEnd;

                std::cout<<"Enter number of beds required:";
                std::cin>>neededBeds;
                while(neededBeds<0)
                {
                    std::cout<<"Invalid number of beds. Enter new number of beds required:";
                    std::cin>>neededBeds;
                }
                std::cin.ignore();

                SmallLineSpacer();
                std::cout<<"Enter beginning date:";
                std::cin>>stringPlh;
                while(CheckDateValidity(stringPlh)==false)
                {
                    std::cout<<"Invalid date. Enter beginning new date:";
                    std::cin>>stringPlh;
                }
                std::cin.ignore();
                PeriodBegin.Set(stringPlh);

                SmallLineSpacer();
                std::cout<<"Enter end date:";
                std::cin>>stringPlh;
                while(CheckDateValidity(stringPlh)==false)
                {
                    std::cout<<"Invalid date. Enter new end date:";
                    std::cin>>stringPlh;
                }
                std::cin.ignore();
                PeriodEnd.Set(stringPlh);

                if(PeriodBegin>PeriodEnd)Swap(PeriodBegin, PeriodEnd);
                
                for(int i=0; i<=hotel.getSize()-1; i++)
                {
                    if(hotel[i].getStatus()==true &&
                       hotel[i].getNumberOfGuests()==0 && 
                       hotel[i].getNumberOfBeds()>=neededBeds && 
                       hotel[i].getNumberOfBeds()<=hotel[roomIndex].getNumberOfBeds()) roomIndex=i;
                }

                SmallLineSpacer();
                if(hotel[roomIndex].getStatus()==true && 
                   hotel[roomIndex].getNumberOfGuests()==0 && 
                   hotel[roomIndex].getNumberOfBeds()>=neededBeds) std::cout<<"A suitable room is:"<<hotel[roomIndex].getRoomNumber()<<std::endl;
                else std::cout<<"---  NO SUITABLE ROOMS  ---"<<std::endl;
                
                break;
            }

            case 11: //find!
            {
                LineSpacer();
                std::cout<<"--- COMMAND IS TEMPORARILY DISABLED ---"<<std::endl;
                break;
            }

             case 12: //unavailable
            {
                hotel.StatusRefresh();
                LineSpacer();
                short rn=0;
                std::string stringPlh="";
                Date datePlh;
                std::cout<<"Enter room number (enter [0] to abort):";
                std::cin>>rn;
                while(hotel.CheckIfRoomExists(rn)==false && rn!=0)
                {
                    std::cout<<"Room does NOT exist. Enter room number (enter [0] to abort):";
                    std::cin>>rn;
                }
                std::cin.ignore();
                if(rn!=0)
                {
                    if(hotel[hotel.FindRoom(rn)].getNumberOfGuests()>0 || hotel[hotel.FindRoom(rn)].getStatus()==false)
                        std::cout<<"--- ROOM IS IN USE OR IS ALREADY OUT OF ORDER ---"<<std::endl; 
                    else
                    {
                        hotel[(hotel.FindRoom(rn))].setStatus(false);
                        hotel[(hotel.FindRoom(rn))].setNumberOfGuests(0);

                        SmallLineSpacer();
                        std::cout<<"Enter beginning date (yyyy-mm-dd):";
                        std::cin>>stringPlh;
                        while(CheckDateValidity(stringPlh)==false)
                        {
                            std::cout<<"Invalid date. Enter new beginning date (yyyy-mm-dd)";
                            std::cin>>stringPlh;
                        }
                        std::cin.ignore();
                        datePlh.Set(stringPlh);
                        hotel[(hotel.FindRoom(rn))].setFrom(datePlh);

                        SmallLineSpacer();
                        std::cout<<"Enter end date (yyyy-mm-dd):";
                        std::cin>>stringPlh;
                        while(CheckDateValidity(stringPlh)==false)
                        {
                            std::cout<<"Invalid date. Enter new end date (yyyy-mm-dd)";
                            std::cin>>stringPlh;
                        }
                        std::cin.ignore();
                        datePlh.Set(stringPlh);
                        hotel[(hotel.FindRoom(rn))].setTo(datePlh);

                        SmallLineSpacer();
                        std::cout<<"Enter note:"<<std::endl;
                        std::getline(std::cin, stringPlh);
                        hotel[(hotel.FindRoom(rn))].setNote(stringPlh);

                        SmallLineSpacer();
                        std::cout<<"---  ROOM MADE UNAVAILABLE  ---"<<std::endl;
                    }
                }
                else std::cout<<"---  OPERATION ABORTED SUCCESSFULLY  ---"<<std::endl;
                break;
            }

            case 13: //return to use
            {
                hotel.StatusRefresh();
                LineSpacer();
                short rn=0;
                std::cout<<"Enter room number (enter [0] to abort):";
                std::cin>>rn;
                while(hotel.CheckIfRoomExists(rn)==false && rn!=0)
                {
                    std::cout<<"Room does NOT exist. Enter room number (enter [0] to abort):";
                    std::cin>>rn;
                }
                std::cin.ignore();
                if(rn!=0)
                {
                    if(hotel[hotel.FindRoom(rn)].getStatus()==false)
                    {
                        hotel[hotel.FindRoom(rn)].Vacate();
                        std::cout<<"---  ROOM MADE OPERATIONAL AGAIN  ---"<<std::endl;
                    }
                    else std::cout<<"---  ROOM IS ALREADY OPERATIONAL  ---"<<std::endl;
                }
                else std::cout<<"---  OPERATION ABORTED SUCCESSFULLY  ---"<<std::endl;
                break;
            }

            //printing commands:
            case 14: //show all info
            {
                LineSpacer();
                hotel.StatusRefresh();
                hotel.Sort();
                hotel.ConsolePrintAll();
                break;
            }

            case 15: //print all info
            {
                LineSpacer();
                std::string temporaryFilePath="";
                std::cout<<"Enter file path:";
                std::getline(std::cin, temporaryFilePath);
                hotel.StatusRefresh();
                hotel.Sort();
                if(hotel.TxtPrintAll(temporaryFilePath)==true) std::cout<<"---  PRINTED SUCCESSFULLY  ---"<<std::endl;
                else std::cout<<"---  FAILED TO PRINT  ---"<<std::endl;
                break;
            }

            //administrator commands
            case 16: //add room
            {
                LineSpacer();
                std::string password="";
                std::cout<<"Enter admin password (enter [0] to exit):";
                std::getline(std::cin, password);
                while(password!=ADMIN_PASSWORD && password!="0")
                {
                    std::cout<<"Wrong password! Try again (enter [0] to exit):";
                    std::getline(std::cin, password);
                }
                if(password!="0")
                {
                    short shortPlh=0;
                    Room roomPlh;

                    std::cout<<"------------------------------------"<<std::endl;
                    std::cout<<"Enter new room number:";
                    std::cin>>shortPlh;
                    while(hotel.CheckIfRoomExists(shortPlh)==true || shortPlh<=0)
                    {
                        if(shortPlh<=0) std::cout<<"Invalid room number. Enter new room number:";
                        else std::cout<<"This room already exists. Enter new room number:";
                        std::cin>>shortPlh;
                    }
                    roomPlh.setRoomNumber(shortPlh);

                    std::cout<<"------------------------------------"<<std::endl;
                    std::cout<<"Enter number of beds:";
                    std::cin>>shortPlh;
                    while(shortPlh<=0)
                    {
                        std::cout<<"Invalid number of beds. Enter number of beds:";
                        std::cin>>shortPlh;
                    }
                    roomPlh.setNumberOfBeds(shortPlh);

                    std::cout<<"------------------------------------"<<std::endl;
                    if(hotel.AddRoom(roomPlh)==true)std::cout<<"---  ROOM ADDED SUCCESSFULLY  ---"<<std::endl;
                    else std::cout<<"---  NO ROOM WAS ADDED  ---"<<std::endl;
                    std::cin.ignore();
                }
                break;
            }
            case 17: //remove room
            {
                LineSpacer();
                std::string password="";
                std::cout<<"Enter admin password (enter [0] to exit):";
                std::getline(std::cin, password);
                while(password!=ADMIN_PASSWORD && password!="0")
                {
                    std::cout<<"Wrong password! Try again (enter [0] to exit):";
                    std::getline(std::cin, password);
                }
                if(password!="0")
                {
                    short shortPlh=0;

                    std::cout<<"------------------------------------"<<std::endl;
                    std::cout<<"Enter room number (enter [0] to abort):";
                    std::cin>>shortPlh;
                    while(shortPlh!=0 && hotel.CheckIfRoomExists(shortPlh)==false)
                    {
                        std::cout<<"Room does NOT exist. Enter room number (enter [0] to abort):";
                        std::cin>>shortPlh;
                    }

                    std::cout<<"------------------------------------"<<std::endl;
                    if(hotel.RemoveRoom(shortPlh)==true && shortPlh!=0) std::cout<<"---  ROOM REMOVED SUCCESSFULLY  ---"<<std::endl;
                    else std::cout<<"---  NO ROOM WAS REMOVED  ---"<<std::endl;
                    std::cin.ignore();
                }
                break;
            }

            //-----------------------------------
            case (-100): //invalid command
            {
                LineSpacer();
                std::cout<<"--- INVALID COMMAND ---"<<std::endl;
                std::cout<<"To see list of available commands type [help]."<<std::endl;
                break;
            }

            default:
            {
                break;
            }

        }
    }while(CommandToInt(command)!=0);

return 0;
}