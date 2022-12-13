//readLikesDriver.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 2 - Problem 5

#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include "User.h"

using namespace std;
/*
 * This file is a driver (testing file) for the function readLikes.
 * It will run 4 tests on the readLikes function to make sure it works correctly.
 * It uses assert statements to check if the function is working correctly.
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
 * The function readLikes will populate an array of User objects with the data from a file.
 * It will return the number of users read.
 * It will populate the users' likes with the data from the file.
*/
int readLikes(string file_name, User users[], int num_users_stored, int users_arr_size, int max_posts)
{
    //declare variables
    string line;
    int arr_size = max_posts;
    int split_count = 0;
    int num_likes = 0;
    int current_user = num_users_stored;
    //if the array is full, return -2
    if(num_users_stored == users_arr_size)
    {
        return -2;
    }
    //open the file
    ifstream file;
    file.open(file_name);
    //if the file open fails, return -1
    if(file.fail())
    {
        return -1;
    }
    //loop through the file line by line
    while(getline(file,line))
    {
        //check and make sure the line isn't empty
        if(line.length() > 0)
        {
            if(current_user == users_arr_size)
            {
                return current_user;
            }
            //split the line by the comma and store it in an array
            string arr[max_posts+1];
            split_count = split(line,',',arr,arr_size+1);
            //set the username
            users[current_user].setUsername(arr[0]);
            //set the number of likes
            users[current_user].setNumPosts(split_count-1);
            //loop through the array and set the likes
            for(int i = 1; i <= max_posts; i++)
            {
                users[current_user].setLikesAt(i-1,stoi(arr[i]));     
            }
            //add one to the current user so it will go to the next user
            current_user++;
        }
    }
    //close the file
    file.close();
    //return the number of users stored
    return current_user;
}

int main()
{
    //test 1 - normal functionality
    User users[10]; 
    int num_users_stored = 0; 
    int users_arr_size = 10; 
    int max_posts = 3;
    int num_users = readLikes("./data/users_two.txt", users,num_users_stored, users_arr_size, max_posts);
    assert(num_users == 2);

    //test 2 - file doesn't exist
    int num_users2 = readLikes("notfound.txt", users,num_users_stored, users_arr_size, max_posts);
    assert(num_users2 == -1);

    //test 3 - checking and making sure its reading correctly
    User users2[10];
    int num_users_stored2 = 0;
    int users_arr_size2 = 10;
    int max_posts2 = 3;
    int num_users3 = readLikes("./data/users_three.txt", users2,num_users_stored2, users_arr_size2, max_posts2);
    assert(num_users3 == 2);
    assert(users2[0].getUsername() == "mitch");
    assert(users2[0].getNumPosts() == 3);
    assert(users2[0].getLikesAt(0) == -1);
    assert(users2[0].getLikesAt(1) == 1);
    assert(users2[0].getLikesAt(2) == 8);

    //test 4 - array is full
    User users3[10];
    int num_users_stored3 = 10;
    int users_arr_size3 = 10;
    int max_posts3 = 3;
    int num_users4 = readLikes("./data/users_four.txt", users3,num_users_stored3, users_arr_size3, max_posts3);
    assert(num_users4 == -2);
    
    return 0; 
}