//arrayPilgrimage.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 5 - Problem # 1

#include <iostream>
#include <cassert>
using namespace std;

/* 
    This program will print the results of generated arrays.
    It takes no user input. It will also preform tests to make sure the program is working correctly.
*/


/*
 * generateDistance will generate an array with 10 ints, starting at 5.
 * It does not return anything because it modifies the array directly.
 */ 
void generateDistance(int X[])
{
    int number = 5;
    for(int i = 0; i < 10;i++)
    {
        X[i] = number++;
    }
}
/*
 * generateSequence will generate an array of the first 100 numbers divisible by 6.
 * It does not return anything because it modifies the array directly.
 */
void generateSequence(int X[])
{
    int array_size = 0;
    int i = 0;
    while(array_size <= 100)
    {
        i++;
        if(i % 6 == 0)
        {
            X[array_size] = i;
            array_size++;
        }
    }
}

/*
 * generateSequence will generate an array of the first 100 numbers divisible by 6.
 * It does not return anything because it modifies the array directly.
 */
void generateLetters(char X[])
{
    int upper_case_location = 65;
    int lower_case_location = 97;
    for(int i = 0; i < 52;i++)
    {
        if(i % 2 == 0)
        {
            X[i] = char(upper_case_location);
            upper_case_location++;
        }
        else
        {
            X[i] = char(lower_case_location);
            lower_case_location++;
        }
    }
}

int main()
{
    //declare initial arrays. distance, sequence and letters are to be populated later by functions.
    int distance[10] = {};
    string cities[] = {"Boulder", "NYC", "LA", "Chicago","Houston"};
    int sequence[100] = {};
    char letters[52] = {};
    //generate the distance array
    generateDistance(distance);
    generateSequence(sequence);
    generateLetters(letters);
    //perform tests on each array to make sure they are as expected.
    //tests to make sure distance array is correct
    assert(distance[6] == 11);
    //tests to make sure cities array is correct
    assert(cities[3] == "Chicago");
    //tests to make sure the lowercase operation is performing correctly
    assert(letters[25] == 'm');
    //tests to make sure the uppercase operation is performing correctly
    assert(letters[36] == 'S');
    //print the results of the distance array one item on each line
    for(int i = 0; i < 10;i++)
    {
        cout << distance[i] << endl;
    }
    //print the results of cities 
    for(int i = 0; i < 5;i++)
    {
        cout << cities[i] << endl;
    }
    //print the sequence results
    for(int i = 0; i < 100;i++)
    {
        cout << sequence[i] << endl;
    }
    //print the results of letters
    for(int i = 0; i < 52;i++)
    {
        cout << letters[i] << endl;
    }
    return 0;
}


