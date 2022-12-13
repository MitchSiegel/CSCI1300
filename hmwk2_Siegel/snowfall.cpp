// snowfall.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 2 - Problem # 4

#include <iostream>
using namespace std;

/*
    This program will ask the user for the amount of days it would like to calculate the snowfall for and then outputs the amount of snowfall.
    It uses data given to us in the problem.
    It also performs error checking to make sure the user inputs a valid number.
*/

int main()
{
    //declare variables
    int breckenridge_snowfall, vail_snowfall, copper_snowfall, days;
    cout << "How many days in the future would you like a prediction for?" << endl;
    // Get the number of days from the user
    cin >> days;
    // Check if days is a valid int and is greater than zero - if not, terminate the program
    if(!cin || days < 0){
        cout << "Days must be a number and greater than 0. Please try again!" << endl;
        return 0;
    }
    //perform snowfall calculations
    breckenridge_snowfall = 25 + (days * 5);
    vail_snowfall = 28 + (days * 12);
    copper_snowfall = 40 + (days * 2);
    //Display output to user
    cout << "Breckenridge will have " << breckenridge_snowfall << " inches, Vail will have " << vail_snowfall << " inches, and Copper Mountain will have " << copper_snowfall << " inches. ";
    return 0;
}