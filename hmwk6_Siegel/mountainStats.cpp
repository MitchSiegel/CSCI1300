//mountainStats.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 6 - Problem # 2

#include <iostream>
#include <string>
#include <fstream>
#include <cassert>

using namespace std;

/*
 * This file will take an input of a file, and prints the number of lines read
 * It will also print out the tallest mountain in the file, and its name.
 * And finally, it will print out the smallest mountain.
*/

/*
 * the split function takes in a string, the seperator, and then the arr, and the arr_size.
 * It will split the function into an array, splitting it by the seperator.
 * If there are more splits than the array size, it will fill it with as many as possible.
*/
int split(string input_string,char seperator, string arr[],int arr_size)
{
    int last_split = 0;
    int array_split = 0;
    int seperator_count = 0;
    int current_part_length = 0;
    //make sure the string is not zero.
    if(input_string.length() == 0)
    {
        return 0;
    }
    //count how many splits we should expect
    for(int i = 0; i < input_string.length(); i++)
    {
        if(input_string[i] == seperator)
        {
            seperator_count++;
        }
    }
    if(seperator_count == 0)
    {
        arr[0] = input_string;
        return 1;
    }
    for(int i = 0;i < input_string.length(); i++)
    {
        if(input_string[i] == seperator)
        {
            arr[array_split] = input_string.substr(last_split,current_part_length);
            array_split++;
            last_split = i + 1;
            current_part_length = 0;
            //handle the remaining string 
            if(array_split == seperator_count)
            {
                arr[array_split] = input_string.substr(last_split,input_string.length());
                array_split++;
            }
        }
        else
        {
            //if we don't have a seperator, we need to increment the current_part_length
            current_part_length++;
        }
    }
    //make sure that the seperator count
    if(seperator_count+1 > arr_size)
    {
        return -1;
    }
    return array_split;
}

/*
 * the printMountainStats function takes in an input file, and will return then number of lines read, the highest and lowest mountain, and its elevation 
 * It will return an error if an invalid file is provided.
 * The line count will not include empty lines.
*/
void printMountainStats(string filename)
{
    //declare variables
    string line;
    ifstream fin;
    int lines_read = 0;
    int tallest_mountain = 0;
    string tallest_mountain_name;
    int shortest_mountain = 100000;
    string shortest_mountain_name;
    //open the file
    fin.open(filename);
    //check if the file is open / exists
    if(fin.fail())
    {
        cout << "Could not open file." << endl;
    }
    else
    {
        //read the entire file
        while (!fin.eof())
        {
            //get the line first to make sure it's not empty
            getline(fin, line);
            //checks and makes sure the line is not empty
            if(line.length() > 0)
            {
                //split the line into an array
                string arr[3];
                split(line,'|',arr,3);
                if(stoi(arr[1]) > tallest_mountain)
                {
                    //set the new highest mountain and its name
                    tallest_mountain = stoi(arr[1]);
                    tallest_mountain_name = arr[0];
                }
                if(stoi(arr[1]) < shortest_mountain)
                {
                    //set the new shortest mountain and its names
                    shortest_mountain = stoi(arr[1]);
                    shortest_mountain_name = arr[0];
                }
                //increment the lines read
                lines_read++;
            }

        }
        //make sure file isn't empty
        if(lines_read > 0)
        {
            cout << "Number of lines read: " << lines_read << "." << endl;
            cout << "Tallest mountain: " << tallest_mountain_name << " at " <<tallest_mountain << " feet." << endl;
            cout << "Shortest mountain: " << shortest_mountain_name << " at " <<shortest_mountain << " feet." << endl;
        }
        else
        {
            cout << "No lines read, file is empty." << endl;
        }
    }   
}

int main()
{
    /* test 1
     * Expected output: 
        Number of lines read: 3.
        Tallest mountain: Pikes Peak at 14114 feet.
        Shortest mountain: Vermilion Peak at 13894 feet.
    */
    //added some padding to the tests to make them more readable.
    cout << "test 1:" << endl;
    string filename = "./data/mountain_data.txt";
    printMountainStats(filename);
    cout << "-----------" << endl;
    /* test 2
     * Expected output: 
        Number of lines read: 4.
        Tallest mountain: Mount Elbert at 14433 feet.
        Shortest mountain: Vermilion Peak at 1304 feet.
    */
    cout << "test 2:" << endl;
    filename = "./data/mountain_data_two.txt";
    printMountainStats(filename);
    cout << "-----------" << endl;

    /* test 3
     * Expected output: 
        Could not open file.
    */
    cout << "test 3:" << endl;
    filename = "./data/fake_file.txt";
    printMountainStats(filename);
    cout << "-----------" << endl;

    /* test 4
     * Expected output: 
        No lines read, file is empty.
    */
    cout << "test 4:" << endl;
    filename = "./data/empty_file.txt";
    printMountainStats(filename);
    cout << "-----------" << endl;
}