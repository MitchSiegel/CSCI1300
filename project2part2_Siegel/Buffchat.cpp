//Buffchat.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 2 - Question 0
#include <iostream>
#include <fstream>
#include <string>
#include "Buffchat.h"
#include "Post.h"
#include "User.h"
using namespace std;


/*
 * This file is where all of the functions for the Buffchat class are defined.
*/

//default constructor, sets all values to default
Buffchat::Buffchat()
{
    num_posts_ = 0;
    num_users_ = 0;
}

//returns the constant posts_size_ (50)
int Buffchat::getPostSize()
{
    return posts_size_;
}

//returns the constant users_size_ (50)
int Buffchat::getUserSize()
{
    return users_size;
}
//returns the number of posts stored
int Buffchat::getNumPosts()
{
    return num_posts_;
}

//returns the number of users stored
int Buffchat::getNumUsers()
{
    return num_users_;
}

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
* the readPosts function takes in a file name and will populate the posts array with the posts from the file.
* It will return the number of posts read.
* If the file is not found, it will return -1.
* If there is no room in the array, it will return -2.
*/
int Buffchat::readPosts(string file_name)
{
 
    //handle critical errors
    if(num_posts_ == posts_size_)
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
    i  = num_posts_;
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
                posts_[i].setPostBody(tempArry[0]);
                posts_[i].setPostAuthor(tempArry[1]);
                posts_[i].setPostLikes(stoi(tempArry[2]));
                posts_[i].setPostDate(tempArry[3]);
                //iterate the number of posts
                i++;
                num_posts_++;
            }
            //return the array if its full
            if(i == posts_size_)
            {
                return posts_size_;
            }
        }

    }
    file.close();
    return i;
}

/*
 * printPostsByYear takes in a year and will print all stored posts from that year.
*/
void Buffchat::printPostsByYear(string year)
{
    int num_post_year = 0;
    //there are no posts in the array
    if(num_posts_ == 0)
    {
        cout << "No posts are stored" << endl;
    }
    else{
        //loop through the array to make sure there are posts in the given year.
        for(int i = 0; i < num_posts_; i++)
        {
            //make sure the post is in the given year
            if(posts_[i].getPostDate().substr(6,4) == year)
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
            for(int i = 0; i < num_posts_; i++)
            {
                //make sure the post is in the given year
                if(posts_[i].getPostDate().substr(6,4) == year)
                {
                    cout << posts_[i].getPostBody() << endl;
                }
            }
        }

    }
}

/*
 * readLikes takes in a file name and will populate the user array with the users from the file.
*/
int Buffchat::readLikes(string file_name)
{
     //declare variables
    string line;
    int arr_size = users_size;
    int split_count = 0;
    int num_likes = 0;
    int current_user = num_users_;
    //if the array is full, return -2
    if(num_users_ == users_size)
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
        if(current_user == users_size)
        {
            return users_size;
        }
        //if the line is empty, skip it
        if(line.length() > 0){
            //split the line by the comma and store it in an array
            string arr[posts_size_+1];
            split_count = split(line,',',arr,arr_size+1);
            //set the username
            users_[current_user].setUsername(arr[0]);
            //set the number of likes
            users_[current_user].setNumPosts(split_count-1);
            //loop through the array and set the likes
            for(int i = 1; i < split_count; i++)
            {
                users_[current_user].setLikesAt(i-1,stoi(arr[i]));
            }
            //add one to the current user so it will go to the next user
            current_user++;
            //add one to the number of users
            num_users_++;
        }
    }
    //close the file
    file.close();
    //return the number of users stored
    return current_user;
}

/*
 * getLikes takes in a post author and a username, and will return the number of likes the user has given the author in the first post.
 * if either the post or the user name isn't found, it will return -3.
*/
int Buffchat::getLikes(string post_author, string username)
{
    int likes = 0;
    int userIndex = -1;
    int postIndex = -1;
    bool found = false;
    //check if num_users_stored and num_posts_stored is 0 or less 
    if(num_users_ <= 0 || num_posts_ <= 0)
    {
        return -2;
    }
    if(username == post_author){
        return 0;
    }
    //loop through users array to find the index of the user
    // if the user isn't found, the userIndex will not be changed (still -1)
    for(int i = 0; i < num_users_; i++)
    {
        if(users_[i].getUsername() == username)
        {
            userIndex = i;
        }
    }
    //loop through posts array to find the index of the post
    // if the post isn't found, the postIndex will not be changed (still -1)
    for(int i = 0; i < num_posts_; i++)
    {
        if(posts_[i].getPostAuthor() == post_author && !found)
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
    return users_[userIndex].getLikesAt(postIndex);
}
/*
 * findTagUser will take in a substring and will print the number of stored users that contain that substring in their username.
*/
void Buffchat::findTagUser(string username_tag)
{
    bool users_found = false;
    bool no_users_stored = false;
    string found_users[num_users_];
    string current_username;
    //if there are zero users, display that error.
    if(num_users_ == 0)
    {
        no_users_stored = true;
        cout << "No users are stored in the database" << endl;
    }
   //loop for each number of users
   for(int i = 0; i < num_users_;i++)
   {
        //get the current user's username
        current_username = users_[i].getUsername();
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
            for(int i = 0; i < num_users_;i++)
            {
                if(found_users[i] != "")
                {
                    cout << found_users[i] << endl;
                }
            }
        }
   }
}

/*
 * addPost will take in a post and will add it to the posts array.
 * if its able to add the post, it will return true.
 * if the array is already full, it will return false.
*/
bool Buffchat::addPost(string post_body, string post_author, string date)
{
    if(num_posts_ >= posts_size_)
    {
        return false;
    }
    //set the post information as long as there is space 
    posts_[num_posts_].setPostBody(post_body);
    posts_[num_posts_].setPostAuthor(post_author);
    posts_[num_posts_].setPostDate(date);
    //set all of the user likes to -1 at the current post index
    for(int i = 0; i < num_users_; i++)
    {
        users_[i].setLikesAt(num_posts_,-1);
    }
    num_posts_++;
    return true;
}

/*
 * printPopularPosts will print the most liked posts in a given year.
 * If it doesn't find any posts, it will output no posts are stored.
 * If there are no posts in that year, it will return no posts found in that year.
 * If there are less posts than request, it will display that.
*/
void Buffchat::printPopularPosts(int count, string year)
{
    int num_posts_year = 0;
    //create a 2d array for highest likes and their index in the posts array
    int highest_likes_index[num_posts_][2];
    Post posts_that_year[posts_size_];
    //make sure there are posts stored
    if(num_posts_ == 0)
    {
        cout << "No posts are stored" << endl;
        return;
    }
    else
    {
        //loop through the posts
        for(int i = 0; i < num_posts_; i++)
        {
            //make sure the post is in the given year
            if(posts_[i].getPostDate().substr(6,4) == year)
            {
                //add the post to the posts_that_year array
                posts_that_year[num_posts_year] = posts_[i];
                num_posts_year++;
            }
        }
        //if there are no posts in the given year, print out that there are no posts.
        if(num_posts_year == 0)
        {
            cout << "No posts stored for year " << year << endl;
        }  
        //check if there are fewer posts during the given year than requested
        else if(count > num_posts_year)
        {
            cout << "There are fewer than " << count << " posts for year " << year << ". Top " << num_posts_year << " posts for year " << year << endl;
            for(int i = 0; i < num_posts_year; i++)
            {
                    cout << posts_that_year[i].getPostLikes() << " likes: " << posts_that_year[i].getPostBody() << endl;
            }
        }
        else
        {
            //populate the 2d array
            for(int i = 0; i < num_posts_year; i++)
            {
                highest_likes_index[i][0] = posts_that_year[i].getPostLikes();
                highest_likes_index[i][1] = i;
            }
            //sort the 2d array
            //loop through the array
            for(int i = 0; i < num_posts_year; i++)
            {
                //loop through the array again to compare the values of every index against the current index (first loop)
                for(int j = 0; j < num_posts_year; j++)
                {
                    //if the current index is greater than the index we are comparing it to, swap the values
                    if(highest_likes_index[i][0] > highest_likes_index[j][0])
                    {
                        //int temp will hold the value of the current index so we can swap it
                        int temp = highest_likes_index[i][0];
                        // swap the values
                        highest_likes_index[i][0] = highest_likes_index[j][0];
                        //set the value of the index we are comparing to the value of the current index (temp)
                        highest_likes_index[j][0] = temp;
                        //do the same for the index of the post in the posts array (the index value of the 2d array)
                        temp = highest_likes_index[i][1];
                        // swap the values
                        highest_likes_index[i][1] = highest_likes_index[j][1];
                        //set the value of the index we are comparing to the value of the current index
                        highest_likes_index[j][1] = temp;
                    }
                }
            }
            //now sort the 2d array by index, only keeping the number of posts requested (count)
            for(int i = 0; i < count; i++)
            {
                //loop through the array again to compare the values of every index against the current index (first loop)
                for(int j = 0; j < count; j++)
                {
                    //if the current index is greater than the index we are comparing it to, swap the values
                    if(highest_likes_index[i][1] < highest_likes_index[j][1])
                    {
                        int temp = highest_likes_index[i][0];
                        highest_likes_index[i][0] = highest_likes_index[j][0];
                        highest_likes_index[j][0] = temp;
                        temp = highest_likes_index[i][1];
                        highest_likes_index[i][1] = highest_likes_index[j][1];
                        highest_likes_index[j][1] = temp;
                    }
                }
            }
            //print out the 2d array
            cout << "Top " << count << " posts for year " << year << endl;
            for(int i = 0; i < count; i++)
            {
                cout << posts_that_year[highest_likes_index[i][1]].getPostLikes() << " likes: " << posts_that_year[highest_likes_index[i][1]].getPostBody() << endl;
            }
        }
    }
}


/*
 * findLeastActiveUser will return the least active user in the database (the user who has viewed the least amount of posts)
 * It will return the least active user if found
 * If not found, it will return an empty user object
 */
User Buffchat::findLeastActiveUser()
{ 
    User least_active_user;
    int least_score = 0;
    int least_score_temp = 0;
    //loop through the users
    for(int i = 0; i < num_users_; i++)
    {
        //reset the least score temp
        least_score_temp = 0;
        //get the number of likes for the user
        int likes = users_[i].getNumPosts();
        for(int j = 0; j < likes; j++)
        {
            //if the user has not viewed a post (-1), add 1 to the leasts_posts
            if(users_[i].getLikesAt(j) == -1)
            {
                least_score_temp++;
            }
        }
        //check the leasts_posts against the current leasts_posts
        if(least_score_temp > least_score)
        {
            least_score = least_score_temp;
            least_active_user = users_[i];
        }
    }
    //return the least active user
    return least_active_user;
}

/*
 * countUniqueLikes will count the number of times a post has been liked by all of users.
 * While the user can like a post up to 10 times, it will only be counted once.
 * If there are no users or no posts, it will return -2
 * If no users have viewed the post, it will return -1
 * If atleast user has viewed the post, but not liked it, it will return 0
*/
int Buffchat::countUniqueLikes(string post_author)
{
    //declare vars
    int unique_likes = 0;
    bool post_viewed = false;
    //make sure there are more than zero posts or users stored
    if(num_posts_ == 0 || num_users_ == 0)
    {
        return -2;
    }
    //loop through the number of posts
    for(int i = 0; i < num_posts_; i++)
    {
        //check to see if its by the post_author
        if(posts_[i].getPostAuthor() == post_author)
        {
            //loop through the users to count the likes on this post
            for(int j = 0; j < num_users_; j++)
            {
                //check to make sure the post has been viewed at least once
                if(users_[j].getLikesAt(i) == 0)
                {
                    post_viewed = true;
                }
                //as long as likes is greater than zero, it counts as a like
                else if(users_[j].getLikesAt(i) > 0)
                {
                    post_viewed = true;
                    unique_likes++;
                }
            } 
        }
    }
    //if the posts has no views, return -1;
    if(!post_viewed)
    {
        return -1;
    }
    return unique_likes;
}
