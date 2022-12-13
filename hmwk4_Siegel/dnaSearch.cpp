//dnaSearch.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 4 - Problem # 4

#include <iostream>
using namespace std;

/* 
    This program will ask the user to input a DNA sequence, and then search for a specific DNA sequence within that sequence.
    It will output how many times the sequence appears in the DNA sequence.
    It will also validate the user's input to make sure it is a valid DNA sequence.
*/

int main(){
    //declare variables
    string dna_sequence, dna_fragment = "";
    int dna_fragment_times_found = 0;
    bool has_valid_input, has_searched = false;
    //repeat until the user inputs a valid dna sequence
    cout << "Enter the DNA Sequence:" << endl;
    cin >> dna_sequence;
    //make sure the dna sequence is valid (only contains A, T, C, and G)
    for(int i = 0; i < dna_sequence.length(); i++)
    {
        if(dna_sequence[i] != 'A' && dna_sequence[i] != 'T' && dna_sequence[i] != 'C' && dna_sequence[i] != 'G')
        {
            cout << "This is not a valid DNA sequence." << endl;
            return 0;
        }
        else
        {
                has_valid_input = true;
        }
    }
    //ask user for a dna fragment to search the sequence for
    cout << "Enter the DNA fragment to be searched:" << endl;
    cin >> dna_fragment;
    //make sure the dna fragment is valid (only contains A, T, C, and G)
    for(int i = 0; i < dna_fragment.length(); i++)
    {
        if(dna_fragment[i] != 'A' && dna_fragment[i] != 'T' && dna_fragment[i] != 'C' && dna_fragment[i] != 'G')
        {
            cout << "This is not a valid DNA sequence" << endl;
            return 0;
        }
    }   
    //search for the dna fragment in the dna sequence
    for(int i = 0; i < dna_sequence.length(); i++)
    {
        if(dna_sequence[i] == dna_fragment[0])
        {
            for(int j = 0; j < dna_fragment.length(); j++)
            {
                if(dna_sequence[i + j] == dna_fragment[j])
                {
                    has_searched = true;
                }
                else
                {
                    has_searched = false;
                    break;
                }
            }
            if(has_searched)
            {
                dna_fragment_times_found++;
            }
        }
    }
    cout << "Number of occurrences: " << dna_fragment_times_found << endl;
    return 0;
}