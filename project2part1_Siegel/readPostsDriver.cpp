//readPostsDriver.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 2 - Problem 2

#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include "Post.h"

using namespace std;


/*
 * This file is a driver (testing file) for the function readPosts.
 * It will read in a file of posts and store them in an array of Post objects.
 * If the file is not found, it will return -1 and not fill the array.
 * If the file is found, it will return the number of posts read in.
 * If there is not enough space in the array for all of the posts, it will return -1
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
 * the readPosts function takes in a filename to read from and an array of posts to fill.
 * It will read the file and fill the array with the posts.
 * If the file is not found, it will return -1.
 * If the number of posts is equal to the array size, it will return -2.
*/
int readPosts(string file_name, Post posts[], int num_posts_stored, int posts_arr_size)
{
    //handle critical errors
    if(num_posts_stored == posts_arr_size)
    {
        return -2;
    }
    //open the file
    ifstream file;
    file.open(file_name);

    //check and make sure the file opened correctly
    if(file.fail())
    {
        return -1;
    }
    //read the file line by line
    string line;
    int i;
    i  = num_posts_stored;
    string tempArry[4];

    while(getline(file, line))
    {
        //make sure the line is not empty
        if(line.length() > 0)
        {
            //split the line into an array and store the result
            int number_of_fields = split(line, ',', tempArry, 4);
            //make sure the post has all required fields by checking the split function
            if(number_of_fields == 4)
            {
                //create a post object
                posts[i].setPostBody(tempArry[0]);
                posts[i].setPostAuthor(tempArry[1]);
                posts[i].setPostLikes(stoi(tempArry[2]));
                posts[i].setPostDate(tempArry[3]);
                //iterate the number of posts
                i++;
            }
            //return the array if its full
            if(i == posts_arr_size)
            {
                return posts_arr_size;
            }
        
        }

    }
    file.close();
    return i;
}



int main()
{
    //test 1 - normal case
    Post posts[10];
    int num_posts = 0;
    int num_posts_stored = 0;
    num_posts = readPosts("./data/posts.txt", posts, num_posts_stored, 10);
    assert(num_posts == 10);

    //test 2 - file not found
    num_posts = readPosts("doesn't-exist.txt", posts, num_posts_stored, 10);
    assert(num_posts == -1);

    //test 3 - empty lines
    num_posts = readPosts("./data/posts-empty-lines.txt", posts, num_posts_stored, 10);
    //test file has 2 empty lines and 3 posts
    assert(num_posts == 3);

    //test 4 - making sure the data is read and stored correctly
    num_posts = readPosts("./data/posts-test4.txt", posts, num_posts_stored, 10);
    assert(posts[0].getPostBody() == "Test body again");
    assert(posts[0].getPostAuthor() == "user10");
    assert(posts[0].getPostLikes() == 20);
    assert(posts[0].getPostDate() == "11/10/21");

    //test 5 - not enough space in the array, should fill as many as possible
    Post post_two[3];
    num_posts = readPosts("./data/posts.txt", post_two, num_posts_stored, 3);
    assert(num_posts == 3);

    //test 6 - array is full
    num_posts_stored = 3;
    num_posts = readPosts("./data/posts.txt", post_two, num_posts_stored, 3);
    assert(num_posts == -2);

    return 0;   
} 
