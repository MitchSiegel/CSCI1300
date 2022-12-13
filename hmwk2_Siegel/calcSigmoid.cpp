// calcSigmoid.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 2 - Problem # 6

#include <iostream>
// Include the math library for the exp function
#include <math.h>
using namespace std;
/*
    This program will calculate the sigmoid function of a number.
    The user will input a number, and the program will calculate the sigmoid function.
    It will also make sure the user inputs a valid number.
*/
int main()
{
    // declaring variables
    double x;
    cout << "Enter a value for x: " << endl;
    // Get the value of x from the user
    cin >> x;
    // Calculate the sigmoid function
    double sigmoid = 1/(1+exp(-x));
    // Print the results
    cout << "The sigmoid for x=" << x << " is " << sigmoid << endl;
    return 0;
}