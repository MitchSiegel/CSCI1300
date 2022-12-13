// almondMilk.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 2 - Problem # 3

#include <iostream>
// Include the iomanip library for the setprecision function
#include <iomanip> 
using namespace std;

/*
    This program will calculate the number of ounces in a certain milk container.
    The user will input the containers height and length. 
    The program will then calculate the number of ounces in the container.
*/

int main()
{
    //declare variables
    double carton_length, carton_height;
    cout << "What is the side length of the base of the carton in inches?" << endl;
    // Get the length of the carton from the user
    cin >> carton_length;
    cout << "What is the height of the carton in inches?" << endl;
    // Get the height of the carton from the user
    cin >> carton_height;
    //calculate the volume of the carton
    double carton_volume = carton_length * carton_length * carton_height;
    //calculate the number of ounces in the carton
    double carton_ounces = carton_volume * 0.55;
    //print results
    cout << "The carton has a volume of " << setprecision(1) << fixed << carton_ounces <<" ounces." << endl;
    return 0;
}