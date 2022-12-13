//Merchant.h

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 3

#pragma once
#include "Map.h"
#include "Player.h"
#include <iostream>
using namespace std;

/*
 * Merchant.h contains the declaration of the Merchant class.
 */

class Merchant
{
    public:
        //default constructor
        Merchant();

        //handle the first visit to the merchant
        void firstVisit();
        //increase the merchant multiplier
        void increasePriceByRoomsCleared(int multiplier);
        //prints out the inventory menu
        void displayInventoryMenu();
        //true/false can afford (with merchant multiplier applied in the fuction)
        bool canAfford(double cost);
        //handle NPC visits
        void handleInteraction(Player players[5]);


        //rps door puzzle function
        bool handleRpsDoorPuzzle(Player players[5]);

        //riddle functions 
        bool fillRiddles(vector<string> &riddleQuestions, vector<string> &riddleAnswers);
        bool handleRiddle(vector<string> &riddleQuestions, vector<string> &riddleAnswers);
        //gold functions
        int getGold();
        void setGold(int newGold);
        int changeGold(int change);


        //functions for weapons
        void getWeapons(int weapons[5]);
        int getWeaponsByIndex(int index);
        void changeWeaponsByIndex(int index, int change);
        int getNumWeapons();
        string getWeaponNameByIndex(int index);

        //functions for armor
        int getArmor();
        void changeArmor(int change);


        //functions for ingredients
        int getIngredients();
        void changeIngredients(int change);

        //functions for treasure
        int getTreasureByIndex(int index);
        void changeTreasureByIndex(int index, int change);
        int getTotalTreasure();

        //functions for cookware
        int getCookwareByIndex(int index);
        void getCookware(int cookware[3]);
        void changeCookware(int index, int change);
        void printCookware();
        string getCookwareNameByIndex(int index);

        //functions for keys
        int getKeys();
        void changeKeys(int change);

    private:
        double gold;
        int totalWeapons;
        int keys;
        int ingredients;
        int cookware[3];
        double merchantMultiplier;
        int weapons[5];
        int armor;
        int treasures[5];
};
