//project2pt1.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 2 - Problem 8

#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include "Post.h"
#include "User.h"
using namespace std;

/*
*  This file is a combination of all of the other files.
 * It takes all of the previous functions and puts them into a nice and easy to use menu.
 * It will repeat the menu until exited, by using the number 6 on the menu.
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


//print menu will print the menu
void printMenu()
{
    cout << "======Main Menu======" << endl;
    cout << "1. Read Posts" << endl;
    cout << "2. Print Posts By Year" << endl;
    cout << "3. Read Likes" << endl;
    cout << "4. Get Likes" << endl;
    cout << "5. Find users with matching tag" << endl;
    cout << "6. Quit" << endl;
}

/*
 * The function readLikes will populate an array of User objects with the data from a file.
 * It will return the number of users read.
 * It will populate the users' likes with the data from the file.
*/
int readLikes(string file_name, User users[], int num_users_stored, int users_arr_size, int max_posts)
{
    //declare variables
    string line;
    int arr_size = max_posts;
    int split_count = 0;
    int num_likes = 0;
    int current_user = num_users_stored;
    //if the array is full, return -2
    if(num_users_stored == users_arr_size)
    {
        return -2;
    }
    //open the file
    ifstream file;
    file.open(file_name);
    //if the file open fails, return -1
    if(file.fail())
    {
        return -1;
    }
    //loop through the file line by line
    while(getline(file,line))
    {
        //if the line is empty, skip it
        if(line.length() > 0)
        {
            if(current_user == users_arr_size)
            {
                return current_user;
            }
            //split the line by the comma and store it in an array
            string arr[max_posts+1];
            split_count = split(line,',',arr,arr_size+1);
            //set the username
            users[current_user].setUsername(arr[0]);
            //set the number of likes
            users[current_user].setNumPosts(split_count-1);
            //loop through the array and set the likes
            for(int i = 1; i < max_posts; i++)
            {
                if(arr[i].length() != 0)
                {
                    users[current_user].setLikesAt(i-1,stoi(arr[i]));
                }
            }
            //add one to the current user so it will go to the next user
            current_user++;
        }

    }
    //close the file
    file.close();
    //return the number of users stored
    return current_user;
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
                if(tempArry[0].length() > 0 && tempArry[1].length() > 0 && tempArry[2].length() > 0 && tempArry[3].length() > 0)
                {
                    //create a post object
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
            if(posts[i].getPostDate() != ""){
                if(posts[i].getPostDate().substr(6,2) == year)
                {
                    num_post_year++;
                }
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

/*
 * the getLikes takes in the post_author, an array of posts, the number of posts stored, the given username, a user array and num_users_stored.
 * It will return the number of likes a given user has liked by a given author.
 * It will also make sure that both the number of users stored and the number of posts stored is not zero.
 * It will return -1 if there are no posts by the author given or if the user doesn't exist.
 *
*/
int getLikes(string post_author, Post posts[],int num_posts_stored, string username,User users[],int num_users_stored)
{
    int likes = 0;
    int userIndex = -1;
    int postIndex = -1;
    bool found = false;
    //check if num_users_stored and num_posts_stored is 0 or less 
    if(num_users_stored <= 0 || num_posts_stored <= 0)
    {
        return -2;
    }
    if(username == post_author){
        return 0;
    }
    //loop through users array to find the index of the user
    // if the user isn't found, the userIndex will not be changed (still -1)
    for(int i = 0; i < num_users_stored; i++)
    {
        if(users[i].getUsername() == username)
        {
            userIndex = i;
        }
    }
    //loop through posts array to find the index of the post
    // if the post isn't found, the postIndex will not be changed (still -1)
    for(int i = 0; i < num_posts_stored; i++)
    {
        if(posts[i].getPostAuthor() == post_author && !found)
        {
            postIndex = i;
            //only find the FIRST post.
            found = true;
        }
    }
    //if the user or post isn't found, return -3
    if(userIndex == -1 || postIndex == -1)
    {
        return -3;
    }
    //Return the value of likes from the user for the post posted by post_author
    return users[userIndex].getLikesAt(postIndex);
}

/* 
 * findTagUser takes in a username tag, an array of users and the number of users stored.
 * It will find all usernames that have the given tag.
 * It will print out the usernames that have the tag, if any have it.
 * If a user with the tag is not found, it will print that no matches have been found.
 * If there are no users, it will print that no users have been found.
 * It doesn't return anything.
*/
void findTagUser(string username_tag,User users[], int num_users_stored)
{
    //delcare variables
    bool users_found = false;
    bool no_users_stored = false;
    string found_users[num_users_stored];
    string current_username;
    //if there are zero users, display that error.
    if(num_users_stored == 0)
    {
        no_users_stored = true;
        cout << "No users are stored in the database" << endl;
    }
   //loop for each number of users
   for(int i = 0; i < num_users_stored;i++)
   {
        //get the current user's username
        current_username = users[i].getUsername();
        //loop for each character in the username
        for(int j = 0; j < current_username.length();j++)
        {
            //if the username contains the tag, add it to the found_users array
            if(current_username.substr(j,username_tag.length()) == username_tag)
            {
                found_users[i] = current_username;
                //set users_found to true because we found atleast one match
                users_found = true;
            }
        }
   }
   //display if there are no matches
   if(!no_users_stored)
   {
        if(users_found == false)
        {
            cout << "No matching user found" << endl;
        }
        //display the matches
        else
        {
            cout << "Here are all the usernames that contain " << username_tag << endl;
            for(int i = 0; i < num_users_stored;i++)
            {
                if(found_users[i] != "")
                {
                    cout << found_users[i] << endl;
                }
            }
        }
   }
}

int main()
{
    //declare variables
    bool user_quit = false;
    bool error = false;
    int user_input;
    //fill the users array with 50 users and 50 posts
    User filled_users[50]; 
    readLikes("users.txt",filled_users,0,50,50);
    Post filled_posts[50];
    readPosts("posts.txt",filled_posts,0,50);
    User empty_users[50];
    Post empty_posts[50];
    int posts_stored = 0;
    int users_stored = 0;
    //repeat until the user quits
    while(!user_quit)
    {
        printMenu();
        //ask for menu input
        cin >> user_input;
        switch(user_input)
        {
            //readPosts
            case 1:
            {
                //user input for filename
                string filename;
                cout << "Enter a post file name:" << endl;
                cin >> filename;
                //call readposts
                int posts_read = readPosts(filename,empty_posts,posts_stored,50);
                //handle the results of readposts
                if(posts_read > 0){
                    posts_stored = posts_read;
                }
                if(posts_read == -1)
                {
                    cout << "File failed to open. No posts saved to the database." << endl;
                }
                else if(posts_read == 50)
                {
                    cout << "Database is full. Some posts may have not been added." << endl;
                }
                else if(posts_read == -2 || posts_stored > 50)
                {
                    cout << "Database is already full. No posts were added." << endl;
                }
                else
                {
                    cout << "Total posts in the database: " << posts_read << endl;
                }
                
                break;
            } 
            //printPostsByYear
            case 2:
            {
                //user input for year
                string year;
                cout << "Enter the year(YY):" << endl;
                cin >> year;
                //call printPostsByYear. It is a void function and will print the results itself.
                printPostsByYear(empty_posts,year,posts_stored);
                break;
            }
            //readLikes
            case 3:
            {
                //user input for filename
                string filename;
                cout << "Enter a user file name:" << endl;
                cin >> filename;
                //call readLikes
                int users_read = readLikes(filename,empty_users,users_stored,50,50);
                //handle the results of readLikes
                if(users_read > 0){
                    users_stored = users_read;
                }
                if(users_read == -1)
                {
                    cout << "File failed to open. No users saved to the database." << endl;
                }
                else if(users_read == -2)
                {
                    cout << "Database is already full. No users were added." << endl;
                }
                else if(users_read == 50)
                {
                    cout << "Database is full. Some users may have not been added." << endl;
                }
                else
                {
                    cout << "Total users in the database: " << users_read << endl;
                }
                break;
            }
            //getLikes (fill user array with users)
            case 4:
            {   
                //user input for user_name and post_author
                string post_author;
                string user_name;
                cout << "Enter a post author:" << endl;
                cin >> post_author;
                cout << "Enter a user name:" << endl;
                cin >> user_name;
                //call getLikes
                int likes = getLikes(post_author,empty_posts,posts_stored,user_name,empty_users,users_stored);
                //handle the results of getLikes
                if(likes == -2)
                {
                    cout << "Database is empty." << endl;
                }
                else if(likes == -3)
                {
                    cout << user_name << " or " << post_author << " does not exist." << endl;
                }
                else if(likes == 0)
                {
                    cout << user_name << " has not liked the post posted by " << post_author << endl;
                }
                else if(likes == -1)
                {
                    cout << user_name << " has not viewed the post posted by " << post_author << endl;
                }
                else
                {
                    cout << user_name << " liked the post posted by " << post_author << " " << likes << " times" << endl;
                }
                break;
            }
            //find users with substring (tag) in their username
            case 5:
            {
                //user input for tag
                string tag;
                cout << "Enter a tag:" << endl;
                cin >> tag;
                //call findUsers. It is a void function and will print the results itself.
                findTagUser(tag,empty_users,users_stored);
                break;
            }
            //quit
            case 6:
            {
                //print out good bye and set user_quit to true to exit the loop
                cout << "Good bye!" << endl;
                user_quit = true;
                break;
            }
            //invalid input
            default:
            {
                //print out invalid input and and break the switch so it will ask for input again
                cout << "Invalid input." << endl;
                break;
            }
        }
    }
    return 0;   
}