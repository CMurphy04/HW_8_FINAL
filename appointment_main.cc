/**
 *   @file: appointment_main.cc
 * @author: Enter your name
 *   @date: Enter the date
 *  @brief: Add Description
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <string.h>
#include <vector>

#include "appointment.h"

using namespace std;

//main functions

//prints data from a vector of Appointment
void printData(vector <Appointment> a){

    cout << "|             Title              |    Date    |    Time    |  Duration  |" << endl;    
    cout << "|--------------------------------|------------|------------|------------|" << endl;

    for(int i = 0; i < a.size(); i++){
        cout << "| " << left << setw(31) << a.at(i).getTitle() << "| " << setw(11) << a.at(i).getDate() << "|  " << setw(10) << a.at(i).getStandardTime() << "|   " << setw(9) << a.at(i).getDuration() << "|" << endl;
    }

    cout << endl << endl;
}

//print data by order of time using selection sort
void printDataByStart(vector <Appointment> a){
    vector <Appointment> temp = a;

    for(int i = 0; i < temp.size()-1; i++){

        int minIndex = i;
        for(int j = i+1; j < temp.size(); j++){

            if(temp.at(j) < temp.at(minIndex)){
                minIndex = j;
            }
        }
        if(minIndex != i){
            temp.at(minIndex).swap(temp.at(i));
        }
    }

    printData(temp);
}

//print data by a specified time
void printDataByTime(vector <Appointment> a, int time){
    vector<Appointment> temp;

    for(int i = 0; i < a.size(); i++){
        if(a.at(i).getTime() == time){
            temp.push_back(a.at(i));
        }
    }

    printData(temp);
}

//deletes Appointment by a specific title
void deleteByTitle(vector <Appointment> a, string title){

    vector <int> temp;
    
    for(int i = 0; i < a.size(); i++){
        if(a.at(i).getTitle() == title){
            temp.push_back(i);
        }
    }

    for(int i = 0; i < temp.size(); i++){
        a.erase(a.begin()+i);
    }
}

//deletes Appointment by a specific time
void deleteByTime(vector <Appointment> a, int time){
    
    vector <int> temp;
    
    for(int i = 0; i < a.size(); i++){
        if(a.at(i).getTime() == time){
            temp.push_back(i);
        }
    }

    for(int i = 0; i < temp.size(); i++){
        a.erase(a.begin()+i);
    }
}

int main(int argc, char const *argv[]) {

    string command = argv[1];
    
    //check for invalid number of commands/invalid commands
    if(argc < 2 && (command != "-ps" || command != "-p" || command != "-a" || command != "-dt" || command != "-dm")){
        cout << "\nError. Please enter a valid command.\n" << endl;
        exit(0);
    }
    
    //load the data from the file
    ifstream is;
    is.open("agenda.txt");
    if (is.fail()){
        cout << "Error. Could not open data file" << endl;
        exit(0);
    }

    //load in the data into a vector of appointment objects
    vector <Appointment> aps;
    string data;
    while (!is.eof()){
        getline(is, data);
        if (data.length() >= 10){
            Appointment a(data);
            aps.push_back(a);
        }
    }

    is.close();

    //-ps argument, print by starting time
    if (argc == 2) // only true if print command is entered, also checks if its not
    {
        if (command == "-ps"){
            printDataByStart(aps);
        }
        else
        {
            cout << "Please enter a valid command." << endl;
        }
        
    }
    else if (argc == 3){
        string data = argv[2];
        if (command == "-p"){
            printDataByTime(aps, stoi(data));
        }
        else if (command == "-a"){
            Appointment temp(data);
            aps.push_back(temp);
        }
        else if (command == "-dt"){
            deleteByTitle(aps, data);
        }
        else if (command == "-dm"){
            deleteByTime(aps, stoi(data));
        }
    }
    else{
        cout << "Please enter a valid command." << endl;
    }
    

    //Write the list back onto the file
    if (command == "-a" || command == "-dt" || command == "-dm"){
        ofstream outs;
        outs.open("agenda.txt");
        if (outs.fail()){
            cout << "Error. Could not open output file." << endl;
            exit(0);
        }

        for (int i = 0; i < aps.size(); i++){
            outs << aps.at(i).getTitle() << "|";
            outs << aps.at(i).getYear() << "|";
            outs << aps.at(i).getMonth() << "|";
            outs << aps.at(i).getDay() << "|";
            outs << aps.at(i).getStandardTime() << "|";
            outs << aps.at(i).getDuration() << endl;
        }
        outs.close();
    }
    
    return 0;
}