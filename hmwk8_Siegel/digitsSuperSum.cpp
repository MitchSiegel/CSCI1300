//digitsSuperSum.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 8 - Problem 1

#include <iostream>
#include <assert.h>
using namespace std;

// digitsSuperSum.cpp contains the function digitsSuperSum, and the main function to test it.
// it will run 6 test on the function to make sure the function works properly.
// This file will not output anything if the function works properly.

/*
 * the digitsSuperSumRecursive function will take the input of a number, and will add all of the digits together.
 * It uses recursion to do this.
 * It will return the sum of the digits.
*/
int digitsSuperSumRecursive(int N)
{
    //base case
    if(N < 10)
    {
        return N;
    }
    //recursive case
    else
    {
        //add the last digit to the sum of the rest of the digits
        int sum = N % 10;
        //remove the last digit
        int newNumber = N / 10;
        //add the sum of the rest of the digits to the sum
        return digitsSuperSumRecursive(sum + digitsSuperSumRecursive(newNumber));
    }
}

int main()
{
    assert(digitsSuperSumRecursive(123) == 6);

    assert(digitsSuperSumRecursive(4567) == 4);
    
    assert(digitsSuperSumRecursive(123456789) == 9);

    assert(digitsSuperSumRecursive(9) == 9);

    assert(digitsSuperSumRecursive(0) == 0);

    assert(digitsSuperSumRecursive(22) == 4);
}
