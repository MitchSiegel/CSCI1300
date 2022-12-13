//numValidNotes.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 1 - Problem 3


#include <iostream>
#include <cassert>
using namespace std;


/* 
* This function checks to see if a note is valid and in the SPN format.
* It takes in a string note and returns a boolean value.
* It will return true if the note is valid and false if it is not.
*/
bool isValidNote(string note)
{
    //Declare variables
    char note_letter = note[0];
    //'0' is used to force the char to be treated as an int
    int note_octave = note[1] - '0';
    bool valid_note = false;
    //This if statements checks to make sure the note is only 2 characters long
    if(note.length() == 2)
    {
        //This if statement checks to make sure the first character is between A and G
        if(note_letter == 'A' || note_letter == 'B' || note_letter == 'C' || note_letter == 'D' || note_letter == 'E' || note_letter == 'F' || note_letter == 'G')
        {
            //This if statement checks to make sure the octave is between 0 and 9
            if(note_octave >= 0 && note_octave <= 9)
            {
                //sets the return value to true because the note is valid
                valid_note = true;
            }
        }
    }
    //returns the result of the function, true or false.
    return valid_note;
}

int numValidNotes(string input)
{
    //declare variable
    int valid_tune_count = 0;
    //This if statement checks to make sure the input is not empty
    if(input.length() > 0)
    {
        //This for loop will iterate through the input string and check each character and its i+1 to see if it is a valid note.
        for(int i = 0; i < input.length(); i++)
        {
            //This if statement checks the substring of the currently selected character and its i+1 to see if it is a valid note.
            if(isValidNote(input.substr(i, 2)) == true)
            {
                //sets the return value to true because the tune is valid
                valid_tune_count++;
            }
        }
    }
    //returns the result of the function, true or false.
    return valid_tune_count;
}
int main() 
{
    assert(numValidNotes("I love comp sci!") == 0);
    assert(numValidNotes("F4E2B0") == 3);
    assert(numValidNotes("ADB3M7G4F") == 2);
    assert(numValidNotes("HC6MB1") == 2);

    return 0;
}