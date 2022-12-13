//Post.h

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 2 - Supporting File

#include <iostream> 
#pragma once
using namespace std;
class User
{ 
    public: 
        //default constructor
        User();
        //constructor with parameters
        User(string username, int likes[], int _size);

        //methods for username
        string getUsername();
        void setUsername(string username);

        //methods for likes
        int getLikesAt(int post_id);
        bool setLikesAt(int post_id, int num_likes);

        //methods for num_posts
        int getNumPosts();
        void setNumPosts(int posts);

        //method for size
        int getSize();
    private:
      string username_;
      int num_posts_;
      int size_;
      int likes_[50];
};
