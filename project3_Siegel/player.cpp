//player.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 3

#include "Player.h"
#include "Map.h"
#include "Menu.h"
#include <iostream>

using namespace std;

/*
 * player.cpp contains the implementation of the Player class.
*/

//default constructor
Player::Player()
{
    name = "";
    fullness = 50;
    isLeader = false;
    isDead = false;
}

//constructor with parameters
Player::Player(string newName, bool newIsLeader)
{
    name = newName;
    fullness = 50;
    isLeader = newIsLeader;
    isDead = false;
}

//set the players name
void Player::setName(string newName)
{
    name = newName;
}

//get the players name
string Player::getName()
{
    return name;
}

//set the players fullness
void Player::setFullness(int newFullness)
{
    if(newFullness > 100)
    {
        fullness = 100;
    }
    else if(newFullness < 0)
    {
        fullness = 0;
    }
    else
    {
        fullness = newFullness;
    }
}

//get the players fullness
int Player::getFullness()
{
    return fullness;
}

//change the players fullness (positive or negative)
int Player::changeFullness(int change)
{
    //make sure its not negative
    if(fullness + change < 0)
    {
        fullness = 0;
    }
    else
    {
        fullness += change;
    }
    return fullness;
}

//sets the player as dead, and sets their fullness to 0
void Player::setDead()
{
    isDead = true;
    fullness = 0;
}

//returns true if the player is dead
bool Player::isPlayerDead()
{
    return isDead;
}

//returns the number of players still alive.
int Player::numPlayersAlive(Player players[5])
{
    //this will always start at 1 because the leader is always alive
    int numAlive = 1;
    for(int i = 1; i < 5; i++)
    {
        if(players[i].isPlayerDead() == false)
        {
            numAlive++;
        }
    }
    return numAlive;
}

//sets the player as alive (only used for the resurrection event - so we can set the fullness here too)
void Player::setAlive()
{
    isDead = false;
    fullness = 20;
}