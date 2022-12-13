//monster.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 3

#include "Merchant.h"
#include "Map.h"
#include "Menu.h"
#include "Probability.h"
#include "Monster.h"
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


/*
 * Monster.cpp contains the implementation of the Monster class.
 * The Monster class handles the loading-in of monsters, and the basic getters and setters for the monsters.
 * It also contains helper fuctions, such as removing a monster by name, and removing monsters below a certain level.
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

//default constructor
Monster::Monster()
{
    //default constructor
    level = 1;
    name = "default";
}

//parameterized constructor
Monster::Monster(int setLevel,string setName)
{
    level = setLevel;
    name = setName;
}

//returns the level of the monster
int Monster::getLevel()
{
    return level;
}

//returns the name of the monster
string Monster::getName()
{
    return name;
}

/*
 * fillArray is a function that takes in an empty vector of monsters and populates the vector with monsters from a file.
 * If the file is not found, it will return false.
 * If the vector is successfully populated, it will return true.
*/
bool Monster::fillArray(vector<Monster> &monsters)
{
    ifstream file;
    file.open("./data/monsters.txt");
    if(file.fail())
    {
        cout << "file failed to open" << endl;
        return false;
    }
    else
    {
        string line;
        while(getline(file,line))
        {
            Monster monster;
            string arr[2];
            int check = split(line,',',arr,2);
            if(check == 2)
            {
                monster.name = arr[0];
                monster.level = stoi(arr[1]);
                monsters.push_back(monster);
            }
            else 
            {
                return false;
            }
        }
        file.close();
        return true;
    }
}

/*
 * getMonstersByLevel returns a vector of monsters that contains all monsters that are the level passed.
 * this function is used when battling a random monster, to get all the monsters by that level.
*/
vector<Monster> Monster::getMonstersByLevel(vector<Monster> &monsters, int level)
{
    vector<Monster> monstersByLevel;
    for(int i = 0; i < monsters.size(); i++)
    {
        if(monsters[i].level == level)
        {
            monstersByLevel.push_back(monsters[i]);
        }
    }
    return monstersByLevel;
}

/*
 * removeMonsterByName is a function that takes in the vector of monsters, and a string name.
 * if it finds the monster, it will remove it from the vector, and return true.
 * if it does not find the monster, it will return false.
*/
bool Monster::removeMonsterByName(vector<Monster> &monsters, string name)
{
    for(int i = 0; i < monsters.size(); i++)
    {
        if(monsters[i].name == name)
        {
            monsters.erase(monsters.begin() + i);
            return true;
        }
    }
    return false;
}

//sets the monster's name
void Monster::setName(string setName)
{
    name = setName;
}