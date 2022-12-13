//merchant.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 3

#include <iostream>
#include <vector>
#include <fstream>
#include "Merchant.h"
#include "Player.h"
#include "Map.h"
#include "Menu.h"

using namespace std;

/*
 * merchant.cpp is the implementation file for the Merchant class
*/

/*
 * the split function takes in a string, the seperator, and then the arr, and the arr_size.
 * It will split the function into an array, splitting it by the seperator.
 * If there are more splits than the array size, it will fill it with as many as possible.
*/
int splitTwo(string input_string,char seperator, string arr[],int arr_size)
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


//default constructor - set all values to 0 (or 1)
Merchant::Merchant()
{
    gold = 100;
    totalWeapons = 0;
    keys = 0;
    ingredients = 0;
    //set cookware to zero
    for(int i = 0; i < 3; i++)
    {
        cookware[i] = 0;
    }
    //set weapons to zero
    for(int i = 0; i < 5; i++)
    {
        weapons[i] = 0;
        treasures[i] = 0;
    }
    armor = 0;
    merchantMultiplier = 1;
}

//handles the first visit to the merchant, and tells them the basic rules of the purchasing system
void Merchant::firstVisit()
{
    cout << "Between the 5 of you, you have 100 gold pieces." << endl;
    cout << "You will need to spend the some of your money on the following items:" << endl;
    cout << endl;
    cout << "- INGREDIENTS. To make food, you have to cook raw ingredients." << endl;
    cout << "- COOKWARE. If you want to cook, you have to have cookware first." << endl;
    cout << "- WEAPONS. You'll want at least one weapon per party member to fend off monsters." << endl;
    cout << "- ARMOR. Armor increases the chances of surviving a monster attack." << endl;
    cout << endl;
    cout << "You can spend all of your money here before you start your journey, or you can save some to spend on merchants along the way. But beware, some of the merchants in this dungeon are shady characters, and they won't always give you a fair price..." << endl;
    cout << endl;
    cout << endl;
}

//handles increasing the merchant multiplier by the number of rooms cleared
void Merchant::increasePriceByRoomsCleared(int roomsCleared)
{
    //reset the multiplier
    merchantMultiplier = 1;
    //increase the multiplier by 25% for each room cleared
    for(int i = 0; i < roomsCleared; i++)
    {
        merchantMultiplier += .25;
    }
}

//prints out the inventory menu for the player (during status updates, and when the player visits the merchant)
void Merchant::displayInventoryMenu()
{
    cout << "+-------------+" << endl;
    cout << "|  INVENTORY  |" << endl;
    cout << "+-------------+" << endl;
    cout << "| Gold        | " << gold << endl;
    cout << "| Ingredients | " << ingredients << endl;
    cout << "| Cookware    | " <<  "P: " << cookware[0] << " | F: " << cookware[1] << " | C: " << cookware[2] << endl;
    cout << "| Weapons     | " << "C: " << weapons[0] << " | S: " << weapons[1] << " | R: " << weapons[2] << " | B: " << weapons[3] << " | L: " << weapons[4] << endl;
    cout << "| Armor       | " << armor << endl;
    cout << "| Treasures   | " << "R: " << treasures[0] << " | N: " << treasures[1] << " | B: " << treasures[2] << " | C: " << treasures[3] << " | G: " << treasures[4] << endl;
    cout << "+-------------+" << endl;
}

//returns true if the player can afford the item, false if they can't. This function takes the merchant multiplier into account
bool Merchant::canAfford(double cost)
{
    if(gold >= cost * merchantMultiplier && cost * merchantMultiplier > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
 * handleInteraction takes in the players array.
 * It handles the purchasing of items, and the selling of items.
 * It will display a menu with the following options:
 * 1. Buy Ingredients
 * 2. Buy Cookware
 * 3. Buy Weapons
 * 4. Buy Armor
 * 5. Sell Treasure
*/
void Merchant::handleInteraction(Player players[5])
{
    cout << "If you're looking to get supplies, you've come to the right place." << endl;
    cout << "I would be happy to part with some of my wares...for the proper price!" << endl;
    bool userQuit = false;
    while(!userQuit)
    {
        cout << endl;
        cout << endl;
        displayInventoryMenu();
        cout << endl;
        cout << "Choose one of the following:" << endl;
        cout << "1. Ingredients: To make food, you have to cook raw ingredients." << endl;
        cout << "2. Cookware: You will need something to cook those ingredients." << endl;
        cout << "3. Weapons: It's dangerous to go alone, take this!" << endl;
        cout << "4. Armor: If you want to survive monster attacks, you will need some armor." << endl;
        cout << "5. Sell treasures: If you find anything shiny, I would be happy to take it off your hands." << endl;
        cout << "6. Leave: Make sure you get everything you need, I'm leaving after this sale!" << endl;
        cout << endl;
        int userChoice;
        string userChoiceString;
        cout << endl;
        cin >> userChoiceString;
        cout << endl;

        if(isdigit(userChoiceString[0])){
            userChoice = stoi(userChoiceString, 0);
        }else{
            userChoice = 100;
        }
        switch(userChoice)
        {
            //handle purchasing ingredients
            //this works perfectly
            case 1:
            {
                cout << "Good choice! Ingredients are very important to success." << endl;
                cout << "I recommend buying at least 10kg of ingredients per person." << endl;
                cout << "I'm currently charing " << 1 * merchantMultiplier << " gold per kg." << endl;
                cout << "How many kg would you like to buy? (must be multiples of 5)" << endl;
                cout << endl;
                int userAmount;
                string userAmountString;
                bool quitTransaction = false;
                cin >> userAmountString;
                if(isdigit(userAmountString[0])){
                    userAmount = stoi(userAmountString, 0);
                }else{
                    userAmount = -1;
                }
                //loop until the user enters a valid amount (multiples of 5)
                while(userAmount % 5 != 0 && userAmount > 0)
                {
                    cout << "Please enter a multiple of 5." << endl;
                    cout << endl;
                    cin >> userAmountString;
                    if(isdigit(userAmountString[0])){
                        userAmount = stoi(userAmountString, 0);
                    }else{
                        userAmount = -1;
                    }
                }
                //loop until the user enters a valid amount of ingredients that they can afford
                while(!canAfford(userAmount) || userAmount % 5 != 0)
                {
                    cout << "You don't have enough gold for that. Please enter a new value. (0 to cancel)" << endl;
                    cout << endl;
                    //ask user for new amount
                    cin >> userAmountString;
                    if(isdigit(userAmountString[0]))
                    {
                        userAmount = stoi(userAmountString, 0);
                    }
                    else{
                        userAmount = -1;
                    }
                }
                if(userAmount == 0)
                {
                    cout << endl;
                    cout << "Transaction cancelled." << endl;
                    cout << endl;
                    break;
                }
                //if user didn't quit transaction, make them confirm their purchase, and then process it
                if(!quitTransaction)
                {
                    cout << "Are you sure you want to buy " << userAmount << " kg of ingredients for " << userAmount * merchantMultiplier << " gold? (y/n)" << endl;
                    cout << endl;
                    string userConfirm;
                    cin >> userConfirm;
                    if(userConfirm[0] == 'y')
                    {
                        ingredients += userAmount;
                        gold -= userAmount * merchantMultiplier;
                        cout << "Thank you for your purchase! What else can I help you?" << endl;
                    }
                    else
                    {
                        cout << "Transaction Cancelled." << endl;
                    }
                }
                break;
            }
            //handle purchasing cookware
            //this is now working
            case 2:
            {
                cout << "I have a several types of cookware, which one would you like?" << endl;
                cout << "Each type has a different probability of breaking when used, marked with (XX%)." << endl;
                cout << endl;
                cout << "Choose one of the following:" << endl;
                cout << "1. (25%) Ceramic Pot [" <<  2 * merchantMultiplier << " Gold]" << endl;
                cout << "2. (10%) Frying Pan  [" << 10 * merchantMultiplier << " Gold]" << endl;
                cout << "3. (02%) Cauldron    [" << 20 * merchantMultiplier << " Gold]" << endl;
                cout << "4. Cancel" << endl;
                cout << endl;
                int userChoice;
                string userChoiceString;
                bool quitTransaction = false;
                cin >> userChoiceString; 
                if(isdigit(userChoiceString[0]))
                {
                    userChoice = stoi(userChoiceString, 0);
                }else
                {
                    userChoice = -1;
                }
                //loop until user enters a valid choice or quits the transaction
                while(userChoice < 1 || userChoice > 4)
                {
                    cout << "Please enter a valid choice. (4 to cancel)" << endl;
                    cout << endl;
                    cin >> userChoiceString;
                    if(isdigit(userChoiceString[0]))
                    {
                        userChoice = stoi(userChoiceString, 0);
                    }else
                    {
                        userChoice = -1;
                    }
                }
                if(userChoice == 4)
                {
                    break;
                }
                cout << endl;
                cout << "How many would you like to buy? (0 to cancel)" << endl;
                cout << endl;
                int userAmount;
                string userAmountString;
                cin >> userAmountString;
                if(isdigit(userAmountString[0]))
                {
                    userAmount = stoi(userAmountString, 0);
                }
                else
                {
                    userAmount = -1;
                }
                cout << endl;
                while(userAmount < 0)
                {
                    cout << "Please enter a valid amount. (0 to cancel)" << endl;
                    cout << endl;
                    cin >> userAmountString;
                    if(isdigit(userAmountString[0]))
                    {
                        userAmount = stoi(userAmountString, 0);
                    }else
                    {
                        userAmount = -1;
                    }
                }
                if(userAmount == 0)
                {
                    cout << endl;
                    cout << "Transaction cancelled." << endl;
                    cout << endl;
                    quitTransaction = true;
                    break;
                }
                int cost = 0;
                int baseCost = 0;
                //calculate cost and set the name of the cookware
                string cookwareName;
                switch(userChoice)
                {
                    case 1:
                    {
                        cost = 2 * userAmount;
                        baseCost = 2;
                        cookwareName = "Ceramic Pot";
                        break;
                    }
                    case 2:
                    {
                        cost = 10 * userAmount;
                        baseCost = 10;
                        cookwareName = "Frying Pan";
                        break;
                    }
                    case 3:
                    {
                        cost = 20 * userAmount;
                        baseCost = 20;
                        cookwareName = "Cauldron";
                        break;
                    }
                }
                //make sure user can afford the purchase
                while(!canAfford(cost))
                {
                    cout << "You don't have enough gold to purchase " << userAmount << " " << cookwareName << "s." << endl; 

                    cout << "Please enter a new value. (0 to cancel)" << endl;
                    cout << endl;
                    if(userAmount == 0)
                    {
                        cout << endl;
                        cout << "Transaction cancelled." << endl;
                        cout << endl;
                        quitTransaction = true;
                        break;
                    }
                    //ask user for new amount
                    cin >> userAmountString;
                    if(isdigit(userAmountString[0]))
                    {
                        userAmount = stoi(userAmountString, 0);
                    }
                    else
                    {
                        userAmount = -1;
                    }
                    //calculate new cost
                    cost = baseCost * userAmount;
                }
                if(userAmount == 0)
                {
                    quitTransaction = true;
                    break;
                }
                //if user didn't quit transaction, make them confirm their purchase, and then process it
                if(!quitTransaction)
                {
                    cout << "Are you sure you want to buy " << userAmount << " " << cookwareName << "s for " << cost * merchantMultiplier << " gold? (y/n)" << endl;
                    cout << endl;
                    string userConfirm;
                    cin >> userConfirm;
                    if(userConfirm[0] == 'y')
                    {
                        cookware[userChoice - 1] += userAmount;
                        gold -= cost * merchantMultiplier;
                        cout << "Thank you for your purchase! What else can I help you?" << endl;
                    }
                    else
                    {
                        cout << "Transaction Cancelled." << endl;
                    }
                }
                break;
            }
            //handle purchasing weapons
            //this is now working
            case 3:
            {
                //purchase weapons
                cout << "I have a several types of weapons, please take a look." << endl;
                cout << "Please note that you can only carry as many weapons as you have party members. You can't sell weapons, so make your choices wisely." << endl;
                cout << "Note that some of them provide you a special bonus in combat, marked by a (+X)." << endl;
                cout << endl;
                cout << "Choose one of the following:" << endl;
                cout << "1. Stone Club [" << 2 * merchantMultiplier << " Gold]" << endl;
                cout << "2. Iron Spear [" << 2 * merchantMultiplier << " Gold]" << endl;
                cout << "3. (+1) Mythril Rapier [" << 5 * merchantMultiplier << " Gold]" << endl;
                cout << "4. (+2) Flaming Battle-Axe [" << 15 * merchantMultiplier << " Gold]" << endl;
                cout << "5. (+3) Vorpal Longsword [" << 50 * merchantMultiplier << " Gold]" << endl;
                cout << "6. Cancel" << endl;
                cout << endl;
                int maxWeapons = 5;
                //calculate the number of max weapons
                for(int i = 0; i < 5; i++)
                {
                    //subtract one if the player is alive
                    if(players[i].isPlayerDead())
                    {
                        maxWeapons--;
                    }
                    //add number of weapons if they have them
                    if(weapons[i] != 0)
                    {
                        maxWeapons = maxWeapons - weapons[i];
                    }
                }
                cout << "You can purchase " << maxWeapons << " more weapon(s)." << endl;
                int userChoice;
                string userChoiceString;
                cin >> userChoiceString;
                if(isdigit(userChoiceString[0]))
                {
                    userChoice = stoi(userChoiceString, 0);
                }
                else
                {
                    userChoice = -1;
                }
                bool quitTransaction = false;
                //loop until user enters a valid choice or quits the transaction
                if(userChoice == 6)
                {
                    cout << endl;
                    cout << "Transaction cancelled." << endl;
                    cout << endl;
                    break;
                }
                while(userChoice < 1 || userChoice > 6)
                {
                    cout << "Please enter a valid choice. (6 to cancel)" << endl;
                    if(userChoice == 6)
                    {
                        cout << endl;
                        cout << "Transaction cancelled." << endl;
                        cout << endl;
                        quitTransaction = true;
                        //exit the while loop
                        break;
                    }
                    cout << endl;
                    cin >> userChoiceString;
                    if(isdigit(userChoiceString[0]))
                    {
                        userChoice = stoi(userChoiceString, 0);
                    }
                    else
                    {
                        userChoice = -1;
                    }
                }
                //exit the purchase weapons transaction if user chose to cancel
                if(quitTransaction)
                {
                    break;
                }
                cout << "How many would you like to buy? (0 to cancel)" << endl;
                cout << endl;
                int userAmount;
                string userAmountString;
                cin >> userAmountString;
                if(isdigit(userAmountString[0]))
                {
                    userAmount = stoi(userAmountString, 0);
                }
                else
                {
                    userAmount = -1;
                }
                cout << endl;
                //loop until user enters a valid amount or quits the transaction
                while(userAmount <= 0)
                {
                    cout << "Please enter a valid amount. (0 to cancel)" << endl;
                    if(userAmount == 0)
                    {
                        cout << endl;
                        cout << "Transaction cancelled." << endl;
                        cout << endl;
                        quitTransaction = true;
                        //exit the while loop
                        break;
                    }
                    cout << endl;
                    cin >> userAmountString;
                    if(isdigit(userAmountString[0]))
                    {
                        userAmount = stoi(userAmountString, 0);
                    }
                    else
                    {
                        userAmount = -1;
                    }
                }
                //exit the purchase weapons transaction if user chose to cancel
                if(quitTransaction)
                {
                    break;
                }
                int cost = 0;
                int baseCost = 0;
                string weaponName;
                switch(userChoice)
                {
                    case 1:
                    {
                        cost = 2 * userAmount;
                        baseCost = 2;
                        weaponName = "Stone Club";
                        break;
                    }
                    case 2:
                    {
                        cost = 2 * userAmount;
                        baseCost = 2;
                        weaponName = "Iron Spear";
                        break;
                    }
                    case 3:
                    {
                        cost = 5 * userAmount;
                        baseCost = 5;
                        weaponName = "Mythril Rapier";
                        break;
                    }
                    case 4:
                    {
                        cost = 15 * userAmount;
                        baseCost = 15;
                        weaponName = "Flaming Battle-Axe";
                        break;
                    }
                    case 5:
                    {
                        cost = 50 * userAmount;
                        baseCost = 50;
                        weaponName = "Vorpal Longsword";
                        break;
                    }
                }
                //make sure user can afford the purchase
                while(!canAfford(cost))
                {
                    cout << "You don't have enough gold to purchase " << userAmount << " " << weaponName << "s." << endl; 
                    cout << "Please enter a new value. (0 to cancel)" << endl;
                    cout << endl;
                    if(userAmount == 0)
                    {
                        break;
                    }
                    //ask user for new amount
                    cin >> userAmountString;
                    if(isdigit(userAmountString[0]))
                    {
                        userAmount = stoi(userAmountString, 0);
                    }
                    else
                    {
                        userAmount = -1;
                    }
                    //calculate new cost
                    cost = 0;
                    cost = baseCost * userAmount;
                }
                //make sure the user has enough space for the weapons
                while(userAmount > maxWeapons)
                {
                    cout << "You don't have enough space for " << userAmount << " " << weaponName << "(s)" << endl;
                    cout << "Please enter a new value. (0 to cancel)" << endl;
                    cout << endl;
                    if(userAmount == 0)
                    {
                        cout << endl;
                        cout << "Transaction cancelled." << endl;
                        cout << endl;
                        quitTransaction = true;
                        break;
                    }
                    //ask user for new amount
                    cin >> userAmountString;
                    if(isdigit(userAmountString[0]))
                    {
                        userAmount = stoi(userAmountString, 0);
                    }
                    else
                    {
                        userAmount = -1;
                    }
                }
                if(userAmount == 0)
                {
                    cout << endl;
                    cout << "Transaction cancelled." << endl;
                    cout << endl;
                    break;
                }
                //if user didn't quit transaction, make them confirm their purchase, and then process it
                if(!quitTransaction)
                {
                    cout << "Are you sure you want to buy " << userAmount << " " << weaponName << "s for " << cost * merchantMultiplier << " gold? (y/n)" << endl;
                    cout << endl;
                    string userConfirm;
                    cin >> userConfirm;
                    if(userConfirm[0] == 'y')
                    {
                        weapons[userChoice - 1] += userAmount;
                        gold -= cost * merchantMultiplier;
                        cout << "Thank you for your purchase! What else can I help you?" << endl;
                    }
                    else
                    {
                        cout << "Transaction Cancelled." << endl;
                    }
                }
                break;
            }
            //handle purchasing armor
            case 4:
            {
                cout << "How many suits of armor can I get you? It costs 10 gold per suit of armor  (0 to cancel)" << endl;
                cout << endl;
                int userAmount;
                string userAmountString;
                bool quitTransaction = false;
                int maxArmor = 5;
                //calculate how many suits of armor the player can purchase
                for(int i = 0; i < 5; i++)
                {
                    //subtract one if the player is alive
                    if(players[i].isPlayerDead())
                    {
                        maxArmor--;
                    }
                }
                //subtract from the max armor how much they can buy
                maxArmor -= armor;
                cout << "You can purchase armor for " <<  maxArmor << " more player(s)." << endl;\
                cout << endl;
                cin >> userAmountString;
                if(isdigit(userAmountString[0]))
                {
                    userAmount = stoi(userAmountString, 0);
                }
                else
                {
                    userAmount = -1;
                }
                //loop until user enters a valid amount or quits the transaction
                while(userAmount < 0)
                {
                    cout << "Please enter a valid amount. (0 to cancel)" << endl;
                    cout << endl;
                    cin >> userAmountString;
                    if(isdigit(userAmountString[0]))
                    {
                        userAmount = stoi(userAmountString, 0);
                    }
                    else
                    {
                        userAmount = -1;
                    }
                }
                if(userAmount == 0)
                {
                    cout << endl;
                    cout << "Transaction cancelled." << endl;
                    cout << endl;
                    break;
                }
                int cost = 10 * userAmount;
                //make sure user can afford the purchase
                while(!canAfford(cost))
                {
                    cout << "You don't have enough gold to purchase " << userAmount << " suits of armor." << endl; 
                    cout << "Please enter a new value. (0 to cancel)" << endl;
                    cout << endl;
                    if(userAmount == 0)
                    {
                        break;
                    }
                    //ask user for new amount
                    cin >> userAmountString;
                    if(isdigit(userAmountString[0]))
                    {
                        userAmount = stoi(userAmountString, 0);
                    }
                    else
                    {
                        userAmount = -1;
                    }
                    //calculate new cost
                    cost = 10 * userAmount;
                }
                //make sure the user has enough space for the armor
                while(userAmount > maxArmor)
                {
                    cout << "You don't have enough space for " << userAmount << " suits of armor." << endl;
                    cout << "Please enter a new value. (0 to cancel)" << endl;
                    cout << endl;
                    if(userAmount == 0)
                    {
                        cout << endl;
                        cout << "Transaction cancelled." << endl;
                        cout << endl;
                        quitTransaction = true;
                        break;
                    }
                    //ask user for new amount
                    cin >> userAmountString;
                    if(isdigit(userAmountString[0]))
                    {
                        userAmount = stoi(userAmountString, 0);
                    }
                    else
                    {
                        userAmount = -1;
                    }
                    //reset cost 
                    cost = 10 * userAmount;
                }
                if(userAmount == 0)
                {
                    break;
                }
                //handle confirming purchase
                cout << "Are you sure you want to buy " << userAmount << " suits of armor for " << cost << " gold? (y/n)" << endl;
                cout << endl;
                string userConfirm;
                cin >> userConfirm;
                if(userConfirm[0] == 'y')
                {
                    armor += userAmount;
                    gold -= cost;
                    cout << "Thank you for your purchase! What else can I help you?" << endl;
                }
                else
                {
                    cout << "Transaction Cancelled." << endl;
                }
                break;
                
            }
            case 5:
            {
                cout << "What would you like to sell? (E to cancel)" << endl;
                cout << "1. Silver ring (R) - " << 10 * merchantMultiplier <<  " gold pieces each (you have " << treasures[0] << ")" << endl;
                cout << "2. Ruby necklace (N) - " << 20 * merchantMultiplier <<  " gold pieces each (you have" << treasures[1] << ")" << endl;
                cout << "3. Emerald bracelet (B) - " << 30 * merchantMultiplier <<  " gold pieces each (you have " << treasures[2] << ")" << endl;
                cout << "4. Diamond circlet (C) - " << 40 * merchantMultiplier <<  " gold pieces each (you have " << treasures[3] << ")" << endl;
                cout << "5. Gem-encrusted goblet (G) - "  << 50 * merchantMultiplier <<  " gold pieces each (you have " << treasures[4] << ")" << endl;
                string userChoice;
                cin >> userChoice;
                bool quitTransaction = false;
                //loop until user enters a valid choice or quits the transaction
                while(userChoice[0] != 'R' && userChoice[0] != 'N' && userChoice[0] != 'B' && userChoice[0] != 'C' && userChoice[0] != 'G' && userChoice[0] != 'E')
                {
                    cout << "Please enter a valid choice. (E to cancel)" << endl;
                    cout << endl;
                    cin >> userChoice; 
                }
                if(userChoice[0] == 'E')
                {
                    quitTransaction = true;
                    break;
                }
                cout << "How many would you like to sell? (0 to cancel)" << endl;
                cout << endl;
                int userAmount;
                string userAmountString;
                cin >> userAmountString;
                if(isdigit(userAmountString[0]))
                {
                    userAmount = stoi(userAmountString, 0);
                }
                else
                {
                    userAmount = -1;
                }
                if(userAmount == 0)
                {
                    break;
                }
                int indexOfTreasure;
                int baseValue;
                int totalValue;
                string treasureName;
                switch(userChoice[0])
                {
                    case 'R':
                    {
                        indexOfTreasure = 0;
                        totalValue = 10 * userAmount * merchantMultiplier;
                        baseValue = 10;
                        treasureName = "Silver Ring";
                        break;
                    }
                    case 'N':
                    {
                        indexOfTreasure = 1;
                        totalValue = 20 * userAmount * merchantMultiplier;
                        baseValue = 20;
                        treasureName = "Ruby Necklace";
                        break;
                    }
                    case 'B':
                    {
                        indexOfTreasure = 2;
                        totalValue = 30 * userAmount * merchantMultiplier;
                        baseValue = 30;
                        treasureName = "Emerald Bracelet";
                        break;
                    }
                    case 'C':
                    {
                        indexOfTreasure = 3;
                        totalValue = 40 * userAmount * merchantMultiplier;
                        baseValue = 40;
                        treasureName = "Diamond Circlet";
                        break;
                    }
                    case 'G':
                    {
                        indexOfTreasure = 4;
                        totalValue = 50 * userAmount * merchantMultiplier;
                        baseValue = 50;
                        treasureName = "Gem-Encrusted Goblet";
                        break;
                    }
                }
                //loop until the user enters a number equal to or less than the amount of the item they have
                while(userAmount > treasures[indexOfTreasure])
                {
                    cout << "You don't have that many " << treasureName << "s." << endl;
                    cout << "Please enter a new value. (0 to cancel)" << endl;
                    cout << endl;
                    cin >> userAmountString;
                    if(isdigit(userAmountString[0]))
                    {
                        userAmount = stoi(userAmountString, 0);
                    }
                    else
                    {
                        userAmount = -1;
                    }
                    if(userAmount == 0)
                    {
                        quitTransaction = true;
                    }
                }
                if(quitTransaction)
                {
                    break;
                }
                //if user didn't quit transaction, make them confirm their purchase, and then process it
                cout << "Are you sure you want to sell " << userAmount << " " << treasureName << "s for " << totalValue << " gold? (y/n)" << endl;
                cout << endl;
                string userConfirm;
                cin >> userConfirm;
                if(userConfirm[0] == 'y')
                {
                    treasures[indexOfTreasure] -= userAmount;
                    gold += totalValue;
                    cout << "Thank you for your purchase! What else can I help you?" << endl;
                }
                else
                {
                    cout << "Transaction Cancelled." << endl;
                }

                break;
            }
            case 6:
            {
                cout << "Are you sure you're finished? You won't be able to buy anything else from me! (y/n)" << endl;
                string confirmQuit;
                cout << endl;
                cin >> confirmQuit;
                cout << endl;
                if(confirmQuit[0] == 'y')
                {
                    cout << "Stay safe out there! Goodbye!" << endl;
                    userQuit = true;
                }
                break;
            }
        }
    }
}


/*
 * handleRpsDoorPuzzle takes in the player array.
 * It handles the door puzzle the user will encounter if they attempt to open the door without a key.
 * It will return true if the user wins the puzzle, and false if they lose.
 * The user has a max of 3 attempts to win the puzzle
 * If they lose the RPS match, they lose 1 player, 1 armor and 1 weapon
 * If they tie 3+ times, they only lose 1 player
*/
bool Merchant::handleRpsDoorPuzzle(Player players[5])
{
    //create new probability class object
    Probability p;
    //player doesn't have a key and is trying to open the door, so they have to play rock (Boulder) paper (Parchment) scissors (Shears)
    cout << "You don't have a key to open this door! To open this, you must play Boulder, Parchment, Shears with me." << endl;
    cout << "If you win, I will let you pass, but if you lose, I'm taking one of your team members with me!" << endl;
    cout << "Are you ready to challenge me? (y/n)" << endl;
    cout << endl;
    string userConfirm;
    cin >> userConfirm;
    int numberOfAttempts = 0;
    while(userConfirm[0] != 'y' && userConfirm[0] != 'n')
    {
        cout << "Please enter a valid choice." << endl;
        cout << endl;
        cin >> userConfirm;
    }
    //if user doesn't want to play, they can't open the door, but they don't lose a team member, they will just have to try again later
    if(userConfirm[0] == 'n')
    {
        cout << "Very well, come back when you have a key or are ready to challenge me." << endl;
        return false;
    }
    //if user wants to play, the will play 1 round of rock paper scissors, and will continue to play if they tie
    cout << endl;
    cout << "Very well, let's begin!" << endl;
    cout << endl;
    cout << "Choose your choice wisely, your success in this dungeon may very well depend on it!" << endl;
    cout << "Please enter your choice: ((1) Boulder, (2) Parchment, (3)Shears)" << endl;
    int userChoice;
    string userChoiceString;
    cin >> userChoiceString;
    if(isdigit(userChoiceString[0]))
    {
        userChoice = stoi(userChoiceString, 0);
    }
    else
    {
        userChoice = 0;
    }
    while(userChoice != 1 && userChoice != 2 && userChoice != 3)
    {
        cout << "Please enter a valid choice." << endl;
        cout << endl;
        cin >> userChoiceString;
        if(isdigit(userChoiceString[0]))
        {
            userChoice = stoi(userChoiceString, 0);
        }
        else
        {
            userChoice = 0;
        }
    }
    //randomly generate the merchant's choice
    int merchantChoice = p.randomNumberBetween(1,3);
    //if user and merchant tie, they will play again
    while(userChoice == merchantChoice)
    {
        cout << "Good minds think alike! However, getting a tie isn't good enough to pass. Try again" << endl;
        cout << endl;
        cout << "Please enter your choice: ((1) Boulder, (2) Parchment, (3)Shears)" << endl;
        cin >> userChoice;
        while(userChoice != 1 && userChoice != 2 && userChoice != 3)
        {
            cout << "Please enter a valid choice." << endl;
            cout << endl;
            cin >> userChoice;
        }
        merchantChoice = p.randomNumberBetween(1,3);
        numberOfAttempts++;
        //if user has tried 3 times, they lose a team member
        if(numberOfAttempts >= 3)
        {
            int playerToLose = p.randomNumberBetween(1,4);
            //if the player is dead, then choose a new player
            while(players[playerToLose].isPlayerDead() == true)
            {
                playerToLose = p.randomNumberBetween(1,4);
            }
            players[playerToLose].setDead();
            cout << "OH NO! Your teammate " << players[playerToLose].getName() << " has been trapped as you've failed to beat me or lose. You must continue without them." << endl;
            cout << endl;
            cout << "Your party size has reduced to " << players[0].numPlayersAlive(players) << " members." << endl;
            cout << endl;
        }
    }
    
    //determine if user won or lost
    //KEY: 1 = Boulder, 2 = Parchment, 3 = Shears
    //Boulder beats Shears, Shears beats Parchment, Parchment beats Boulder
    //1 beats 3, 3 beats 2, 2 beats 1
    if(userChoice == 1 && merchantChoice == 3)
    {
        cout << "You chose Boulder, and I chose Shears. Boulder beats Shears, so you win!" << endl;
        cout << "I will let you pass, but be careful, you may not be so lucky next time." << endl;
        return true;
    }
    else if(userChoice == 3 && merchantChoice == 2)
    {
        cout << "You chose Shears, and I chose Parchment. Shears beats Parchment, so you win!" << endl;
        cout << "I will let you pass, but be careful, you may not be so lucky next time." << endl;
        return true;
    }
    else if(userChoice == 2 && merchantChoice == 1)
    {
        cout << "You chose Parchment, and I chose Boulder. Parchment beats Boulder, so you win!" << endl;
        cout << "I will let you pass, but be careful, you may not be so lucky next time." << endl;
        return true;
    }
    //in all other cases, the merchant wins
    else
    {
        cout << "You chose " << userChoice << ", and I chose " << merchantChoice << ". You lose!" << endl;
        cout << "I'm taking one of your team members with me! Good luck in the dungeon without them!" << endl;
        //randomly select a team member to remove
        int playerToLose = p.randomNumberBetween(0,4);
        while(playerToLose == 0)
        {
            playerToLose = p.randomNumberBetween(0,4);
        }
        //remove the team member
        players[playerToLose].setDead();
        cout << players[playerToLose].getName() << " has died." << endl;
        int playersLeft = players[0].numPlayersAlive(players);
        int totalWeapons = getNumWeapons();
        int weaponToLose = rand() % 5;
        if(playersLeft < totalWeapons)
        {
            //if the number of players is less than the number of weapons, then we need to remove a weapon
            //this is because the player can't have a weapon if they are dead, and the max number of weapons is 1 per alive player
            int weaponToRemove = p.randomNumberBetween(0,4);
            while(getWeaponsByIndex(weaponToRemove) == 0)
            {
                weaponToRemove = p.randomNumberBetween(0,4);
            }
            changeWeaponsByIndex(weaponToRemove, -1);
            changeArmor(-1);
        }
        return false;
    }

}

/*
 * the fillRiddles function takes in the empty vectors for the riddles and answers and fills them with the riddles and answers
 * it reads the riddles and answers from a file
 * it will return true if the riddles and answers were successfully filled, and false if they were not
*/
bool Merchant::fillRiddles(vector<string> &riddleQuestions, vector<string> &riddleAnswers)
{
    //read in riddles from file
    ifstream file;
    file.open("./data/riddles.txt");
    if(file.fail())
    {
        cout << "file failed to open" << endl;
        return false;
    }
    string line;
    while(getline(file, line))
    {
        string question[2];
        int numberOfSplits = splitTwo(line, '~', question,2);
        if(numberOfSplits != 2)
        {
            cout << "Error reading riddle file" << endl;
            return false;
        }
        riddleQuestions.push_back(question[0]);
        riddleAnswers.push_back(question[1]);
    }
    file.close();
    return true;
}

/*
 * the handleRiddle function takes in the riddle and answer vectors and asks the user a random riddle
 * it handles all of the inputs of asking the user the riddle.
 * it will return true if the user answers the riddle correctly, and false if they do not
 * if they fail to answer it correctly, they will be forced to fight a random monster, handled in the main function
*/
bool Merchant::handleRiddle(vector<string> &riddleQuestions, vector<string> &riddleAnswers)
{
    Probability p;
    //pick a random riddle
    int randomIndex = p.randomNumberBetween(0, riddleQuestions.size() - 1);
    string question = riddleQuestions[randomIndex];
    string answer = riddleAnswers[randomIndex];
    //ask the riddle
    cout << question << endl;
    string userAnswer;
    cin >> userAnswer;
    //check if the user got it right
    if(userAnswer == answer)
    {
        cout << "Correct! You may pass." << endl;
        return true;
    }
    else
    {
        cout << "Incorrect! You will now have to fight!" << endl;
        return false;
    }
    //should never get here
    return false;
}

//gets the amount of gold the player has 
int Merchant::getGold()
{
    return gold;
}

//sets the amount of gold the player has
void Merchant::setGold(int newGold)
{
    gold = newGold;
}

//changes the amount of gold the player has (positive or negative)
int Merchant::changeGold(int change)
{
    gold += change;
    return gold;
}

//weapon stuff

//gets the weapons by filling the provided array with the weapons
void Merchant::getWeapons(int newWeapons[5])
{
    for(int i = 0; i < 5; i++)
    {
        weapons[i] = newWeapons[i];
    }
}

//gets the number of weapons by index (type)
int Merchant::getWeaponsByIndex(int index)
{
    return weapons[index];
}

//changes the number of weapons by index (type) (positive or negative)
void Merchant::changeWeaponsByIndex(int weaponIndex, int change)
{
    if(weapons[weaponIndex] + change < 0)
    {
        weapons[weaponIndex] = 0;
    }
    else
    {
        weapons[weaponIndex] += change;
    }
}

//gets the total number of weapons the player has
int Merchant::getNumWeapons()
{
    int numWeapons = 0;
    for(int i = 0; i < 5; i++)
    {
        numWeapons += weapons[i];
    }
    return numWeapons;
}

//gets the armor the player has.
int Merchant::getArmor()
{
    return armor;
}

//changes the armor the player has (positive or negative)
void Merchant::changeArmor(int change)
{
   //make sure armor doesn't go below 0
    if(armor + change < 0)
    {
         armor = 0;
    }
    else
    {
         armor += change;
    }
}


//gets the total number of ingredients the player has
int Merchant::getIngredients()
{
    return ingredients;
}

//changes the total number of ingredients the player has (positive or negative)
void Merchant::changeIngredients(int change)
{
    //make sure its not negative
    if(ingredients + change < 0)
    {
        ingredients = 0;
    }
    else
    {
        ingredients += change;
    }
}

//changes the total number of treasures by index (positive or negative)
void Merchant::changeTreasureByIndex(int treasureIndex, int change)
{
    if(treasures[treasureIndex] + change < 0)
    {
        treasures[treasureIndex] = 0;
    }
    else
    {
        treasures[treasureIndex] += change;
    }
}

//gets the total number of treasures by index
int Merchant::getTreasureByIndex(int treasureIndex)
{
    return treasures[treasureIndex];
}

//fills the provided array with the cookware the player has.
void Merchant::getCookware(int newCookware[])
{
    for(int i = 0; i > 2; i++)
    {
        newCookware[i] = cookware[i];
    }
}

//returns the total number of treasures the player has
int Merchant::getTotalTreasure()
{ 
    int totalTreasure = 0;
    for(int i = 0; i < 5; i++)
    {
        totalTreasure += treasures[i];
    }
    return totalTreasure;
}

//changes the cookware item by index (positive or negative)
void Merchant::changeCookware(int cookwareIndex, int change)
{
    if(cookware[cookwareIndex] + change < 0)
    {
        cookware[cookwareIndex] = 0;
    }
    else
    {
        cookware[cookwareIndex] += change;
    }
}

//gets the number of cookware by index (type)
int Merchant::getCookwareByIndex(int index)
{
    return cookware[index];
}

//gets the name of the cookware by index
string Merchant::getCookwareNameByIndex(int index)
{
    if(index == 0)
    {
        return "Ceramic Pot";
    }
    else if(index == 1)
    {
        return "Frying Pan";
    }
    else if(index == 2)
    {
        return "Cauldron";
    }
    else
    {
        return "Error";
    }
}

//gets the name of the weapon by index
string Merchant::getWeaponNameByIndex(int index)
{
    if(index == 0)
    {
        return "Stone Club";
    }
    else if(index == 1)
    {
        return "Iron Spear";
    }
    else if(index == 2)
    {
        return "Mythril Rapier";
    }
    else if(index == 3)
    {
        return "Flaming Battle-Axe";
    }
    else if(index == 4)
    {
        return "Vorpal Longsword";
    }
    else
    {
        return "Error";
    }
}

//prints the number of cookware the player has, only used for debugging
void Merchant::printCookware()
{
    cout << "Cookware: " << endl;
    cout << "1. Pot - " << cookware[0] << endl;
    cout << "2. Pan - " << cookware[1] << endl;
    cout << "3. Skillet - " << cookware[2] << endl;
}


//gets the number of keys the player has
int Merchant::getKeys(){
    return keys;
}

//changes the number of keys the player has (positive or negative)
void Merchant::changeKeys(int change){
    keys += change;
}