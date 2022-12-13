//Monster.h

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 3

#pragma once
#include <iostream>
using namespace std;  

/* 
 * Monster.h contains the declaration of the Monster class.
*/

class Monster
{
    public:
        //default constructor
        Monster();
        //constructor with parameters
        Monster(int level, string name);
        //fills the vector with monsters from the file
        bool fillArray(vector<Monster> &monsters);
        //gets the monsters by a certain level
        vector<Monster> getMonstersByLevel(vector<Monster> &monsters, int level);
        //removes monsters from the vector
        bool removeMonsterByName(vector<Monster> &monsters, string name);
        
        //getters
        int getLevel();
        string getName();

        //setters
        void setName(string newName);

    private:
        //monsters name
        string name;
        //monsters level
        int level;
};