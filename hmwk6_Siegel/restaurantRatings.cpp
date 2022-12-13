//readPosts.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 6 - Problem # 4a

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cassert>

using namespace std;
/*
 * This file will create an array of the restaurants from a file, and their ratings.
 * It will print out the valid restaurants, and their ratings.
 * A restaurant is valid if it has the correct number of information.
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
 * readRestaurantData will read ratings from an inputted filename
 * it will return an error if the file isn't there 
 * It will use the split function above to split each line and add to the array ratings
 * It will return the number of restaurants, unless there is an error.
 * 
 */
int readRestaurantData(string filename,string restaurants[],int ratings[][3],int arrSize)
{
    //declare variables
    string line;
    ifstream fin;
    int number_of_restaurants = 0;
    int seperator_count = 0;
    //open the file
    fin.open(filename);
    //check if the file is open / exists
    if(fin.fail())
    {
        return -1;
    }
    else
    {
        //read the entire file
        while (!fin.eof())
        {
            //get the line first to make sure it's not empty
            getline(fin, line);
            //checks and makes sure the line is not empty
            if(line.length() > 0 && number_of_restaurants < arrSize){
                    //count how many splits we should expect
                for(int i = 0; i < line.length(); i++)
                {
                    if(line[i] == '~')
                    {
                        seperator_count++;
                    }
                }
                if(seperator_count == 3)
                {
                    //split the line into an array 
                    string arr[arrSize+1];
                    split(line,'~',arr,seperator_count);
                    //add the restaurant name to the array
                    restaurants[number_of_restaurants] = arr[0];
                    //add the ratings to the array of ratings
                    ratings[number_of_restaurants][0] = stoi(arr[1]);
                    ratings[number_of_restaurants][1] = stoi(arr[2]);
                    ratings[number_of_restaurants][2] = stoi(arr[3]);
                    //increment the number of restaurants
                    number_of_restaurants++;
                }
                seperator_count = 0;
            }
        }
        //close the file
        fin.close();
        //return the number of restaurants stored in the restaurants array
    }
    return number_of_restaurants;
}

/* 
 * printResults is used for testing and will print the ratings of the restaurants as long as the file can be opened and read.
*/
void printResults(int num_lines,string restaurants[], int ratings[][3])
{
    if (num_lines == -1)
    {
        cout << "Could not open file." << endl;
    }
    else
    {
        cout << "Number of lines: " << num_lines << "." << endl;
        for (int i = 0; i < num_lines; i++)
        {
            cout << restaurants[i] << endl;
        }
        for (int i = 0; i < num_lines; i++)
        {
            cout << "food quality: " << ratings[i][0] << " / 10, cleanliness: " << ratings[i][1] << " / 5, wait time: " << ratings[i][2] << " / 5" << endl;
        }
    }
}

int main()
{
    /* test 1
     * Expected output: 
        Number of lines: 3.
        Olive Garden
        Pasta Jays
        Wendys
        food quality: 9 / 10, cleanliness: 4 / 5, wait time: 1 / 5
        food quality: 7 / 10, cleanliness: 3 / 5, wait time: 3 / 5
        food quality: 6 / 10, cleanliness: 3 / 5, wait time: 2 / 5
    */
    cout << "test 1:" << endl;
    string filename = "./data/restaurant_samples.txt";
    int num_restaurants = 3;

    string restaurants[num_restaurants];
    int ratings[num_restaurants][3];

    int num_lines = readRestaurantData(filename, restaurants, ratings, num_restaurants);
    printResults(num_lines,restaurants,ratings);
    cout << "-----------" << endl;

    /* test 2
     * Expected output: 
        Chick-fil-a
        Snarfburger
        Cosmo's Pizza
        food quality: 9 / 10, cleanliness: 5 / 5, wait time: 5 / 5
        food quality: 10 / 10, cleanliness: 4 / 5, wait time: 3 / 5
        food quality: 7 / 10, cleanliness: 3 / 5, wait time: 2 / 5
    */
    cout << "test 2:" << endl;
    filename = "./data/restaurant_sample_two.txt";
    num_restaurants = 3;

    string restaurants_two[num_restaurants];
    int ratings_two[num_restaurants][3];

    num_lines = readRestaurantData(filename, restaurants_two, ratings_two, num_restaurants);
    printResults(num_lines,restaurants_two,ratings_two);
    cout << "-----------" << endl;

    /* test 3
     * Expected output: 
        Number of lines: 0.
    */
    cout << "test 3:" << endl;
    filename = "./data/empty_file.txt";
    num_restaurants = 3;

    string restaurants_three[num_restaurants];
    int ratings_three[num_restaurants][3];

    num_lines = readRestaurantData(filename, restaurants_three, ratings_three, num_restaurants);
    printResults(num_lines,restaurants_three,ratings_three);
    cout << "-----------" << endl;

    /* test 4
     * Expected output: 
        Could not open file.
    */
    cout << "test 4:" << endl;
    filename = "./data/does_not_exist.txt";
    num_restaurants = 3;

    string restaurants_four[num_restaurants];
    int ratings_four[num_restaurants][3];

    num_lines = readRestaurantData(filename, restaurants_four, ratings_four, num_restaurants);
    printResults(num_lines,restaurants_four,ratings_four);
    cout << "-----------" << endl;
}