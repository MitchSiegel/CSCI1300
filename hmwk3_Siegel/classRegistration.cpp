//classRegistration.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 3 - Problem # 5

#include <iostream>
using namespace std;

/*
    This program provides basic information about classes in the math, science, or computer science department at a university.
    It will ask the student to enter the department, and then the class, and finally the section.
    It will "register" the student for the class.
    It will also validate the user's input.
*/

int main()
{
    //declare variables
    int department, class_number, section_number, section_full_number;
    string class_name;
    cout << "Select a department: (1)Computer Science (2)Math (3)Science" << endl;
    //get user input for department
    cin >> department;
    //check if the department is valid
    if(!(department == 1 || department == 2 || department == 3))
    {
        cout << "Please enter a valid input." << endl;
        return 0;
    }
    //check if the department is computer science
    if(department == 1)
    {
        cout << "Select a class: (1)Starting Computing (2)Data Structures (3)Algorithms" << endl;
        //get user input for class number
        cin >> class_number;
        //check if the class is valid
        if(!(class_number == 1 || class_number == 2 || class_number == 3))
        {
            cout << "Please enter a valid input." << endl;
            return 0;
        }
        //check what class is selected and set the class name, and ask user what section they want
        switch (class_number){
            case 1:
                class_name = "Starting Computing";
                cout << "Select a section: (1)Section 100 (2)Section 200" << endl;
                break;
            case 2:
                class_name = "Data Structures";
                cout << "Select a section: (1)Section 101 (2)Section 201" << endl;
                break;
            case 3:
                class_name = "Algorithms";
                cout << "Select a section: (1)Section 102 (2)Section 202" << endl;
                break;
        }
        //ask user for section number
        cin >> section_number;
        //check if the section is valid
        if(!(section_number == 1 || section_number == 2))
        {
            cout << "Please enter a valid input." << endl;
            return 0;
        }
        //check what section is selected and set the section full number
        if(class_name == "Starting Computing"){
            if(section_number == 1){
                section_full_number = 100;
            }
            else{
                section_full_number = 200;
            }
        }
        else if(class_name == "Data Structures"){
            if(section_number == 1){
                section_full_number = 101;
            }
            else{
                section_full_number = 201;
            }
        }
        else{
            if(section_number == 1){
                section_full_number = 102;
            }
            else{
                section_full_number = 202;
            }
        }
        //output the class name and section full number
        cout << "You've been enrolled in Section " << section_full_number << " of " << class_name << "!" << endl;
    }
    //check if the department is math
    if(department == 2)
    {
        cout << "Select a class: (1)Calculus 1 (2)Calculus 2 (3)Linear Algebra" << endl;
        //get user input for class number
        cin >> class_number;
        //check if the class is valid
        if(!(class_number == 1 || class_number == 2 || class_number == 3))
        {
            cout << "Please enter a valid input." << endl;
            return 0;
        }
        //check what class is selected and set the class name, and ask user what section they want
        switch (class_number){
            case 1:
                class_name = "Calculus 1";
                cout << "Select a section: (1)Section 400 (2)Section 500" << endl;
                break;
            case 2:
                class_name = "Calculus 2";
                cout << "Select a section: (1)Section 401 (2)Section 501" << endl;
                break;
            case 3:
                class_name = "Linear Algebra";
                cout << "Select a section: (1)Section 402 (2)Section 502" << endl;
                break;
        }
        //ask user for section number
        cin >> section_number;
        //check if the section is valid
        if(!(section_number == 1 || section_number == 2))
        {
            cout << "Please enter a valid input." << endl;
            return 0;
        }
        //check what section is selected and set the section full number
         if(class_name == "Calculus 1"){
            if(section_number == 1){
                section_full_number = 400;
            }
            else{
                section_full_number = 500;
            }
        }
        else if(class_name == "Calculus 2"){
            if(section_number == 1){
                section_full_number = 401;
            }
            else{
                section_full_number = 501;
            }
        }
        else{
            if(section_number == 1){
                section_full_number = 402;
            }
            else{
                section_full_number = 502;
            }
        }
        //output the class name and section full number
        cout << "You've been enrolled in Section " << section_full_number << " of " << class_name << "!" << endl;
    }
    //check if the department is science
    if(department == 3)
    {
        cout << "Select a class: (1)General Chemistry 1 (2)Physics 1" << endl;
        //get user input for class number
        cin >> class_number;
        //check if the class is valid
        if(!(class_number == 1 || class_number == 2))
        {
            cout << "Please enter a valid input." << endl;
            return 0;
        }
        //check what class is selected and set the class name, and ask user what section they want
        switch (class_number){
            case 1:
                class_name = "General Chemistry 1";
                cout << "Select a section: (1)Section 700 (2)Section 800" << endl;
                break;
            case 2:
                class_name = "Physics 1";
                cout << "Select a section: (1)Section 701 (2)Section 801" << endl;
                break;
        }
        //ask user for section number
        cin >> section_number;
        //check if the section is valid
        if(!(section_number == 1 || section_number == 2))
        {
            cout << "Please enter a valid input." << endl;
            return 0;
        }
        //check what section is selected and set the section full number
        if(class_name == "General Chemistry 1"){
            if(section_number == 1){
                section_full_number = 700;
            }
            else{
                section_full_number = 800;
            }
        }
        else{
            if(section_number == 1){
                section_full_number = 701;
            }
            else{
                section_full_number = 801;
            }
        }
        //output the class name and section full number
        cout << "You've been enrolled in Section " << section_full_number << " of " << class_name << "!" << endl;
    }
    return 0;
}