//charCount.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 5 - Problem # ?

#include <iostream>
#include <cassert>
using namespace std;


/**
 * doublesEqual will test if two doubles are equal to each other within two decimal places.
 * This function was taken from the github on homework 5. It is used for comparing doubles in test cases.
 */
bool doublesEqual(double a, double b, const double epsilon = 1e-2)
{
    double c = a - b;
    return c < epsilon && -c < epsilon;
}

int main()
{
    /* paste here */
    return 0;
}