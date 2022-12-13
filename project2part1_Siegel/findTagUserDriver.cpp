//findTagUserDriver.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 2 - Problem 7

#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include "Post.h"
#include "User.h"

using namespace std;
/*
 * This file is a driver file for the function findTagUser. 
 * It tests the function to make sure it is working correctly.
 * It will print out the results, along with the test number.
 * Because it is a void function, the comments will show what the expected output is.
*/

/* 
 * findTagUser takes in a username tag, an array of users and the number of users stored.
 * It will find all usernames that have the given tag.
 * It will print out the usernames that have the tag, if any have it.
 * If a user with the tag is not found, it will print that no matches have been found.
 * If there are no users, it will print that no users have been found.
 * It doesn't return anything.
*/
void findTagUser(string username_tag,User users[], int num_users_stored)
{
    //delcare variables
    bool users_found = false;
    bool no_users_stored = false;
    string found_users[num_users_stored];
    string current_username;
    //if there are zero users, display that error.
    if(num_users_stored == 0)
    {
        no_users_stored = true;
        cout << "No users are stored in the database" << endl;
    }
   //loop for each number of users
   for(int i = 0; i < num_users_stored;i++)
   {
        //get the current user's username
        current_username = users[i].getUsername();
        //loop for each character in the username
        for(int j = 0; j < current_username.length();j++)
        {
            //if the username contains the tag, add it to the found_users array
            if(current_username.substr(j,username_tag.length()) == username_tag)
            {
                found_users[i] = current_username;
                //set users_found to true because we found atleast one match
                users_found = true;
            }
        }
   }
   //display if there are no matches
   if(!no_users_stored)
   {
        if(users_found == false)
        {
            cout << "No matching user found" << endl;
        }
        //display the matches
        else
        {
            cout << "Here are all the usernames that contain " << username_tag << endl;
            for(int i = 0; i < num_users_stored;i++)
            {
                if(found_users[i] != "")
                {
                    cout << found_users[i] << endl;
                }
            }
        }
   }
}

int main()
{
    //data has been partially sources from the github.
    //define variables for tests cases
    User user_array[5];
    int likes1[3] = {1, 0, -1};
    int likes2[3] = {4, 5, 0};
    // set data for test case 1
    user_array[0] = User("mitch1", likes1, 3);
    user_array[1] = User("mitch123", likes2, 3);
    user_array[2] = User("mitch1234", likes2, 3);
    user_array[3] = User("luwkml1", likes2, 3);
    user_array[4] = User("fwollow3", likes1, 3);

    /*
     - test case 1 (normal operation but with only one match)
        Expected Output:

        Here are all the usernames that contain 1234
        mitch1234
    */
    cout << "test case 1: " << endl;
    cout << "-----------------" << endl;
    findTagUser("1234", user_array, 5);
    cout << "-----------------" << endl;

    //redefine data for test case 2
    user_array[0] = User("foliwn22", likes1, 3);
    user_array[1] = User("joh23k", likes2, 3);
    user_array[2] = User("harryol02", likes2, 3);
    user_array[3] = User("luwkml1", likes2, 3);
    user_array[4] = User("fwollow3", likes1, 3);

    /*
     - test case 2  (normal operation but with a few matches)
        Expected Output:

        Here are all the usernames that contain ol
        foliwn22
        harryol02
        fwollow3
    */
    cout << "test case 2: " << endl;
    cout << "-----------------" << endl;
    findTagUser("ol", user_array, 5);
    cout << "-----------------" << endl;

    /*
    - test case 3 (no users stored in the database)
        Expected Output:

        No users are stored in the database
    */
    cout << "test case 3: " << endl;
    cout << "-----------------" << endl;
    findTagUser("ol", user_array, 0);
    cout << "-----------------" << endl;

    /*
    - test case 4
        Expected Output:

        No matching user found
    */
    cout << "test case 4: " << endl;
    cout << "-----------------" << endl;
    findTagUser("no", user_array, 5);
    cout << "-----------------" << endl;
    return 0;   
}