// Aquarium.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 9 - All Functions

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Aquarium.h"
using namespace std;

// This file contains the aquarium class implementation

// Basic constructor, sets aquarist_name to name, gallons_used to 0
Aquarium::Aquarium(string name)
{
    aquarist_name = name;
    gallons_used = 0;
}

// Returns aquarist_name
string Aquarium::getAquaristName()
{
    return aquarist_name;
}

// Returns gallons_used
int Aquarium::getGallonsUsed()
{
    return gallons_used;
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

// loads fish from file_name into available_fish, returns true if successful, false otherwise
bool Aquarium::loadFish(string file_name)
{
    ifstream file;
    file.open(file_name);
    //if the file is not open (for whatever reason), return false
    if(file.fail())
    {
        return false;
    }
    //if the file is open, read the file
    //create a string to hold the line
    string line;
    //loop through the file using getline, replacing the line each time
    while(getline(file,line))
    {
        //skip empty lines
        if(line.length() > 0)
        {
            //create an array to hold the split line
            string arr[2];
            //split the line by the comma
            int check = split(line,',',arr,2);
            //if the split was successful, create a fish struct and add it to the vector
            if(check != -1)
            {
                //create a fish struct
                Fish new_fish;
                //set the name to the first part of the split
                new_fish.name = arr[0];
                //set the gallons required to the second part of the split
                new_fish.gallons_required = stoi(arr[1]);
                //add the fish to the vector
                available_fish.push_back(new_fish);
            }
        }
    }
    file.close();
    return true;
}

// prints the contents of the available_fish vector to the console, shows the user what fish they can add to their aquarium, and how many gallons they will use
void Aquarium::displayAvailableFish()
{
    //check if there are any fish in the vector
    if(available_fish.size() == 0)
    {
        cout << "There are no fish available." << endl;
    }
    //print out the available fish that we can add to the aquarium
    else
    {
        cout << "Fish available to add to aquarium:" << endl;
        //loop through the vector and print out the fish
        for(int i = 0; i < available_fish.size(); i++)
        {
            cout << available_fish[i].name << " - " << available_fish[i].gallons_required << endl;
        }
    }
}

//addFish moves a fish from the available_fish vector to the aquarium_fish vector
//if the fish is not found in the available_fish vector, returns false
//the input fish_name is not case sensitive, it will be converted to lowercase
//if the fish is found, but there is not enough room in the aquarium, returns false
//if the fish is found and there is enough room, returns true
int Aquarium::addFish(string fish_name)
{
    //check if there are any fish in the vector
    if(available_fish.size() == 0)
    {
        return -1;
    }
    //change fish_name to lowercase
    for(int i = 0; i < fish_name.length(); i++)
    {
        fish_name[i] = tolower(fish_name[i]);
    }
    //change input to lowercase
    //create a temp string to hold the lowercase name, so we don't have to change the original
    vector<string> fish_names;
    for(int i = 0; i < available_fish.size(); i++)
    {
        string temp = available_fish[i].name;
        for(int j = 0; j < temp.length(); j++)
        {
            temp[j] = tolower(temp[j]);
        }
        fish_names.push_back(temp);
    }
    //loop through the vector and print out the fish
    for(int i = 0; i < available_fish.size(); i++)
    {
        //check if the fish name is the same as the fish we are looking for
        if(fish_names[i] == fish_name)
        {
            //check if the fish will fit in the aquarium
            if(available_fish[i].gallons_required + gallons_used <= tank_size_gallons)
            {
                //add the fish to the selected fish vector
                selected_fish.push_back(available_fish[i]);
                //update the gallons used
                gallons_used += available_fish[i].gallons_required;
                //remove the fish from the available fish vector
                available_fish.erase(available_fish.begin() + i);
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    return -1;
}

//remove fish moves a fish from the aquarium_fish vector to the available_fish vector
//if the fish is not found in the aquarium_fish vector, returns false
//it will also free up the gallons used by the fish/
//input fish_name is not case sensitive, it will be converted to lowercase
bool Aquarium::removeFish(string fish_name)
{
    //change fish_name to lowercase
    for(int i = 0; i < fish_name.length(); i++)
    {
        fish_name[i] = tolower(fish_name[i]);
    }
    //create a temp string to hold the lowercase name, so we don't have to change the original
    vector<string> fish_names;
    for(int i = 0; i < selected_fish.size(); i++)
    {
        string temp = selected_fish[i].name;
        for(int j = 0; j < temp.length(); j++)
        {
            temp[j] = tolower(temp[j]);
        }
        fish_names.push_back(temp);
    }
    //loop through the vector and print out the fish
    for(int i = 0; i < selected_fish.size(); i++)
    {
        //check if the fish name is the same as the fish we are looking for (case insensitive)
        if(fish_names[i] == fish_name)
        {
            //add the fish to the available fish vector
            available_fish.push_back(selected_fish[i]);
            //update the gallons used
            gallons_used -= selected_fish[i].gallons_required;
            //remove the fish from the selected fish vector
            selected_fish.erase(selected_fish.begin() + i);
            return true;
        }
    }
    return false;
}


//writes the contents of the aquarium_fish vector to the file_name, returns true if successful, false otherwise
//if the file already exists, it will be overwritten
//if the file cannot be opened/created, returns false
bool Aquarium::writeAquariumContents(string file_location)
{
    //open the file
    ofstream file;
    file.open(file_location);
    //check if the file opened successfully
    if(file.fail())
    {
        return false;
    }
    //create a vector to hold the new files contents (1 line per fish)
    vector<string> new_file_contents;
    //check if there are any fish in the aquarium
    if(selected_fish.size() == 0)
    {
        //add the second line to the vector
        new_file_contents.push_back("There are no fish in " + aquarist_name + "'s Aquarium.");
    }
    else
    {
        //add the first line to the vector
        new_file_contents.push_back(aquarist_name + "'s Aquarium (" + to_string(gallons_used) + " of " + to_string(tank_size_gallons) + " gallons of water used):");
        //loop through the vector and add the fish to the vector
        for(int i = 0; i < selected_fish.size(); i++)
        {
            new_file_contents.push_back(selected_fish[i].name + " - " + to_string(selected_fish[i].gallons_required));
        }
    }
    //loop through the vector and write the contents to the file
    for(int i = 0; i < new_file_contents.size(); i++)
    {
        file << new_file_contents[i] << endl;
    }
    return true;
}