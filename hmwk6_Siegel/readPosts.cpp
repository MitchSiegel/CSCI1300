//readPosts.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 6 - Problem # 3

#include <iostream>
#include <string>
#include <fstream>
#include <cassert>

using namespace std;

/*
 * The file will read the number of posts in a given file, and will output the number of valid posts
 * If an invalid file is inputted, it outputs -1.
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
 * Read posts will read a text file, then return the number of valid posts.
 * If an invalid file is inputted, it returns -1 and stops the function.
 * It is a valid post if the it contains all three aspects: the text body, the username, and the like count.
 */
int readPosts(string filename)
{
    //declare variables
    string line;
    ifstream fin;
    int post_count = 0;
    //open the file
    fin.open(filename);
    //check if the file is open / exists
    if(fin.fail())
    {
        return -1;
    }
    else
    {
        //read the entire file
        while (!fin.eof())
        {
            //get the line first to make sure it's not empty
            getline(fin, line);
            //checks and makes sure the line is not empty
            if(line.length() > 0){
                //split the line into an array
                string arr[3];
                split(line,',',arr,3);
                //make sure post has all three parts
                if(arr[0].length() > 0 && arr[1].length() > 0 && arr[2].length() > 0)
                {
                    //increment the post count
                    post_count++;
                }
            }

        }
        //close the file
        fin.close();
        //return number of posts
        return post_count;
    }
}

/* 
 * printResults is used for testing and will print the number of posts if the file can be opened.
*/
void printResults(int num_posts)
{
    if (num_posts == -1)
    {
        cout << "Could not open file." << endl;
    }
    else
    {
        cout << "Number of posts: " << num_posts << "." << endl;
    }
}

int main()
{
    /* test 1
     * Expected output: 
        Number of posts: 7.
    */
    cout << "test 1:" << endl;
    string filename = "./data/posts.txt";
    int num_posts = readPosts(filename);
    printResults(num_posts);
    cout << "-----------" << endl;

    /* test 2
     * Expected output: 
        Number of posts: 5.
    */
    cout << "test 2:" << endl;
    filename = "./data/posts_two.txt";
    num_posts = readPosts(filename);
    printResults(num_posts);
    cout << "-----------" << endl;

    /* test 3
     * Expected output: 
        Number of posts: 0.
    */
    cout << "test 3:" << endl;
    filename = "./data/empty_file.txt";
    num_posts = readPosts(filename);
    printResults(num_posts);
    cout << "-----------" << endl;

     /* test 4
     * Expected output: 
        Could not open file.
    */
    cout << "test 4:" << endl;
    filename = "./data/does_not_exist.txt";
    num_posts = readPosts(filename);
    printResults(num_posts);
    cout << "-----------" << endl;
}