// vacation.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 3 - Problem # 2

#include <iostream>
using namespace std;

/*
    This program will calculate the cost of transportation for a vacation.
    The user will input their budget and the their mode of transportation (bus, train, or plane).
    The program will make sure the budget is positive and the mode of transportation is valid.
    The program will then calculate if they can afford the transportation.
*/

int main()
{
    // declare all the variables
    double budget;
    char mode;
    // ask the user for their budget
    cout << "What is your budget?" << endl;
    cin >> budget;
    // make sure the budget is positive
    if(budget <= 0)
    {
        cout << "Please enter a valid input." << endl;
        return 0;
    }
    // ask the user for their mode of transportation
    cout << "What mode of transportation would you like to take (B, T, or A)?" << endl;
    cin >> mode;
    // make sure the mode of transportation is valid
    if(mode != 'B' && mode != 'T' && mode != 'A')
    {
        cout << "Please enter a valid input." << endl;
        return 0;
    }
    // calculate the cost of the transportation - bus
    if(mode == 'B' && budget >= 175.25)
    {
        cout << "Yes, this vacation is within your budget!" << endl;
    }
    else if(mode == 'B')
    {
        cout << "Sorry, this vacation is outside your budget." << endl;
    }
    // calculate the cost of the transportation - train
    if(mode == 'T' && budget >= 240.66)
    {
        cout << "Yes, this vacation is within your budget!" << endl;
    }
    else if(mode == 'T')
    {
        cout << "Sorry, this vacation is outside your budget." << endl;
    }
    // calculate the cost of the transportation - plane
    if(mode == 'A' && budget >= 350.93)
    {
        cout << "Yes, this vacation is within your budget!" << endl;
    }
    else if(mode == 'A')
    {
        cout << "Sorry, this vacation is outside your budget." << endl;
    }
    return 0;
}
