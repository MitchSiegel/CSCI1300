// convertCurrency.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 2 - Problem # 5

#include <iostream>
#include <math.h>
using namespace std;
/*
    This program will convert bolts to gold coins, and gold coins to bolts.
    The user will input the amount of bolts they have, and the program will convert it.
    It will also make sure the user inputs a valid number.
*/

int main()
{
    // declaring variables
    int gold_coins, gems, bolts;
    cout << "Enter the number of Bolts:" << endl;
    cin >> bolts;
    // Check if bolts is a valid int and is greater than zero - if not, terminate the program
    if(!cin || bolts < 0){
        cout << "Bolts must be a number and greater than 0. Please try again!" << endl;
        return 0;
    }
    // Convert bolts to gold coins
    gold_coins = bolts / 23;
    // Set the remainder left over from the division to bolts
    bolts = bolts % 23;    
    // Convert gold coins to gems
    gems = gold_coins / 13;
    // Set the remainder left over from the division to gold coins
    gold_coins = gold_coins % 13;
    // Print the results
    cout << gems << " Gem(s) " << gold_coins << " GoldCoin(s) " << bolts << " Bolt(s)" << endl;
    return 0;
}