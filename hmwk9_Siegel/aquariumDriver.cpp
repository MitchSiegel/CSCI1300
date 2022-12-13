// AquariumDriver.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 9 - Problem 2

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <assert.h>
#include "Aquarium.h"

using namespace std;

// This file contains the aquarium driver
// It tests the aquarium class

int main()
{
    //normal case
    Aquarium a("Mitch");
    assert(a.getAquaristName() == "Mitch");
    assert(a.getGallonsUsed() == 0);

    //normal case
    bool result = a.loadFish("fish.txt");
    assert(result == true);

    //test a file that does not exist
    result = a.loadFish("does not exist.txt");
    assert(result == false);

    //normal case - E is capitalized to make sure it is not case sensitive
    a.addFish("LyrEtail Guppy");
    assert(a.getGallonsUsed() == 1);
    
    //test a fish that is not in the file
    a.addFish("not in file");
    //make sure the gallons used did not change
    assert(a.getGallonsUsed() == 1);

    //normal case
    result = a.removeFish("LyrEtail Guppy");
    assert(result == true);
    assert(a.getGallonsUsed() == 0);

    //test a fish that is not in the file
    result = a.removeFish("not in file");
    assert(result == false);

    //normal case
    a.addFish("eLePhAnt EaR bEtTa");
    assert(a.getGallonsUsed() == 3);

    //normal case
    a.addFish("Red Oranda Goldfish");
    assert(a.getGallonsUsed() == 7);

    a.writeAquariumContents("output.txt");
    return 0;
}