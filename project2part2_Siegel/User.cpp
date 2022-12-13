//User.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 2 - Problem 4

#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include "User.h"

using namespace std;

//default constructor
User::User(){
    username_ = "";
    //set all elements of _likes to -1
    for(int i = 0; i < 50; i++)
    {
        likes_[i] = -1;
    }
    num_posts_ = 0;
    size_ = 50;
}

//constructor with parameters
User::User(string username, int likes[], int n)
{
    //declare variables
    username_ = username;
    num_posts_ = n;
    for(int i = 0; i < n; i++)
    {
            likes_[i] = likes[i];
    }
    //set all remaining elements of likes_ to -1
    for(int i = n; i < size_; i++)
    {
        likes_[i] = -1;
    }
}
//get method for username
string User::getUsername()
{
    return username_;
}
//set method for username
void User::setUsername(string username)
{
    username_ = username;
}
//get method for likes at a certain index (post_id)
int User::getLikesAt(int post_id)
{
    //make sure post_id is greater than 0 and less than 50 (inclusive) 
    if(post_id >= 0 && post_id < 50)
    {
        return likes_[post_id];
    }
    else
    {
        return -2;
    }
    
}

bool User::setLikesAt(int post_id, int num_likes)
{
    //num_likes is greater than 0 and less than 10 and make sure post_id is greater than 0 and less than 50 
    if(num_likes < -1 || num_likes > 10 || post_id < 0 || post_id > 50 || num_posts_ <= post_id)
    {
        return false;
    }else{
        likes_[post_id] = num_likes;
        return true;
    }
}
//get method for number of posts
int User::getNumPosts()
{
    return num_posts_;
}

//set method for number of posts
void User::setNumPosts(int posts)
{
    if(posts >= 0 && posts <= size_)
    {
        num_posts_ = posts;
    }
}

//get method for size
int User::getSize(){
    return size_;
}