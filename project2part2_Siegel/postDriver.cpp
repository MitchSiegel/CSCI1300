//postDriver.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 2 - Problem 1

#include <iostream>
#include <string>
#include <fstream>
#include <cassert>

using namespace std;

#include "Post.h"
/*
 * postDriver is a driver file for the post.h class.
 * It runs test to makes sure everything works correctly in the class and its parameters
*/

int main()
{
    //test 1 - testing default test 
    Post defaultValues;
    cout << defaultValues.getPostBody() << endl;
    assert(defaultValues.getPostBody() == "");
    assert(defaultValues.getPostAuthor() == "");
    cout << defaultValues.getPostAuthor() << endl;


    //test 2 - setter functions test - set post likes
    string body = "body";
    string author = "username";
    int likes = 2;
    string d = "date";

    Post testTwoPost = Post(body, author, likes, d);
    testTwoPost.setPostLikes(5);
    assert(testTwoPost.getPostLikes() == 5);

    //test 3 - setter function test - set post author and set post date
    body = "body";
    author = "username";
    likes = 2;
    d = "date";

    Post testThreePost= Post(body, author, likes, d);
    testThreePost.setPostAuthor("Mitch");
    testThreePost.setPostDate("11/20/21");
    assert(testThreePost.getPostAuthor() == "Mitch");
    assert(testThreePost.getPostDate() == "11/20/21");

    return 0;
}