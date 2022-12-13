//Player.h

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 3

#pragma once
#include <iostream>
using namespace std;

/*
 * Player.h contains the declaration of the Player class.
*/

class Player
{
    public:
        Player();
        Player(string name, bool isLeader);
        
        //get and set name
        void setName(string newName);
        string getName();

        //get and set fullness
        void setFullness(int newFullness);
        int changeFullness(int change);
        int getFullness();

        //get and set dead
        void setDead();
        bool isPlayerDead();
        void setAlive();  

        //check to see how many players are still alive
        int numPlayersAlive(Player players[5]);
    private:
        string name;
        int fullness;
        bool isDead;
        bool isLeader;
};