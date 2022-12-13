// tubing.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 3 - Problem # 1
//CREDIT: I used the template provided on the homework page


/* 
    This program will calculate if it safe to go tubing on the boulder creek.
    The user will input the flowrate of the creek.
    The program will then calculate if it is safe to go tubing.
*/

#include <iostream>
using namespace std;

int main() 
{
    // declare all the variables
    int flowrate;

    // prompt the user & get their input
    cout << "What is the flowrate of Boulder Creek?" << endl;
    cin >> flowrate;

    // input validation: flowrate must be positive
    if (flowrate <= 0) // EDIT THIS LINE
    {
        cout << "Please enter a valid input." << endl;
        return 0;
    }

    // decide if it's safe based on flowrate
    if (flowrate <= 250) // EDIT THIS LINE
    {
        cout << "It is safe to go tubing. Have fun!" << endl;
    }
    else
    {
        cout << "The river is flowing too fast to go tubing." << endl;
    }

    return 0;
}