//Menu.h

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 3

#pragma once
#include <iostream>
#include "Merchant.h"
#include "Map.h"
#include "Player.h"
#include "Monster.h"
#include "Probability.h"

/*
* Menu.h contains the declaration of the Menu class.
*/

using namespace std;

class Menu
{
    public:
        //default constructor
        Menu();
        //handles the action menu
        int displayActionMenu(Map &map);
        //displays the first part of the status update
        void displayStatusUpdatePart1(int sorcererLevel, int keys, int roomsCleared);
        //displays the second part of the status update
        void displayStatusUpdatePart2(Map map, Player players[5]);
        //handles setting up the users
        void setupUsers(Player players[5]);
        //handles printing the final status update
        void printEndingOfGame(Player players[5],int roomsCleared, Merchant &merchant, int spacesExplored, int turns, int monstersDefeated, bool won);
};
