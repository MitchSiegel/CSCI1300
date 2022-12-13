//Buffchat.h

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 2 - Question 0

using namespace std;
#include "Post.h"
#include "User.h"
#pragma once

class Buffchat
{
    public:
        Buffchat();
        int getPostSize();
        int getUserSize();
        int getNumPosts();
        int getNumUsers();
        int readPosts(string file_name);
        void printPostsByYear(string year);
        int readLikes(string file_name);
        int getLikes(string post_author, string username);
        void findTagUser(string username_tag);
        bool addPost(string post_body, string post_author, string date);
        void printPopularPosts(int count, string year);
        User findLeastActiveUser();
        int countUniqueLikes(string post_author);
    private:
        int posts_size_ = 50;
        int users_size = 50;
        Post posts_[50];
        User users_[50];
        int num_posts_;
        int num_users_;
};