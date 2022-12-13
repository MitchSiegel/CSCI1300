//alphabeticalTriangle.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 4 - Problem # 5

#include <iostream>
using namespace std;

/*
    This program will print a triangle of letters, with the user inputting the number of rows.
    It will print out the letters in alphabetical order, starting with A, and resetting to A after Z.
    It will add 2 letters per row, and will print the number of rows the user inputs.
    It will also perform input validation, and will make sure the user inputs a positive number.
*/

int main(){
    //declare variables
    int number_height, current_position = 0;
    int triangle_length = 1;
    bool has_valid_input = false;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    //repeat until the user inputs a valid number of rows
    cout << "Enter the height:" << endl;
    cin >> number_height;
    //check and make sure the number is valid
    if(number_height >= 1)
    {
        has_valid_input = true;
    }
    else
    {
        cout << "Invalid input." << endl;
    }
    //print the triangle 
    //loop: for each row
    for(int i = 0; i < number_height; i++)
    {
        //loop: for each character in the row
        for(int j = 0; j < triangle_length; j++)
        {
            //print the character
            cout << alphabet[current_position];
            //increment the current letter - reset if at end of alphabet
            if(current_position < 25)
            {
                current_position++;
            }
            else
            {
                current_position = 0;
            }
        }
        //add 2 to the length of the next row
        triangle_length += 2;
        //print a new line
        cout << endl;
    }
    return 0;
}