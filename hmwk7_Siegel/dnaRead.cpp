//dnaRead.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 7 - Problem 2

#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

/*
 * dnaRead.cpp contains the function dnaRead, which takes in a vector of strings. 
 * The function will return a string of the dna sequence provided in the vector.
*/

/*
* dnaRead function takes in a vector of DNA codons.
* It will make sure the DNA codon is valid, and if it isn't, it will return "invalid sequence".
* It will return the sequence of DNA between the start codon (ATG) and the stop codons (TAA, TAG, or TGA).
* If there is no start codon, it will return an empty string.
* If there is no stop codon, it will return the sequence of DNA between the start codon and the end of the vector.
*/
string dnaRead(vector<string> dna)
{
    string dnaSequence = "";
    int numberOfLoops = 0;
    int startCodon = -1;
    int stopCodon = -1;
    int numberOfStartCodons = 0;
    int numberOfStopCodons = 0;
    //check the number of start codons and stop codons
    for(int i = 0; i < dna.size(); i++)
    {
        if(dna[i] == "ATG")
        {
            numberOfStartCodons++;
        }
        if(dna[i] == "TAA" || dna[i] == "TAG" || dna[i] == "TGA")
        {
            numberOfStopCodons++;
        }
    }
    //count the number of pairs of start and stop codons
    if(numberOfStartCodons == numberOfStopCodons)
    {
        //if there is an equal number of start and stop codons, then the number of loops will be the number of start codons
        numberOfLoops = numberOfStartCodons;
    }else{
        //default to just one loop
        numberOfLoops = 1;
    }
    for(int j = 0; j < numberOfLoops; j++)
    {
        for (int i = 0; i < dna.size(); i++)
        {
            //if its not 3, its not a valid codon
            if (dna[i].length() != 3)
            {
                return "Invalid sequence.";
            }
            //if there is a start codon, set startCodon to i
            else if (dna[i] == "ATG")
            {
                startCodon = i;
            }
            //stop codon checking
            else if (dna[i] == "TAA" || dna[i] == "TAG" || dna[i] == "TGA")
            {
                stopCodon = i;
            }
        }
        //if there is no start codon
        if (startCodon == -1)
        {
            return "";
        }
        //if there is no stop codon
        else if (stopCodon == -1)
        {
            //because there is no stop codon, we return the dna sequence from the start codon to the end of the vector
            for (int i = startCodon + 1; i < dna.size(); i++)
            {
                dnaSequence += dna[i];
            }
            return dnaSequence;
        }
        //there is both a start and stop codon
        else
        {
            //create the dna sequence from the start codon to the stop codon and return it
            for (int i = startCodon + 1; i < stopCodon; i++)
            {
                dnaSequence += dna[i];
            }
        }
    }
    return dnaSequence;
}
int main()
{
    //test 1 - normal case
    vector<string> dna{"ATG", "TCA", "TAA"};
    assert(dnaRead(dna) == "TCA");

    //test 2 - no start codon
    vector<string> dna2{"TCA","TCA","TAA"};
    assert(dnaRead(dna2) == "");

    //test 3 - no stop codon
    vector<string> dna3{"ATG","TCA","TCA"};
    assert(dnaRead(dna3) == "TCATCA");

    //test 4 - invalid sequence
    vector<string> dna4{"AT","TCA","TAA","TCA"};
    assert(dnaRead(dna4) == "Invalid sequence.");

    //test 5 - multiple sequences
    vector<string> dna5{"ATG","TCA","TAA","ATG","TCA","TAA"};
    assert(dnaRead(dna5) == "TCATCA");

    //test 6 - start codon in position 1
    vector<string> dna6{"TCA","ATG","TCA","TAA"};
    assert(dnaRead(dna6) == "TCA");


    return 0;
}