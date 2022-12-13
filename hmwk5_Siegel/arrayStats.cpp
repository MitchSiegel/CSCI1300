//arrayStats.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 5 - Problem # 2

#include <iostream>
#include <iomanip>
#include <cassert>
using namespace std;

/*
    This program will perform three operations on an array of doubles: min, sum, and average. 
    It will return the results and print them.
*/

/*
 * The min function takes in an array of doubles, and the array size.
 * It will return a double of the lowest value in the array.
 */ 
double min(double arr[],int arr_size)
{
    double lowest_number = arr[0];
    for(int i = 0; i < arr_size; i++)
    {
        if(arr[i] < lowest_number){
            lowest_number = arr[i];
        }
    }
    return lowest_number;
}

/*
 * The sum function takes in an array of doubles, and the array size.
 * It will return a double of the sum of the array values.
 */ 
double sum(double arr[],int arr_size)
{
    double sum = 0.0;
    for(int i = 0; i < arr_size; i++)
    {
        sum = sum + arr[i];
    }
    return sum;
}

/*
 * The average function takes in an array of doubles, and the array size.
 * It will return a double of the average of the array values.
 */ 
double average(double arr[],int arr_size)
{
    double array_sum = sum(arr, arr_size);
    double average = array_sum/arr_size;
    return average;
}
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
    //define values.
    double arr[] = {1.24, 5.68, 3.456};
    int arr_size = 3;
    //test to make sure the min function works
    assert(doublesEqual(min(arr, arr_size), 1.240));
    //test to make sure the sum function works
    assert(doublesEqual(sum(arr, arr_size), 10.376));
    //test to make sure the average function works
    assert(doublesEqual(average(arr, arr_size), 3.459));
    //print the results after passing test.
    cout << "Min: " << fixed << setprecision(3)<< min(arr, arr_size) << endl;
    cout << "Sum: " << fixed << setprecision(3) << sum(arr, arr_size) << endl;
    cout << "Avg: " << fixed << setprecision(3) << average(arr, arr_size) << endl;
    return 0;
}