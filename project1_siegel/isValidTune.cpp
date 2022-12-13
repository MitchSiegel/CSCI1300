//isValidTune.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 1 - Problem 2


#include <iostream>
#include <cassert>
using namespace std;
/* 
 * This program will make sure all the notes in a tune are valid (SPN format).
 * It will also run test cases to make sure the function is working properly.
 * It will return true if the tune is valid and false if it is not.
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

/*
 * This function checks to see if a tune is valid and in the SPN format.
 * It takes in a string tune and returns a boolean value.
 * It will return true if the tune is valid and false if it is not.
*/
bool isValidTune(string input)
{
    //declare variable
    bool valid_tune = false;
    //This if statement checks to make sure the input is not empty
    if(input.length() > 0)
    {
        //This for loop will check each two character string in the input to see if it is a valid note.
        for(int i = 0; i < input.length(); i = i + 2)
        {
            //This if statement checks the substring of the currently selected two characters to see if it is a valid note.
            if(isValidNote(input.substr(i, 2)) == true)
            {
                //sets the return value to true because the tune is valid
                valid_tune = true;
            }
            //This else statement will set the return value to false and break the loop if the character is not a valid note
            else
            {
                valid_tune = false;
                break;
            }
        }
    }
    //returns the result of the function, true or false.
    return valid_tune;
}
int main() 
{    
    assert(isValidTune("A2B4C7") == true);
    assert(isValidTune("M5D2E1") == false);
    assert(isValidTune("A5D2E11") == false);

    return 0;
}