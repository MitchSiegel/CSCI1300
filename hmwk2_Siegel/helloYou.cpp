// helloYou.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 2 - Problem # 2

#include <iostream>
using namespace std;

/*
    This program will ask the user for their name and then output a greeting to them.
*/

int main()
{
    // Declare variables
    string name;
    cout << "Please enter your name below:" << endl;
    // Get the user's name
    cin >> name;
    // Print the message
    cout << "Hello, " << name << "!" << endl;
    return 0;
}