//printPostsByYear.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 2 - Problem 3

#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include "Post.h"

using namespace std;

/*
 * This file will tests the function printPostsByYear.
 * It will read an array of posts and take in an inputted year (YY format).
 * It will then print out all of the posts that were made in that year.
 * If there are no posts in that year, it will print "No posts found".
 * If there are no posts provided, it will print "No posts are stored".
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
    int num_posts = num_posts_stored;
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
    while(getline(file, line))
    {
        //make sure the line is not empty
        if(line.length() > 0)
        {
            //make sure the array can hold the post
            if(i < posts_arr_size)
            {
                //split the line into an array
                string tempArry[10];
                split(line, ',', tempArry, 4);
                //make sure the post has all required fields
                if(tempArry[0] != "" && tempArry[1] != "" && stoi(tempArry[2]) != ' ' && tempArry[3] != "")
                {
                    //populate the post array
                    posts[i].setPostBody(tempArry[0]);
                    posts[i].setPostAuthor(tempArry[1]);
                    posts[i].setPostLikes(stoi(tempArry[2]));
                    posts[i].setPostDate(tempArry[3]);
                    num_posts++;
                }
            }
            i++;
        }

    }
    file.close();
    return num_posts;
}

/*
 * the printPostsByYear function takes in an array of posts and the number of posts stored.
 * It will print out all of the posts in the array that were posted in the given year.
*/
void printPostsByYear(Post posts[], string year, int num_posts_stored)
{
    int num_post_year = 0;
    //there are no posts in the array
    if(num_posts_stored == 0)
    {
        cout << "No posts are stored" << endl;
    }
    else{
        //loop through the array to make sure there are posts in the given year.
        for(int i = 0; i < num_posts_stored; i++)
        {
            //make sure the post is in the given year
            if(posts[i].getPostDate().substr(6,4) == year)
            {
                num_post_year++;
            }
        }
        //if there are no posts in the given year, print out that there are no posts.
        if(num_post_year == 0)
        {
            cout << "No posts stored for year " << year << endl;
        }
        //there are posts in the given, so lets print them.
        else
        {
            cout << "Here is a list of posts for year " << year << endl;
            for(int i = 0; i < num_posts_stored; i++)
            {
                //make sure the post is in the given year
                if(posts[i].getPostDate().substr(6,4) == year)
                {
                    cout << posts[i].getPostBody() << endl;
                }
            }
        }

    }

}

int main()
{
    /*
     * test case 1: making sure the function works under normal circumstances
     * Expected output:
        Here is a list of posts for year 22
        new post1
        new post2
    */
    cout << "test 1: " << endl;
    cout << "---------" << endl;
    Post post_1 = Post("new post1","Mitch1", 10, "10/02/22");
    Post post_2 = Post("new post2","Mitch2", 11, "10/02/22");
    Post post_3 = Post("new post3","Mitch3", 8, "10/02/18");
    Post list_of_posts[] = {post_1, post_2, post_3};
    int number_of_posts = 3;
    string year = "22";
    printPostsByYear(list_of_posts, year, number_of_posts);
    cout << "---------" << endl;

    /*
     * test case 2: making sure the function works when there are no posts in the given year
     * Expected output:
        No posts found for year 19
    */
    cout << "test 2: " << endl;
    cout << "---------" << endl;
    year = "19";
    printPostsByYear(list_of_posts, year, number_of_posts);
    cout << "---------" << endl;

    /*
     * test case 3: making sure the function works when there are no posts at all
     * Expected output:
        No posts are stored
    */
    cout << "test 3: " << endl;
    cout << "---------" << endl;
    number_of_posts = 0;
    printPostsByYear(list_of_posts, year, number_of_posts);
    cout << "---------" << endl;
    
    return 0;   
}