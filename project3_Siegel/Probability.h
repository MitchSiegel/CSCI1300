//Probably.h

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 3

#pragma once
#include <iostream>
#include <vector>
#include "Map.h"
#include "Monster.h"
#include "Merchant.h"
#include "Player.h"
using namespace std;

/*
 * Probability.h contains the declaration of the Probability class.
*/

class Probability
{
    public:
        //default constructor
        Probability();
        //
        void pressToContinue();
        //returns a random number between min and max
        int randomNumberBetween(int min, int max);
        //handles placing the rooms and NPCs on the map
        void generateRandomPlacement(Map &map);
        //handles investigation of the map
        bool handleInvestigation(Map &map, Player players[5], int roomsCleared, Merchant &merchant);
        //picks a random monster from the vector by monster level
        Monster pickRandomMonster(vector<Monster> &monsters, int roomsCleared);
        //handles the fighting equations
        bool fightMonster(Player players[5], vector<Monster> &monsters,int roomsCleared, Merchant &merchant);
        //handles the cooking equations
        void handleCooking(Player players[5], Merchant &merchant);
        //handles the chances of stuff after moving
        bool handleMoving(Player players[5]);
        //handles the chances of stuff after all actions but moving 
        void handleMisfortune(Player players[5],bool openedDoorWithKey,Merchant &merchant);
        //handling chance of 60% misfortune after opening a door and defeating the monster
        void handleMisfortuneAfterMonster(Player players[5],bool defeatedMonster,Merchant &merchant);
        //removes a random weapon from the merchant
        bool removeRandomWeapon(Player players[5],Merchant &merchant);
        //handles the sorcerer battle
        bool handleSorcererBattle(Player players[5],Merchant &merchant, int weapons[],int totalWeapons, int uniqueWeapons);
    private:
        bool pressToContinueVar;
};