//instrument.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 3 - Problem # 6

#include <iostream>
using namespace std;

/* 
    This program will calculate the price of an instrument based on input from the user.
    The program will ask what category the instrument is in.
    The program will then ask what instrument the user wants.
    Finally, the program will output the price of the instrument.
    This program uses only switch statements instead of if statements.
*/

int main()
{
    // declare all the variables
    int category, instrument;
    cout << "Select a category: (1)Brass (2)Woodwind (3)Percussion" << endl;
    // ask the user what category of instrument they want.
    cin >> category;
    // input validation: category must be 1, 2, or 3
    switch(category)
    {
        case 1:

            cout << "Select an instrument: (1)Trumpet (2)Trombone" << endl;
            // ask the user what instrument they want.
            cin >> instrument;
            // input validation + displaying the price of the instrument
            switch(instrument)
            {
                case 1:
                    cout << "Your instrument will be $350." << endl;
                    break;
                case 2:
                    cout << "Your instrument will be $400." << endl;
                    break;
                default:
                    cout << "Please enter a valid input." << endl;
                    break;
            }
            break;
        case 2:
            cout << "Select an instrument: (1)Flute (2)Saxophone" << endl;
            // ask the user what instrument they want.
            cin >> instrument;
            // input validation + displaying the price of the instrument
            switch(instrument)
            {
                case 1:
                    cout << "Your instrument will be $325." << endl;
                    break;
                case 2:
                    cout << "Your instrument will be $425." << endl;
                    break;
                default:
                    cout << "Please enter a valid input." << endl;
                    break;
            }
            break;
        case 3:
            cout << "Select an instrument: (1)Snare Drum (2)Cymbals" << endl;
            // ask the user what instrument they want.
            cin >> instrument;
            // input validation + displaying the price of the instrument
            switch(instrument)
            {
                case 1:
                    cout << "Your instrument will be $275." << endl;
                    break;
                case 2:
                    cout << "Your instrument will be $200." << endl;
                    break;
                default:
                    cout << "Please enter a valid input." << endl;
                    break;
            }
            break;
        default:
            cout << "Please enter a valid input." << endl;
            break;
    }
    return 0;
}