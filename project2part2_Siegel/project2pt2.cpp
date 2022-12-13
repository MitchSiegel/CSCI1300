//project2pt2.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 2 - Problem 10

#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include "Post.h"
#include "User.h"
#include "Buffchat.h"

using namespace std;

/*
*  This file is a combination of all of the other files.
 * It takes all of the previous functions and puts them into a nice and easy to use menu.
 * It will repeat the menu until exited, by using the number 10 on the menu.
*/


//print menu will print the menu
void printMenu()
{
    cout << "======Main Menu=====" << endl;
    cout << "1. Read posts" << endl;
    cout << "2. Print Posts By Year" << endl;
    cout << "3. Read Likes" << endl;
    cout << "4. Get Likes" << endl;
    cout << "5. Find users with matching tag" << endl;
    cout << "6. Add a new post" << endl;
    cout << "7. Print popular posts for a year" << endl;
    cout << "8. Find least active user" << endl;
    cout << "9. Find unique likes for a post author" << endl;
    cout << "10. Quit" << endl;
}

int main()
{
    //declare main variables
    bool user_quit = false;
    bool error = false;
    int user_input;
    //initialize buffchat to use later on
    Buffchat buffChat;
    int posts_stored;
    int users_stored;
    //loop until user_quit = true;
    while(!user_quit)
    {
        //print the menu every loop
        printMenu();
        //menu selector
        cin >> user_input;
        //handle user input
        switch(user_input)
        {
            //readPosts
            case 1:
            {
                //get filename from user
                string filename;
                cout << "Enter a post file name:" << endl;
                cin >> filename;
                //call readPosts function with user input
                int posts_read = buffChat.readPosts(filename);
                //get the number of posts currently stored in buffchat
                posts_stored = buffChat.getNumPosts();
                //handle the return value of readposts
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
                //get year from user
                string year;
                cout << "Enter the year(YY):" << endl;
                cin >> year;
                //call printPostsByYear function with user input
                buffChat.printPostsByYear(year);
                //printPostsByYear will handle printing the result
                break;
            }
            //readLikes (populate the user array)
            case 3:
            {
                //get filename from user
                string filename;
                cout << "Enter a user file name:" << endl;
                cin >> filename;
                //call readLikes with user input
                int users_read = buffChat.readLikes(filename);
                //update the number of users stored in buffchat
                users_stored = buffChat.getNumUsers();
                //handle the output of readLikes and print out the proper message
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
            //getLikes
            case 4:
            {   
                //get post_author and user_name from user
                string post_author;
                string user_name;
                cout << "Enter a post author:" << endl;
                cin >> post_author;
                cout << "Enter a user name:" << endl;
                cin >> user_name;
                //call the getLikes function with user input
                int likes = buffChat.getLikes(post_author, user_name);
                //handle the return value of getLikes
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
            //findTagUser
            case 5:
            {
                //get user input
                string tag;
                cout << "Enter a tag:" << endl;
                cin >> tag;
                //call the function with user input
                buffChat.findTagUser(tag);
                //findTagUser will handle printing the result.
                break;
            }
            //addPost
            case 6:
            {
                //get user input for all of the post variables (author, body & year).
                string post_body;
                string post_author;
                string post_date;
                cout << "Enter a post body:" << endl;
                cin >> post_body;
                cout << "Enter a post author:" << endl;
                cin >> post_author;
                cout << "Enter a date(mm/dd/yy):" << endl;
                cin >> post_date;
                //call the addPost function
                bool post_added = buffChat.addPost(post_body, post_author, post_date);
                //check if the post was added and print the appropriate message
                if(post_added)
                {
                    cout << post_author << "'s post added successfully" << endl;
                }
                else
                {
                    cout << "Database is already full. " << post_author << "'s post was not added" << endl;
                }
                break;
            }
            //printPopularPosts
            case 7:
            {
                //get user input for number of posts to list and the year to search
                int num_of_posts;
                string year;
                cout << "Enter the number of posts:" << endl;
                cin >> num_of_posts;
                cout << "Enter the year(YY):" << endl;
                cin >> year;
                //call the printPopularPosts function
                buffChat.printPopularPosts(num_of_posts, year);
                //printPopularPosts function will handle printing them out, so no need to print anything here
                break;
            }
            //findLeastActiveUser
            case 8:
            {
                //call the findLeastActiveUser function first to find the least active user
                User least_active_user = buffChat.findLeastActiveUser();
                //check if it returns a empty user object, and if so say the database is emtpy, otherwise print the username of the least active user
                if(least_active_user.getUsername() == "")
                {
                    cout << "There are no users stored" << endl;
                }
                else
                {
                    cout << least_active_user.getUsername() << " is the least active user" << endl;
                }
                break;
            }
            //countUniqueLikes
            case 9:
            {
                //handle user input for post author
                string post_author;
                cout << "Enter a post author:" << endl;
                cin >> post_author;
                //call countUniqueLikes with the given input
                int result = buffChat.countUniqueLikes(post_author);
                //handle the result of countUniqueLikes
                if(result >= 1)
                {
                    cout << "The posts posted by " << post_author << " have been liked by " << result << " unique users." << endl;
                }
                else if(result == 0)
                {
                    cout << "The posts posted by " << post_author << " have received 0 likes so far." << endl;
                }
                else if(result == -2)
                {
                    cout << "The posts posted by " << post_author << " have not been viewed by anyone." << endl;
                }
                break;
            }
            //quit
            case 10:
                //print goodbye and then quit the program by exiting the loop
                cout << "Good bye!" << endl;
                user_quit = true;
                break;
            //default handler - invalid input
            default:
                cout << "Invalid input" << endl;
                break;
        }
    }
    return 0;   
}