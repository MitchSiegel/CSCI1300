//Post.h

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 2 - Supporting File (for question 1)

#include <iostream> 
using namespace std; 
#pragma once
class Post 
{ 
    public:
        // default constructor
        Post();
        // parameterized constructor
        Post(string postBody, string postAuthor, int postLikes, string postDate);
        //read and write methods for post body
        string getPostBody();
        void setPostBody(string postBody);
        //read and write methods for post author
        string getPostAuthor();
        void setPostAuthor(string postAuthor);
        //read and write methods for post likes
        int getPostLikes();
        void setPostLikes(int postLikes);
        //read and write methods for post date
        string getPostDate();
        void setPostDate(string postDate);
    private: 
        string body_;
        string post_author_;
        int num_likes_;
        string date_;
};