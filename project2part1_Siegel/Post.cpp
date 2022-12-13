//Post.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 2 - Problem 4

#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include "Post.h"

using namespace std;

//when a post is created, set the default values
Post::Post()
{   
    //set all values to default (empty or 0)
    body_ = "";
    post_author_ = "";
    num_likes_ = 0;
    date_ = "";
}

//if we want to create a post with values, we can use this constructor
Post::Post(string postBody, string postAuthor, int postLikes, string postDate)
{
    body_ = postBody;
    post_author_ = postAuthor;
    num_likes_ = postLikes;
    date_ = postDate;
}

//member functions for getting the post body
string Post::getPostBody()
{
    return body_;
}

//member functions for setting the post body
void Post::setPostBody(string postBody)
{
    body_ = postBody;
}

//member functions for getting the post author
string Post::getPostAuthor()
{
    return post_author_;
}

//member functions for setting the post author
void Post::setPostAuthor(string postAuthor)
{
    post_author_ = postAuthor;
}

//member functions for getting the post likes
int Post::getPostLikes()
{
    return num_likes_;
}

//member functions for setting the post likes
void Post::setPostLikes(int postLikes)
{
    if(postLikes > 0)
    {
        num_likes_ = postLikes;
    }
}

//member functions for getting the post date
string Post::getPostDate()
{
    return date_;
}

//member functions for setting the post date
void Post::setPostDate(string postDate)
{
    date_ = postDate;
}