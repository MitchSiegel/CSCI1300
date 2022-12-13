//secondPlace.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 5 - Problem # 3b

#include <iostream>
#include <cassert>
using namespace std;

/*
 * This program will update an array of pokemon names. 
 * It will add a new pokemon after a supplied pokemon.
 */

/*
 * insertAfter will insert a new item in the array after a certain index.
 * It will make sure the array has the space to do so.
 * It will return 1 if the item was inserted and 0 if it was not.
 */
bool insertAfter(string input_strings[], int num_elements, int arr_size, int index, string string_to_insert)
{
    if(num_elements == arr_size)
    {
        //array is full
        return false;
    }
    else if(index == arr_size || index - 1 == arr_size)
    {
        return false;
    }
    else
    {
        if(index + 1 == arr_size)
        {
            input_strings[index + 1] = string_to_insert;
        }
        else
        {
            //shift elements up before inserting the new string
            for(int i = num_elements; i > index; i--)
            {
                input_strings[i] = input_strings[i - 1];
                
            }
            input_strings[index + 1] = string_to_insert;
        }
        return true;
    }
}
/*
 * secondPlace will update an array of pokemon names.
 * It will add a new pokemon after a searching for a target pokemon provided.
 */ 
int secondPlace(string input_strings[], string string_to_insert, string string_to_find, int num_elements, int arr_size, int count)
{
    //check if the array is full
    if(num_elements == arr_size)
    {
        return num_elements;
    }
    else
    {
        //check if the number of strings added are going to be too large for the array
        if(num_elements + count > arr_size)
        {
            return num_elements;
        }
        else
        {
            //find the index of the string to find
            int index = 0;
            for(int i = 0; i < num_elements; i++)
            {
                if(input_strings[i] == string_to_find)
                {
                    index = i;
                    //insert the new string after the string to find
                    insertAfter(input_strings, num_elements, arr_size, index, string_to_insert);
                    num_elements++;
                }
            }
            return num_elements;
        }
    }
}

/*
 * doublesEqual will test if two doubles are equal to each other within two decimal places.
 * This function was taken from the github on homework 5. It is used for comparing doubles in test cases.
 */
bool doublesEqual(double a, double b, const double epsilon = 1e-2)
{
    double c = a - b;
    return c < epsilon && -c < epsilon;
}

int main()
{
    // test case 10
    int size = 12;
    string inputStrings[12] ={"charmeleon", "pichu", "pikachu","charmeleon", "charmeleon", "bulbasaur", "charmeleon"};
    int numElements = 7;
    string stringToInsert = "crobat";
    string stringToFind = "charmeleon";
    int count = 4;
    // updating numElements with the updated value returned by secondPlace
    numElements = secondPlace(inputStrings, stringToInsert, stringToFind, numElements, size, count);
    cout << "Function returned value: " << numElements << endl;
    // print array contents
    for(int i = 0; i < size; i++)
    {
        cout << inputStrings[i] << endl;
    }
    return 0;
}