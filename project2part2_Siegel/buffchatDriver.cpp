//Buffchat.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 2 - Question 0

#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
#include "Buffchat.h"
#include "Post.h"
#include "User.h"
using namespace std;

/*
 * buffchatDriver.cpp is a driver file for the class Buffchat.
 * It will run test to make sure the methods for buffchat are working correctly.
*/

int main()
{
    //test 1 - check all functions for empty users and posts
     /*
        Expected output: 
        No posts are stored
    */
    Buffchat buffchat;
    buffchat.printPostsByYear("2019");
    assert(buffchat.getNumPosts() == 0);
    assert(buffchat.getNumUsers() == 0);
    assert(buffchat.getPostSize() == 50);
    assert(buffchat.getUserSize() == 50);

    //test 2 - check functions for posts and users
    int result = buffchat.readPosts("file_that_doesnt_exist.txt");
    assert(result == -1);
    assert(buffchat.getNumPosts() == 0);
    result = buffchat.readLikes("file_that_doesnt_exist.txt");
    assert(result == -1);
    assert(buffchat.getNumUsers() == 0);

    //test 3 - checking full array
    buffchat.readPosts("./data/posts_full.txt");
    buffchat.readLikes("./data/users_full.txt");
    assert(buffchat.getNumPosts() == 50);
    assert(buffchat.getNumUsers() == 50);

    //test 4 - checking compounding
    Buffchat buffchat2;
    buffchat2.readPosts("./data/posts_two.txt");
    buffchat2.readPosts("./data/posts_two.txt");
    assert(buffchat2.getNumPosts() == 4);
    buffchat2.readLikes("./data/users_four.txt");
    buffchat2.readLikes("./data/users_four.txt");
    assert(buffchat2.getNumUsers() == 8);


    //test 5 (part 1) - checking print posts by year
    /* Expected output:
        No posts stored for year 2019
    */
    Buffchat buffchat3;
    buffchat3.readPosts("./data/posts_two.txt");
    buffchat3.printPostsByYear("19");

    //test 5 (part 2) - checking print posts by year
    /* Expected output:
        Here is a list of posts for year 21
        Friday night lights in Folsom
    */
    Buffchat buffchat4;
    buffchat4.readPosts("./data/posts_two.txt");
    buffchat4.printPostsByYear("21");

    //test 6 (part 1) - checking get likes
    Buffchat buffchat5;
    buffchat5.readPosts("./data/posts_two.txt");
    buffchat5.readLikes("./data/users_four.txt");
    int likes = buffchat5.getLikes("michelleryan", "Mitch");
    assert(likes == -3);

    //test 6 (part 2) - checking get likes
    Buffchat buffchat6;
    buffchat6.readPosts("./data/posts_four.txt");
    buffchat6.readLikes("./data/users_four.txt");
    likes = buffchat6.getLikes("michelleryan", "cuisthebest");
    assert(likes == 4);

    //test 7 - checking find tag user
    /*
        Expected Output:
        Here are all the usernames that contain ol
        goldenbuff3
        involvedfair
        cucornhole
    */
    Buffchat buffchat7;
    buffchat7.readPosts("./data/posts_full.txt");
    buffchat7.readLikes("./data/users_full.txt");
    buffchat7.findTagUser("ol");
    
    //test 8 - checking add post
    Buffchat buffchat8;
    buffchat8.readLikes("./data/users_full.txt");
    buffchat8.addPost("This is a test post", "Mitch", "2021-09-21");
    assert(buffchat8.getNumPosts() == 1);
    result = buffchat8.getLikes("Mitch", "michelleryan");
    assert(result == -1);

    //test 9 - checking print popular posts
    /*
        Expected Output:
        Here are the 3 most popular posts from 2021
        241 likes: Chancellor recaps and highlights topics discussed during his 2022 State of the Campus address.To watch the speech in its entirety or read more highlights click our link in bio
        218 likes: Are you team sunset or sunrise?
        221 likes: Rise and grind Buffs! It’s a brew-tiful day for a hot beverage and we cannot fully espresso how much we love coffee (hint: it’s a latte).
    */
    Buffchat buffchat9;
    buffchat9.readPosts("./data/posts_full.txt");
    buffchat9.readLikes("./data/users_full.txt");
    buffchat9.printPopularPosts(3, "21");

    //test 10 - checking least active user
    User least_active = buffchat9.findLeastActiveUser();
    assert(least_active.getUsername() == "michelleryan");

    //test 11 - count unique likes test
    assert(buffchat9.countUniqueLikes("cubouldermusic") == 91);
    assert(buffchat9.countUniqueLikes("cubuffnews") == 43);
    assert(buffchat9.countUniqueLikes("michelleryan") == 112);

    return 0;
}
