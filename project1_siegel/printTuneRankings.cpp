//printTuneRankings.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 1 - Problem 6
#include <iostream>
#include <cassert>
using namespace std;

//This program will take in a string of notes and output them based on how similar they are to the target tune.

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

/*
 * bestSimilarity will find the best similarity score possible between an input tune and a target tune.
 * It takes in two strings, input_tune and target_tune, and returns a double value.
 * It will make sure the input_tune is large enough to be compared to the target_tune.
 * It will then calculate the similarity score between the input_tune and the target_tune, and then it will shift the input_tune by one note and calculate the similarity score again.
 * It will keep the highest similarity score and return it.
*/
double bestSimilarity(string input_tune, string target_tune)
{
    //declare variables
    double best_similarity = -10;
    double similarity = 0.0;
    if(input_tune.length() < target_tune.length())
    {
        return 0.0;
    }
    //loop through the input tune, starting at the beginning and ending at the end of the target tune
    for(int i = 0; i < input_tune.length() - target_tune.length() + 1; i++)
    {
        //calculate the similarity score for each subsequence of the input tune
        similarity = tuneSimilarity(input_tune.substr(i,target_tune.length()),target_tune);
        //if the similarity score is greater than the best similarity score, set the best similarity score to the similarity score
        if(similarity > best_similarity)
        {
            best_similarity = similarity;
        }
    }
    //return the best similarity score
    return best_similarity;
}

/*
 * This function will print the rankings of the tunes against the target tune.
 * It takes in three string tunes, and a target tune. It will return nothing.
 * It will first calculate the best similarity score between the target tune and each of the three tunes.
 * It will then print the rankings of the tunes based on their similarity scores.
*/
void printTuneRankings(string tune1, string tune2, string tune3, string target_tune)
{
    //declare variables
    double similarity1 = 0.0;
    double similarity2 = 0.0;
    double similarity3 = 0.0;
    //calculate the similarity score for each tune
    similarity1 = bestSimilarity(tune1,target_tune);
    similarity2 = bestSimilarity(tune2,target_tune);
    similarity3 = bestSimilarity(tune3,target_tune);
    // if all of the similarity scores are equal, print them in order of tune number.
    if(doublesEqual(similarity1,similarity2) && doublesEqual(similarity2,similarity3))
    {
        cout << "1) Tune 1, 2) Tune 2, 3) Tune 3" << endl;
    }
    // if the first two similarity scores are equal, print them in order of tune number.
    else if(doublesEqual(similarity1,similarity2))
    {
        //if the first similarity score is greater than the third similarity score, print them in order of tune number.
        if(similarity1 > similarity3)
        {
            cout << "1) Tune 1, 2) Tune 2, 3) Tune 3" << endl;
        }
        //if the third similarity score is greater than the first similarity score, print them in order of tune number.
        else if(similarity3 > similarity1)
        {
            cout << "1) Tune 3, 2) Tune 2, 3) Tune 1" << endl;
        }
        //if the first and third similarity scores are equal, print them in order of tune number.
        else if(doublesEqual(similarity1,similarity3))
        {
            cout << "1) Tune 1, 2) Tune 2, 3) Tune 3" << endl;
        }
    }
    //if the second and third similarity scores are equal, print them in order of tune number.
    else if(doublesEqual(similarity2,similarity3))
    {
        //if the second similarity score is greater than the first similarity score, print them in order of tune number.
        if(similarity2 > similarity1)
        {
            cout << "1) Tune 2, 2) Tune 3, 3) Tune 1" << endl;
        }
        //if the first similarity score is greater than the second similarity score, print them in order of tune number.
        else if(similarity1 > similarity2)
        {
            cout << "1) Tune 1, 2) Tune 2, 3) Tune 3" << endl;
        }
        //if the first and second similarity scores are equal, print them in order of tune number.
        else if(doublesEqual(similarity1,similarity2))
        {
            cout << "1) Tune 1, 2) Tune 2, 3) Tune 3" << endl;
        }
    }
    //if the first and third are tied
    else if(doublesEqual(similarity1,similarity3))
    {
        //if the first similarity score is greater than the second similarity score, print them in order of tune number.
        if(similarity1 > similarity2)
        {
            cout << "1) Tune 1, 2) Tune 3, 3) Tune 2" << endl;
        }
        //if the second similarity score is greater than the first similarity score, print them in order of tune number.
        else if(similarity2 > similarity1)
        {
            cout << "1) Tune 2, 2) Tune 1, 3) Tune 3" << endl;
        }
        //if the first and second similarity scores are equal, print them in order of tune number.
        else if(doublesEqual(similarity1,similarity2))
        {
            cout << "1) Tune 1, 2) Tune 2, 3) Tune 3" << endl;
        }
    }
    //if the second and third are tied
    else if(doublesEqual(similarity2,similarity3))
    {
        //if the second similarity score is greater than the first similarity score, print them in order of tune number.
        if(similarity2 > similarity1)
        {
            cout << "1) Tune 2, 2) Tune 3, 3) Tune 1" << endl;
        }
        //if the first similarity score is greater than the second similarity score, print them in order of tune number.
        else if(similarity1 > similarity2)
        {
            cout << "1) Tune 1, 2) Tune 2, 3) Tune 3" << endl;
        }
        //if the first and second similarity scores are equal, print them in order of tune number.
        else if(doublesEqual(similarity1,similarity2))
        {
            cout << "1) Tune 1, 2) Tune 2, 3) Tune 3" << endl;
        }
    }
    //if the first is bigger than the others
    else if(similarity1 > similarity2 && similarity1 > similarity3)
    {
        //if the second is bigger than the third
        if(similarity2 > similarity3)
        {
            cout << "1) Tune 1, 2) Tune 2, 3) Tune 3" << endl;
        }
        //if the third is bigger than the second
        else if(similarity3 > similarity2)
        {
            cout << "1) Tune 1, 2) Tune 3, 3) Tune 2" << endl;
        }
        //if the second and third are equal
        else if(doublesEqual(similarity2,similarity3))
        {
            cout << "1) Tune 1, 2) Tune 2, 3) Tune 3" << endl;
        }
    }
    //if the second is bigger than the others
    else if(similarity2 > similarity1 && similarity2 > similarity3)
    {
        //if the first is bigger than the third
        if(similarity1 > similarity3)
        {
            cout << "1) Tune 2, 2) Tune 1, 3) Tune 3" << endl;
        }
        //if the third is bigger than the first
        else if(similarity3 > similarity1)
        {
            cout << "1) Tune 2, 2) Tune 3, 3) Tune 1" << endl;
        }
        //if the first and third are equal
        else if(doublesEqual(similarity1,similarity3))
        {
            cout << "1) Tune 1, 2) Tune 2, 3) Tune 3" << endl;
        }
    }
    //if the third is bigger than the others
    else if(similarity3 > similarity1 && similarity3 > similarity2)
    {
        //if the first is bigger than the second
        if(similarity1 > similarity2)
        {
            cout << "1) Tune 3, 2) Tune 1, 3) Tune 2" << endl;
        }
        //if the second is bigger than the first
        else if(similarity2 > similarity1)
        {
            cout << "1) Tune 3, 2) Tune 2, 3) Tune 1" << endl;
        }
        //if the first and second are equal
        else if(doublesEqual(similarity1,similarity2))
        {
            cout << "1) Tune 1, 2) Tune 2, 3) Tune 3" << endl;
        }
    }
}
int main() 
{
    printTuneRankings("E0C1B6D2", "A0C1B5F2", "F1G4E8C3", "F9G4");
    return 0;
}