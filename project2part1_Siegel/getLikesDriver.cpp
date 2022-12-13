//getLikesDriver.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 2 - Problem 6

#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include "Post.h"
#include "User.h"

using namespace std;

/* 
 * This file is a driver file for the getLikes function.
 * It uses assert statements to make sure the function is working properly.
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
 * the getLikes takes in the post_author, an array of posts, the number of posts stored, the given username, a user array and num_users_stored.
 * It will return the number of likes a given user has liked by a given author.
 * It will also make sure that both the number of users stored and the number of posts stored is not zero.
 * It will return -1 if there are no posts by the author given or if the user doesn't exist.
 *
*/
int getLikes(string post_author, Post posts[],int num_posts_stored, string username,User users[],int num_users_stored)
{
    int likes = 0;
    int userIndex = -1;
    int postIndex = -1;
    bool found = false;
    //check if num_users_stored and num_posts_stored is 0 or less 
    if(num_users_stored <= 0 || num_posts_stored <= 0)
    {
        return -2;
    }
    if(username == post_author){
        return 0;
    }
    //loop through users array to find the index of the user
    // if the user isn't found, the userIndex will not be changed (still -1)
    for(int i = 0; i < num_users_stored; i++)
    {
        if(users[i].getUsername() == username)
        {
            userIndex = i;
        }
    }
    //loop through posts array to find the index of the post
    // if the post isn't found, the postIndex will not be changed (still -1)
    for(int i = 0; i < num_posts_stored; i++)
    {
        if(posts[i].getPostAuthor() == post_author && !found)
        {
            postIndex = i;
            //only find the FIRST post.
            found = true;
        }
    }
    //if the user or post isn't found, return -3
    if(userIndex == -1 || postIndex == -1)
    {
        return -3;
    }
    //Return the value of likes from the user for the post posted by post_author
    return users[userIndex].getLikesAt(postIndex);
}

int main()
{
    //Creating posts for testing purposes. Data is sourced from the github. 
    //Code to create the posts and users is also taken from the example runs on the github.
    Post posts[3]; 
    Post my_post_1 = Post("Hello!","Xuefei", 10, "10/02/22");
    posts[0] = my_post_1;
    Post my_post_2 = Post("new post","Morgan", 9, "10/04/22");
    posts[1] = my_post_2;
    Post my_post_3 = Post("Hey!","Jot", 10, "10/05/22");
    posts[2] = my_post_3;

    //Create 2 users for testing purposes
    User users[2];
    int likes1[3] = {1, 3, 2};
    User u1 = User("bookworm43", likes1, 3);
    users[0] = u1;
    users[1].setUsername("roboticscu");
    users[1].setLikesAt(0,-1); 
    users[1].setLikesAt(1,2); 
    users[1].setLikesAt(2,4);
    
    //test 1 (normal functionality)
    int result = getLikes("Xuefei", posts, 3, "bookworm43", users, 2);
    assert(result == 1);

    //test 2 (post author isn't found)
    result = getLikes("Morgan", posts, 3, "cubikingclub", users, 2);
    assert(result == -3);

    //test 3 (username doesn't exist)
    result = getLikes("Mitch", posts, 3, "bookworm43", users, 2);
    assert(result == -3);

    //test 4 (username & poster don't exist)
    result = getLikes("Mitch", posts, 3, "mitch", users, 2);
    assert(result == -3);
    return 0;   
}
