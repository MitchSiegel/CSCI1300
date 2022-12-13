//tuneSimilarity.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 1 - Problem 4


#include <iostream>
#include <cassert>
using namespace std;

/*
 * This program will calculate the similarity between two tunes.
 * It takes in two strings, tune1 and tune2, and returns a double value.
 * It will make sure the two strings are greater than zero, and equal in length.
 * It will output a similarity score using the formulas provided in the project description.
*/

/*
 * doubles_equal will test if two doubles are equal to each other within two decimal places.
 * Credit: taken from the github project 1 page.
 */
bool doublesEqual(double a, double b, const double epsilon = 1e-2)
{
    double c = a - b;
    return c < epsilon && -c < epsilon;
}

/*
* tuneSimilarity will calculate the similarity between two tunes.
* It takes in two strings, tune1 and tune2, and returns a double value.
* It will make sure the two strings are greater than zero, and equal in length.
* It will output a similarity score using the formulas provided in the project description.
*/
double tuneSimilarity(string tune1,string tune2)
{
    //declare variables
    double matching_notes = 0.0;
    double different_notes = 0.0;
    double matching_perfectly = 0.0;
    double total_notes = 0;
    double similarity = 0.0;
    
    //handle case if the tunes are empty or if they are not the same length
    if((tune1.length() != tune2.length()) || (tune1.length() == 0 || tune2.length() == 0))
    {
        return similarity;
    }
    //loop through the strings by 2, since each note is 2 characters long, and compare them.
    for(int i = 0; i < tune1.length(); i = i + 2)
    {
        //If the notes are a perfect match (both letter and pitch), add 1 to matching_perfectly
        if(tune1.substr(i,2) == tune2.substr(i,2))
        {
            matching_perfectly++;
        }
        //If the notes are a match (just the letter), add 1 to matching_notes
        if(tune1.substr(i,1) == tune2.substr(i,1))
        {
            matching_notes++;
        }
        //If the notes are not a match, add 1 to different_notes (unless they match in pitch but not letter, in which case they are not counted as different notes)
        else if(tune1.substr(i+1,1) != tune2.substr(i+1,1))
        {
            different_notes++;
        }
    }
    //calculate the total number of notes (divide by 2 since each note is 2 characters long)
    total_notes = tune1.length() / 2;
    //calculate the similarity score (using the formulas provided in the project description)
    similarity = (matching_notes / total_notes);
    similarity = similarity + matching_perfectly;
    similarity = similarity - different_notes;
    //return the similarity score (0 if the strings are not the same length or if they are empty and the similarity score otherwise)
    return similarity;
}
int main() 
{
    //test 1
    assert(doublesEqual(tuneSimilarity("G4E5D4", "G4F4D5"), 0.666667));
    //test 2
    assert(doublesEqual(tuneSimilarity("A0B0C0D0", "D1C1B1A1"), -4));
    //test 3
    assert(doublesEqual(tuneSimilarity("E5E5G5A6G5D5", "E5G5A6G5D5D5"), 0.333333));
    //test 4
    assert(doublesEqual(tuneSimilarity("D5G2", "F7D1E4G4"), 0));
    return 0;
}
