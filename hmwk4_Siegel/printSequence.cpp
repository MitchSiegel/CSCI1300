//printSequence.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 4 - Problem # 2

#include <iostream>
#include <math.h>

using namespace std;

/*
    This program uses the Collatz Sequence to print a sequence of numbers   
    It takes in a number between 1 and 1000 (excluding 1 and 1000) and prints the sequence
    If the user inputs a negative number, 1, or 1000, it will print "Invalid Input" and ask them to input a new number
*/

int main(){
    //declare variables
    int number;
    bool has_valid_input = false;
    //repeat until user inputs a valid number
    while(!has_valid_input)
    {
        //ask user for input
        cout << "Enter  a value between 1 and 1000:" << endl;
        cin >> number;
        //check if input is valid, output error message if not
        if(number > 1 && number < 1000)
        {
            has_valid_input = true;
        }
        else
        {
            cout << "Invalid input." << endl;
        }
    }
    //print the sequence, loops until the number is 1, which is the end of the sequence
    while(number != 1)
    {
        //prints the number in the sequence
        cout << number << endl;
        //checks if the number is even or odd
        if(number % 2 == 0)
        {
            //if even, divide by 2
            number = floor(number / 2);
        }
        else
        {
            //if odd, multiply by 3 and add 1
            number = (number * 3) + 1;
        }
    }
    //finally, print the result (1)
    cout << number << endl;
    return 0;
}