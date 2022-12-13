//wifiSpeeds.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 3 - Problem # 4

#include <iostream>
using namespace std;

/*
    This program will ask the user for their internet speed test results.
    It will tell the user if their internet speed test is increasing, decreasing, or inconclusive.
    It will also validate the user's input.
*/

int main()
{
    // declare variables
    double speed_1, speed_2, speed_3;
    cout << "Enter wifi speeds over the last 3 classes: " << endl;
    cin >> speed_1;
    cin >> speed_2;
    cin >> speed_3;
    // check if the speeds are valid
    if(speed_1 < 0 || speed_2 < 0 || speed_3 < 0)
    {
        cout << "Please enter a valid input." << endl;
        return 0;
    }
    // check if the speeds are increasing
    if(speed_1 < speed_2 && speed_2 < speed_3)
    {
        cout << "The wifi is getting faster!" << endl;
    }
    // check if the speeds are decreasing
    else if(speed_1 > speed_2 && speed_2 > speed_3)
    {
        cout << "The wifi is getting slower!" << endl;
    }
    // other cases - inconclusive
    else
    {
        cout << "The wifi speed is changing unpredictably." << endl;
    }
    return 0;
}