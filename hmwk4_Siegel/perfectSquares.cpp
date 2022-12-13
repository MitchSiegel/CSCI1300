//perfectSquare.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 4 - Problem # 1

//Credit: Used the example code from the homework page
#include <iostream>
#include <cmath>

using namespace std;

/*
    This program will calculate the sum of the perfect squares between 0 and the inputted number.
    It will make sure the inputted number is a positive integer.
    It will then calculate the sum of the perfect squares between 0 and the inputted number.
    Finally, it will print the results.
*/

int main()
{
    // declare all variables
    int number;
    int sum = 0;
    int max_val;
    
    // prompt the user and get their input
    cout << "Enter a non-negative integer:" << endl;
    cin >> number;
    
    // input validation
    if (number < 0) //EDIT THIS LINE
    { 
        cout << "Invalid input." << endl;
    }
    else
    {
        // compute square root
        max_val = sqrt(number);
        
        // loop to compute sum of perfect squares
        for (int i = 0; i <= max_val; i++)
        {
            sum = sum + (i * i);
        }
            cout << "Sum: " << sum << endl;
    }
    return 0;
}