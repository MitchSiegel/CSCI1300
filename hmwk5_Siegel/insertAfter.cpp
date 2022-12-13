//insertAfter.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 5 - Problem # 3a

#include <iostream>
#include <cassert>
using namespace std;

/*
    This program will see if you can insert another item in the array after a certain index.
    It will check and make sure the array has the space to do so.
    It will also check to make sure the index is valid.
    It will shift the items in the array to make room for the new item.
    It will return 1 if the item was inserted and 0 if it was not.
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

int main()
{
	//declare variables
    int size = 10;
    string inputStrings[10] = {"pikachu", "meowth", "snorlax", "caterpie", "pichu", "eevee"};
    int numElements = 6;
    int index = 1;
    string stringToInsert = "clefairy";
    // result contains the value returned by insertAfter
    bool result = insertAfter(inputStrings, numElements, size, index, stringToInsert);
    // print result
    cout << "Function returned value: "<< result << endl;
    // print the array
    for (int i = 0; i < numElements + 1; i++)
    {
        cout << inputStrings[i] << endl;
    }
    return 0;
}