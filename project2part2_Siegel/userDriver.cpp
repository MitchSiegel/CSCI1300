//userDriver.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 2 - Problem 4

#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include "User.h"

/*
 * This file is a driver for the User class. It will test the methods of the User class.
*/
using namespace std;
int main()
{
    //test default constructor
    User user1;
    assert(user1.getUsername() == "");
    assert(user1.getLikesAt(0) == -1);
    assert(user1.getLikesAt(1) == -1);

    //test parameterized constructor
    int likes[3] = {1, 2, 3};
    User user2("Mitch", likes, 3);
    assert(user2.getUsername() == "Mitch");
    assert(user2.getLikesAt(0) == 1);
    assert(user2.getLikesAt(1) == 2);
    assert(user2.getLikesAt(2) == 3);
    assert(user2.getLikesAt(49) == -1);

    //test setUsername
    user2.setUsername("Mitchell");
    assert(user2.getUsername() == "Mitchell");

    //test setLikesAt
    user2.setLikesAt(0, 5);
    assert(user2.getLikesAt(0) == 5);

    //test getNumPosts
    assert(user2.getNumPosts() == 3);
    
    //test setNumPosts
    user2.setNumPosts(5);
    assert(user2.getNumPosts() == 5);

    //test getSize
    assert(user2.getSize() == 50);

    return 0;   
}