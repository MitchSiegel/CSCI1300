//pizza.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 3 - Problem # 3

#include <iostream>
using namespace std;

/*
    This program will calculate the cost of a pizza.
    The user will input the size of the pizza and the number of toppings.
    The program will make sure the size is valid and the number of toppings is positive.
    The program will then calculate the cost of the pizza and toppings, and output it.
*/

int main()
{
    // declare variables
    char pizza_size;
    int toppings;
    double total_cost;
    // ask the user for the size of the pizza
    cout << "What size pizza would you like to order?" << endl;
    cin >> pizza_size;
    // make sure the size is valid
    if(pizza_size != 'S' && pizza_size != 'M' && pizza_size != 'L')
    {
        cout << "Please enter a valid input." << endl;
        return 0;
    }
    // ask the user for the number of toppings
    cout << "How many toppings do you want?" << endl;
    cin >> toppings;
    // make sure the number of toppings is positive
    if(toppings < 0)
    {
        cout << "Please enter a valid input." << endl;
        return 0;
    }
    // calculate the cost of the pizza - small
    if(pizza_size == 'S')
    {
        total_cost = 4.99 + (toppings * .75);
    }
    // calculate the cost of the pizza - medium
    else if(pizza_size == 'M')
    {
        total_cost = 5.99 + (toppings * 1.50);
    }
    // calculate the cost of the pizza - large
    else if(pizza_size == 'L')
    {
        total_cost = 6.99 + (toppings * 2.25);
    }
    // output the total cost
    cout << "Your total is $" << total_cost << endl;
    return 0;
}