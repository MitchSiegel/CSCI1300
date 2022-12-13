//isValidNote.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 1 - Problem 1


#include <iostream>
#include <cassert>
using namespace std;

/*
 * This program will check and make sure a note is valid and in the SPN (Scientific Pitch Notation) format.
 * It will also run test cases to make sure the function is working properly.
 * It will return true if the note is valid and false if it is not.
*/

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

int main() 
{
    //test 1 - valid note
    assert(isValidNote("A4") == true);
    //test 2 - valid note
    assert(isValidNote("B3") == true);
    //test 3 - invalid note
    assert(isValidNote("y") == false);
    //test 4 - invalid note
    assert(isValidNote("A1z") == false);

    return 0;
}