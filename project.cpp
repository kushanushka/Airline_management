#include<iostream>
#include<fstream>
#include<unistd.h> // For sleep()
#include<sstream>
using namespace std;

class Airline{
private:
    string Flight, Des, Dep;
    int Seats;

public:
    Airline(string flight, string des, string dep, int seats){
        Flight = flight;
        Des = des;
        Dep = dep;
        Seats = seats;    
    }

    string getFlight(){
        return Flight;
    }

    string getDes(){
        return Des;
    }

    string getDep(){
        return Dep;
    }

    int getSeat(){
        return Seats;
    }

    void update(string flight){
        ifstream in("./Flight.txt");  // Correct path for Mac
        ofstream out("./Flight_Temp.txt");  // Correct path for Mac

        string line;
        while(getline(in, line)){
            int pos = line.find(flight);
            if(pos != string::npos){

                int current = Seats - 1;
                Seats = current;
                stringstream ss;
                ss << current;
                string strCurrent = ss.str();

                int seatPos = line.find_last_of(':');
                line.replace(seatPos + 2, string::npos, strCurrent);
            }
            out << line << endl;
        }
        out.close();
        in.close();
        remove("./Flight.txt");  // Correct path for Mac
        rename("./Flight_Temp.txt", "./Flight.txt");  // Correct path for Mac
        cout << "Seat Reserved Successfully!" << endl;
    }
};

void display(){
    ifstream in("./Flight.txt");  // Correct path for Mac
    if(!in){
        cout << "Error: File Can't Open!" << endl;
    }
    else {
        string line;
        while(getline(in, line)){
            cout << line << endl;
        }
    }
}

int main(){
    Airline flight1("F101", "UAE", "England", 50);
    Airline flight2("F202", "UAE", "USA", 40);
    Airline flight3("F303", "UAE", "Canada", 2);

    ofstream out("./Flight.txt");  // Correct path for Mac
    if(!out){
        cout << "Error: File can't open!" << endl;
    }
    else{
        out << "\t " << flight1.getFlight() << " : " << flight1.getDes() << " : " << flight1.getDep() << " : " 
            << flight1.getSeat() << endl << endl;

        out << "\t " << flight2.getFlight() << " : " << flight2.getDes() << " : " << flight2.getDep() << " : " 
            << flight2.getSeat() << endl << endl;

        out << "\t " << flight3.getFlight() << " : " << flight3.getDes() << " : " << flight3.getDep() << " : " 
            << flight3.getSeat() << endl << endl;

        cout << "Data Saved Successfully!" << endl;
        out.close();
    }

    bool exit = false;
    while(!exit){
        system("clear");  // For MacOS
        cout << "\t Welcome To Airline Management System" << endl;
        cout << "\t ************************************" << endl;
        cout << "\t 1. Reserve A Seat." << endl;
        cout << "\t 2. Exit." << endl;
        cout << "\t Enter Your Choice: ";
        int val;
        cin >> val;

        if(val == 1){
            system("clear");
            display();
            string flight;
            cout << "Enter Flight No: ";
            cin >> flight;

            if(flight == flight1.getFlight() && flight1.getSeat() > 0){
                flight1.update(flight);    
            }
            else if(flight1.getSeat() <= 0){
                cout << "Sorry, Seats Not Available!" << endl;
            }

            if(flight == flight2.getFlight() && flight2.getSeat() > 0){
                flight2.update(flight);
            }
            else if(flight2.getSeat() <= 0){
                cout << "Sorry, Seat Not Available!" << endl;
            }

            if(flight == flight3.getFlight() && flight3.getSeat() > 0){
                flight3.update(flight);
            }
            else if(flight3.getSeat() <= 0){
                cout << "Sorry, Seat Not Available!" << endl;
            }
            sleep(5);  // For MacOS
        }
        else if(val == 2){
            system("clear");
            exit = true;
            cout << "Good Luck!" << endl;
            sleep(3);  // For MacOS
        }
    }
}
