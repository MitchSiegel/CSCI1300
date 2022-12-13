//Probability.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 3

#include "Probability.h"
#include "Map.h"
#include "Monster.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <ctype.h>
using namespace std;

//this function will pause the game until the player presses enter, so the player can read the text
void Probability::pressToContinue()
{
    if(!pressToContinueVar)
    {
        pressToContinueVar = true;
        cout << endl;
        cout << "Press enter to continue..." << endl;
        cin.ignore();
        cin.get();
        pressToContinueVar = false;
    }
}


Probability::Probability()
{
    //default constructor
    pressToContinueVar = false;
}


/*
 * randomNumberBetween takes in two ints, and returns a random number between the two ints.
*/
int Probability::randomNumberBetween(int min, int max)
{
    int randomNum = rand() % (max - min + 1) + min;
    return randomNum;
}

/*
 * generateRandomPlacement takes in the map class, and handles the generation of the dungeon.
 * it will handle placing 5 rooms and 5 NPCs.
 * It will make sure the space is free before placing the room or NPC.
*/
void Probability::generateRandomPlacement(Map &map)
{
    Probability p;
    //add 5 Rooms to the map
    int roomsAdded = 0;
    while(roomsAdded < 5)
    {
        //generate a random number between 0 and 4
        int x = p.randomNumberBetween(0, 11);
        int y = p.randomNumberBetween(0, 11);
        //if the room is not occupied, add a room
        bool check = map.addRoom(x, y);
        //if the room is not already occupied
        if(check)
        {
            //add a room
            roomsAdded++;
        }
    }
    int NPCsAdded = 0;
    while(NPCsAdded < 5)
    {
        //generate a random number between 0 and 4
        int x = p.randomNumberBetween(0, 11);
        int y = p.randomNumberBetween(0, 11);
        //if the room is not occupied, add a room
        bool check = map.addNPC(x, y);
        //if the room is not already occupied
        if(check)
        {
            //add a room
            NPCsAdded++;
        }
    }
}

/*
 * handleMoving handles the aftermath of moving. It takes in the player array.
 * It will calculate the chances of stuff happening after moving.
*/
bool Probability::handleMoving(Player players[5])
{
    //20% chance that the player will lose 1 fullness
    bool loseFullness = false;
    for(int i = 0; i < 5; i++)
    {
        bool result = (randomNumberBetween(0,100)) < 20;
        if(result == true)
        {
            loseFullness = true;
            players[i].changeFullness(-1);
        }
    }
    return loseFullness;
}

/*
 * handleInvestigation takes in the map class, the player array, how many rooms the player has cleared, and the merchant.
 * It will handle the action of investigating a space.
 * They can find a key, fight a monster, or find nothing.
 * It will return a bool if they fight a monster, so the game knows into the fighting mode.
*/
bool Probability::handleInvestigation(Map &map, Player players[5], int roomCleared,Merchant &merchant)
{
    bool monsterFound = false;
    int percent = randomNumberBetween(0, 100);
    bool result = (randomNumberBetween(0,100)) < 50;

    if(percent <= 10)
    {
        //player finds the key
        merchant.changeKeys(1);
        cout << "You found a key! Congrats! " << endl;
        pressToContinue();
    }
    else if(percent <= 30)
    {
        //player finds a piece of treasure
        merchant.changeTreasureByIndex(roomCleared,1);
        cout << "You found a piece of treasure!" << endl;
        pressToContinue();
    }
    else if(percent <= 50)
    {
        //player finds a monster, so will return true and the main file will trigger the fightMonster function
        monsterFound = true;
        
    }
    else
    {
        //nothing happens
        cout << "You found nothing." << endl;
        pressToContinue();
    }
    //set the map space as explored 
    map.exploreSpace(map.getPlayerCol(), map.getPlayerRow());
    //fighting a monster also has this 50% chance, so we don't need to repeat it 
    if(!monsterFound)
    {
        //after the player investigates, they have a 50% chance of losing 1 fullness
        for(int i = 0; i < 5; i++)
        {
            bool result = (randomNumberBetween(0,100)) < 50;
            if(result == true)
            {
                players[i].changeFullness(-1);
            }
        }
    }
    return monsterFound;
}

/*
 * handleCooking takes in the player array and the merchant. 
 * It will handle the action of cooking.
 * Because the cookware has a chance of breaking, it is handled here in the probability class.
 * If the cookware breaks, a message is printed out and the player loses 1 cookware.
*/
void Probability::handleCooking(Player players[5], Merchant &merchant)
{
    bool hasCooking = false;
    int cookware[3];
    //populate and list the cookware
    for(int i = 0; i < 3; i++)
    {
        cookware[i] = merchant.getCookwareByIndex(i);
        if(cookware[i] > 0)
        {
            hasCooking = true;
        }
        cout << i  << ". " << cookware[i] << endl;
    }
    //check if the player has any cookware
    for(int i = 0; i > 3; i++)
    {
        if(cookware[i] > 0)
        {
            hasCooking = true;
        }
    }
    if(hasCooking)
    {
        //if the player has cookware, lets list the options
        cout << "You have the following cookware. Please select an option from below. (0 to cancel) " << endl;
        if(cookware[0] > 0)
        {
            cout << "(1) Ceramic Pot: " << cookware[0] << ". This item has a 25% chance of breaking each time you use it." << endl;
        }
        if(cookware[1] > 0)
        {
            cout << "(2) Frying Pan: " << cookware[1] << ". This item has a 10% chance of breaking each time you use it." << endl;
        }
        if(cookware[2] > 0)
        {
            cout << "(3) Caldron: " << cookware[2] << ". This item has a 2% chance of breaking each time you use it." << endl;
        }
        cout << endl;
        int choice;
        string input;
        cin >> input;
        //check if the input is a number
        if(isdigit(input[0]))
        {
            choice = stoi(input);
        }
        else
        {
            choice = -1;
        }
        //if the player chooses to cancel
        if(choice == 0)
        {
            cout << "You have chosen to cancel. " << endl;
            return;
        }
        //make sure the user enters a valid choice
        while(choice < 1 || choice > 3 || choice == -1)
        {
            cout << "Please enter a valid choice. (0 to cancel)" << endl;
            cin >> input;
            if(isdigit(input[0]))
            {
                choice = stoi(input);
            }
            else
            {
                choice = -1;
            }
            if(choice == 0)
            {
                cout << "You have chosen to cancel. " << endl;
                return;
            }
        }
        //if the player chooses to cancel break
        if(choice == 0)
        {
            return;
        }
        //check if the player has the cookware they selected
        while(cookware[choice - 1] == 0)
        {
            cout << "You do not have that item. Please select a different item." << endl;
            cin >> input;
            if(isdigit(input[0]))
            {
                choice = stoi(input);
            }
            else
            {
                choice = -1;
            }
        }
        cout << "Ingredients will heal you 5:1, as long as the item doesn't break." << endl;
        //if the player has the cookware, then we can cook
        //cooking involves consuming ingredients and gaining fullness at a 5:1 ratio (ingredients:fullness)
        //this is all assuming the cooking item does not break
        int ingredients = merchant.getIngredients();
        cout << "You have " << ingredients << " ingredients. How many would you like to use (must use multiples of 5)?" << endl;
        int numIngredients;
        string ingredientsInput;
        cin >> ingredientsInput;
        if(isdigit(ingredientsInput[0]))
        {
            numIngredients = stoi(ingredientsInput);
        }
        else
        {
            numIngredients = -1;
        }
        //make sure the player is using a multiple of 5
        while(numIngredients % 5 != 0 || numIngredients == -1)
        {
            cout << "You must use a multiple of 5. Please enter a new number." << endl;
            cin >> ingredientsInput;
            if(isdigit(ingredientsInput[0]))
            {
                numIngredients = stoi(ingredientsInput);
            }
            else
            {
                numIngredients = -1;
            }

        }
        //make sure the player has enough ingredients
        while(numIngredients > ingredients || numIngredients == -1)
        {
            cout << "You do not have enough ingredients. Please enter a new number." << endl;
            cin >> ingredientsInput;
            if(isdigit(ingredientsInput[0]))
            {
                numIngredients = stoi(ingredientsInput);
            }
            else
            {
                numIngredients = -1;
            }
        }
        //if the player has enough ingredients, then we can cook
        //lets check and see if the item breaks
        bool itemBreaks = false;
        if(choice == 1)
        {
            //ceramic pot has a 25% chance of breaking
            itemBreaks = (randomNumberBetween(0,100)) < 25;
        }
        else if(choice == 2)
        {
            //frying pan has a 10% chance of breaking
            itemBreaks = (randomNumberBetween(0,100)) < 10;
        }
        else if(choice == 3)
        {
            //caldron has a 2% chance of breaking
            itemBreaks = (randomNumberBetween(0,100)) < 2;
        }
        if(!itemBreaks)
        {
            //if the item doesn't break, then we can finally handle the health.
        
            int fullnessGained = numIngredients / 5;
            for(int i = 0; i < 5; i++)
            {
                players[i].changeFullness(fullnessGained);
            }
            merchant.changeIngredients(-numIngredients);
            cout << "The cooking was a success! You gained " << fullnessGained << " fullness." << endl;
            pressToContinue();
        }
        else
        {
            //if the item breaks, then we need to remove it from the merchant's inventory
            cookware[choice - 1]--;
            cout << "Your item broke! You have lost " << numIngredients << " ingredient(s)" << endl;
            pressToContinue();
        }
    }
    else
    {
        cout << "You don't have any cookware to cook with!" << endl;
        pressToContinue();
    }
}

/*
 * fightMonster handles the fight between the player and the monster.
 * It takes in the player array, the vector of monsters, the merchant, and the number of rooms cleared.
 * It calculates the fight based on the formula in the function. 
 * It handles both the win and loss conditions.
 * It will return true if the player wins, and false if the player loses.
*/
bool Probability::fightMonster(Player players[5],vector<Monster> &monsters, int roomsCleared,Merchant &merchant)
{
    Monster monster = pickRandomMonster(monsters, roomsCleared);
    if(monster.getName() == "No Monster")
    {
        cout << endl;
        cout << "You looked for a monster to fight." << endl;
        cout << "* But nobody came " << endl;
        pressToContinue();
        return false;
    }
    cout << endl;
    cout << "You have encountered a " << monster.getName() << "!" << endl;
    cout << endl;
    //make sure the player has atleast 1 weapon
    bool hasWeapon = false;
    bool stillInFight = true;
    bool wonFight = false;
    int totalWeapons = 0;
    int uniqueWeapons = 0;
    int weapons[5];
    for(int i = 0; i < 5; i++)
    {
        int tempWeapon = merchant.getWeaponsByIndex(i);
        weapons[i] = tempWeapon;
        if(tempWeapon > 0)
        {
            hasWeapon = true;
            totalWeapons += tempWeapon;
            uniqueWeapons++;
        }
    }
    //handle the sorcerer's battle, which is different from the other monsters, so its will be handled separately
    if(roomsCleared+1 == 6)
    {
        return handleSorcererBattle(players,merchant,weapons,totalWeapons,uniqueWeapons);
    } 

    //check if the player has any weapons, and then display the options they have
    while(stillInFight)
    {
        if(hasWeapon)
        {
            //if the player has weapons, then we can fight
            cout << "(1) Attack" << endl;
            cout << "(2) Surrender" << endl;
            int choice;
            string input;
            cin >> input;
            if(isdigit(input[0]))
            {
                choice = stoi(input);
            }
            else
            {
                choice = -1;
            }
            //make sure the player enters a valid choice
            while(choice < 1 || choice > 2 || choice == -1)
            {
                cout << "Please enter a valid choice." << endl;
                cin >> input;
                if(isdigit(input[0]))
                {
                    choice = stoi(input);
                }
                else
                {
                    choice = -1;
                }
            }
            //if the player chooses to attack
            if(choice == 1)
            {
                //calculate the vars needed to calculate a win or not
                //weapons calculations. index's 2,3,4 are weapons that add bonus damage
                double w = 5 * (totalWeapons) + 1 * (weapons[2]) + 2 * (weapons[3]) + 3 * (weapons[4]);

                //d is the number of unique weapons the player has. +1 for each unique weapon type
                int d = uniqueWeapons;

                int a = merchant.getArmor();

                int c = roomsCleared+1;

                int r1 = randomNumberBetween(1,4);
                int r2 = randomNumberBetween(1,8);
                //calculate the win chance
                bool hasWon;
                //avoid division by 0
                if(a == 0)
                {
                    hasWon = ((r1 * w + d) - ((r2 * c))) > 0;
                }
                else
                {
                    hasWon = ((r1 * w + d) - ((r2 * c)/a)) > 0;
                }
                if(hasWon)
                {
                    cout << "You have won the fight!" << endl;
                    //if the player has won, then we need to remove the monster from the vector
                    monster.removeMonsterByName(monsters, monster.getName());
                    //10% of getting a key
                    if(randomNumberBetween(1,100) < 10)
                    {
                        cout << "You have found a key!" << endl;
                        merchant.changeKeys(1);
                    }
                    //gold winnings
                    int goldWinnings = 10 * c;
                    int ingredientsWinnings = 5 * c;
                    cout << "You have won " << goldWinnings << " gold and " << ingredientsWinnings << " ingredients!" << endl;
                    merchant.changeGold(goldWinnings);
                    merchant.changeIngredients(ingredientsWinnings);
                    stillInFight = false;
                    wonFight = true;
                }
                else 
                {
                    cout << "You have lost the fight." << endl;
                    //lose 1/4 of the gold
                    int goldLost = merchant.getGold() * 0.25;
                    merchant.changeGold(-goldLost);
                    cout << "You have lost " << goldLost << " gold." << endl;
                    //lose up to 30kg of food 
                    int foodLost = randomNumberBetween(0,30);
                    merchant.changeIngredients(-foodLost);
                    int armor = merchant.getArmor();
                    //each party member (except the player) has a 10% chance of dying, 5% if they have armor
                    for(int i = 1; i < 5; i++)
                    {
                        if(armor >= i)
                        {
                            if(randomNumberBetween(1,100) < 5)
                            {
                                players[i].setDead();
                                cout << players[i].getName() << " has died." << endl;
                                int playersLeft = players[0].numPlayersAlive(players);
                                int totalWeapons = merchant.getNumWeapons();
                                if(playersLeft < totalWeapons)
                                {
                                    //if the number of players is less than the number of weapons, then we need to remove a weapon
                                    removeRandomWeapon(players, merchant);
                                    merchant.changeArmor(-1);
                                }
                            }
                        }
                        else
                        {
                            if(randomNumberBetween(1,100) < 10)
                            {
                                players[i].setDead();
                                cout << players[i].getName() << " has died." << endl;
                                int playersLeft = players[0].numPlayersAlive(players);
                                int totalWeapons = merchant.getNumWeapons();
                                if(playersLeft < totalWeapons)
                                {
                                    //if the number of players is less than the number of weapons, then we need to remove a weapon
                                    //this is because the player can't have a weapon if they are dead, and the max number of weapons is 1 per alive player
                                    removeRandomWeapon(players,merchant);
                                    merchant.changeArmor(-1);
                                }
                            }
                        }
                    }
                    int ingredientToLose = randomNumberBetween(0,30);
                    merchant.changeIngredients(-ingredientToLose);
                    cout << "You have lost " << ingredientToLose << " ingredients." << endl;
                    stillInFight = false;
                }
            }
            else
            {
                //make them confirm their choice
                cout << "Are you sure you want to surrender? (y/n)" << endl;
                string confirm;
                cin >> confirm;
                if(confirm[0] == 'y')
                {
                    int playerToLose = randomNumberBetween(1,4);
                    cout << "You have chosen to surrender. " << players[playerToLose].getName() << " has been taken hostage." << endl;
                    //remove a random weapon from the players's inventory
                    int weaponToLose = randomNumberBetween(0,4);
                    cout << "Weapon to lose: " << weaponToLose << endl;
                    while(weapons[weaponToLose] == 0)
                    {
                        cout << "Weapon to lose: " << weaponToLose << endl;
                        weaponToLose = randomNumberBetween(0,4);
                    }
                    merchant.changeWeaponsByIndex(weaponToLose, -1);
                    players[playerToLose].setDead();
                    stillInFight = false;
                }
                else
                {
                    cout << "You have chosen not to surrender." << endl;
                    pressToContinue();
                }
            }
        }
        else 
        {
            cout << "You don't have any weapons to fight with!" << endl;
            cout << "The only option you have is surrender." << endl;
            cout << "You will lose 1 party member permanently." << endl;
            cout << endl;
            //if the player doesn't have any weapons, then they can only surrender so just make them surrender
            //choose a random player to be held hostage (lose permanently), this should never be the player (index 0)
            int playerToLose = randomNumberBetween(1,4);
            cout << "You have chosen to surrender. " << players[playerToLose].getName() << " has been taken hostage." << endl;
            players[playerToLose].setDead();
            stillInFight = false;
        }
    }

    //handle a 50/50 chance to drop each players fullness by 1
    for(int i = 0; i < 5; i++)
    {
        bool result = (randomNumberBetween(0,100)) < 50;
        if(result == true)
        {
            players[i].changeFullness(-1);
        }
    }
    pressToContinue();
    return wonFight;
}

/*
 * pickRandomMonster takes in the vector of monsters and returns a random monster from the vector.
 * if there are no monsters at that level, then it returns a monster with the name of "No Monster".
 * this signals that there are no monsters at that level.
*/
Monster Probability::pickRandomMonster(vector<Monster> &monsters, int roomsCleared)
{
    Monster m;
    //if there are no monsters at that level, then return a monster with the name of "No Monster"
    m.setName("No Monster");
    //get all the monsters at that level
    vector<Monster> monstersLeveled = m.getMonstersByLevel(monsters, roomsCleared+1);
    //if its greater than 0, then there are monsters at that level, so pick a random one
    if(monstersLeveled.size() > 0)
    {
        int randomIndex = randomNumberBetween(0, monstersLeveled.size()-1);
        return monstersLeveled[randomIndex];
    }
    else
    {
        return m;
    }
}

/*
* handleMisfortune takes in the player, if they used a key to open the door, and the merchant.
* it handles the various misfortunes that can happen to the player.
* 30% chance team is robbed, loose 10kg of food, 1 random cookware, or 1 armor
* 10% one weapon / armor is lost
* 20% of food poisoning, 1 random player loses 10 fullness, if they are at 0 fullness after the -10, they die instantly
* 30% team member gets stuck in last room, this event only happens if they opened the door with a key before this event 
*/
void Probability::handleMisfortune(Player players[5], bool openedDoorWithKey,Merchant &merchant)
{
    //30% chance team is robbed, loose 10kg of food, 1 random cookware, or 1 armor
    //10% one weapon / armor is lost
    //20% of food poisoning, 1 random player loses 10 fullness, if they are at 0 fullness after the -10, they die instantly
    //30% team member gets stuck in last room, this event only happens if they opened the door with a key before this event 

    int randomNum = randomNumberBetween(0,100);
    //team is robbed
    if(randomNum <= 30)
    {
        int randomNum2 = randomNumberBetween(0,100);
        if(randomNum2 <= 50)
        {
            //loose 10kg of food
            int foodToLose = randomNumberBetween(0,10);
            merchant.changeIngredients(-foodToLose);
            cout << "You have lost " << foodToLose << "kg of food." << endl;
        }
        else if(randomNum2 <= 75)
        {
            //loose 1 random cookware
            int cookwareToLose = randomNumberBetween(0,5);
            merchant.changeCookware(cookwareToLose, -1);
            cout << "You have lost 1 " << merchant.getCookwareNameByIndex(cookwareToLose) << endl;
        }
        else
        {
            //loose 1 armor
            merchant.changeArmor(-1);
            cout << "You have lost 1 armor." << endl;
        }
    }
    //loose 10kg of food, 1 random weapon, or 1 armor
    else if(randomNum <= 40)
    {
        int randomNum2 = randomNumberBetween(0,100);
        if(randomNum2 <= 50)
        {
            //loose 10kg of food
            int foodToLose = randomNumberBetween(0,10);
            merchant.changeIngredients(-foodToLose);
            cout << "You have lost " << foodToLose << "kg of food." << endl;
        }
        else if(randomNum2 <= 75)
        {
            //loose 1 random weapon
            int weaponToLose = randomNumberBetween(0,4);
            int weaponToRemove = randomNumberBetween(0,4);
            while(merchant.getWeaponsByIndex(weaponToRemove) == 0)
            {
                weaponToRemove = randomNumberBetween(0,4);
            }
            merchant.changeWeaponsByIndex(weaponToRemove, -1);
            cout << "OH NO! Your " << merchant.getWeaponNameByIndex(weaponToRemove) << " broke!" << endl;

        }
        else
        {
            //loose 1 armor
            merchant.changeArmor(-1);
            cout << "You have lost 1 armor." << endl;
        }
    }
    //food poisoning
    else if(randomNum <= 70)
    {
        int playerToLose = randomNumberBetween(1,4);
        while(players[playerToLose].isPlayerDead() == true)
        {
            playerToLose = randomNumberBetween(1,4);
        }
        players[playerToLose].changeFullness(-5);
        if(players[playerToLose].getFullness() <= 0)
        {
            cout << players[playerToLose].getName() << " has died from food poisoning." << endl;
            players[playerToLose].setDead();
        }
        else
        {
            cout << players[playerToLose].getName() << " has lost 10 fullness." << endl;
        }
    }
    //stuck in the last room
    else if(randomNum <= 90 && openedDoorWithKey == true)
    {
        int playerToLose = randomNumberBetween(1,4);
        //if the player is dead, then choose a new player
        while(players[playerToLose].isPlayerDead() == true)
        {
            playerToLose = randomNumberBetween(1,4);
        }
        players[playerToLose].setDead();
        cout << "OH NO! Your teammate " << players[playerToLose].getName() << " is trapped in the previous room and is unable to get through. You must continue without them." << endl;
        cout << endl;
        cout << "Your party size has reduced to " << players[0].numPlayersAlive(players) << " members." << endl;
    }
    else if(randomNum <= 95){
        //good luck
        int playerToWin = randomNumberBetween(1,4);
        //if the player is dead, then choose a new player
        while(players[playerToWin].isPlayerDead() == true)
        {
            playerToWin = randomNumberBetween(1,4);
        }
        players[playerToWin].changeFullness(10);
        cout << "Wow, you stumbled upon a healing potion, good job! " << players[playerToWin].getName() << " has gained 10 fullness." << endl;
    }
    else
    {
        //good luck
        int playerToWin = randomNumberBetween(1,4);
        //if the player is dead, then choose a new player
        while(players[playerToWin].isPlayerDead() == true)
        {
            playerToWin = randomNumberBetween(1,4);
        }
        players[playerToWin].changeFullness(20);
        cout << "Wow, you stumbled upon a healing potion, good job! " << players[playerToWin].getName() << " has gained 20 fullness." << endl;

    }
    pressToContinue();
    return;
}

/*
 * handleMisfortuneAfterMonster takes in the player, if they defeated the monster, and the merchant.
 * it handles the various misfortunes that can happen to the player after fighting a monster.
*/
void Probability::handleMisfortuneAfterMonster(Player players[5],bool defeatedMonster,Merchant &merchant)
{
    //60% chance team is robbed (the misfortune that happens)
    bool misfortuneHappened = randomNumberBetween(0,100) < 60;
    //40% chance team is robbed if they lose the fight
    bool misfortuneHappened2 = randomNumberBetween(0,100) < 40;
    if(misfortuneHappened && defeatedMonster)
    {
        int randomNum2 = randomNumberBetween(0,100);
        if(randomNum2 <= 50)
        {
            //loose 10kg of food
            int foodToLose = randomNumberBetween(0,10);
            merchant.changeIngredients(-foodToLose);
            cout << "You have lost " << foodToLose << "kg of food." << endl;
        }
        else if(randomNum2 <= 75)
        {
            //loose 1 random cookware
            int cookwareToLose = randomNumberBetween(0,5);
            merchant.changeCookware(cookwareToLose, -1);
            cout << "You have lost 1 " << merchant.getCookwareNameByIndex(cookwareToLose) << endl;
        }
        else
        {
            //loose 1 armor
            merchant.changeArmor(-1);
            cout << "You have lost 1 armor." << endl;
        }
    }
    if(misfortuneHappened2 && !defeatedMonster)
    {
        int randomNum2 = randomNumberBetween(0,100);
        if(randomNum2 <= 50)
        {
            //loose 10kg of food
            int foodToLose = randomNumberBetween(0,10);
            merchant.changeIngredients(-foodToLose);
            cout << "You have lost " << foodToLose << "kg of food." << endl;
        }
        else if(randomNum2 <= 75)
        {
            //loose 1 random cookware
            int cookwareToLose = randomNumberBetween(0,5);
            merchant.changeCookware(cookwareToLose, -1);
            cout << "You have lost 1 " << merchant.getCookwareNameByIndex(cookwareToLose) << endl;
        }
        else
        {
            //loose 1 armor (if they have armor)
            if(merchant.getArmor() > 1){
                merchant.changeArmor(-1);
                cout << "You have lost 1 armor." << endl;
            }

        }
    }

}

/*
 * removeRandomWeapon takes in the player array and the merchant.
 * it handles removing a random weapon from the player.
 * it will make sure the player has that type of weapon before removing it.
 * it will always return true.
*/
bool Probability::removeRandomWeapon(Player players[5],Merchant &merchant)
{
    //loose 1 random weapon
    int weaponToLose = randomNumberBetween(0,4);
    while(merchant.getWeaponsByIndex(weaponToLose) == 0)
    {
        weaponToLose = randomNumberBetween(0,4);
    }
    merchant.changeWeaponsByIndex(weaponToLose, -1);
    return true;
}
/*
 * handleSorcererBattle handles the battle with the sorcerer. 
 * it takes in the player array, the merchant.
 * it will return true if the player wins, false if they lose.
 * it is the final battle of the game.
*/
bool Probability::handleSorcererBattle(Player players[5],Merchant &merchant, int weapons[],int totalWeapons,int uniqueWeapons)
{
    //Sorcerer battle, will have 2 phases
    cout << "I'm very surprised you made this far, traveler, but you have not escaped the dungeon yet." << endl;
    cout << "You must defeat me, the Sorcerer, to escape." << endl;
    cout << "Let's see if you have what it takes." << endl;
    cout << endl;
    cout << endl;
    //temporary return value
    bool returnValue = false;

    //first phase is just a normal battle
    cout << "I think we should start with a normal battle, you should be quite used to those by now." << endl;
    cout << "But do not think this is it, winning the battle is just the first step." << endl;
    cout << endl;
    cout << endl;

    //before the first phase, the player has a 25% chance a random weapon will be removed
    bool weaponRemoved = randomNumberBetween(0,100) < 25;
    bool result;
    if(weaponRemoved)
    {
        result = removeRandomWeapon(players,merchant);
        if(result)
        {
            cout << "Hmm, you seem to have a lot of weapons, don't think you'll mind if I just take one. Thanks!" << endl;
            totalWeapons--;
        }
    }
    pressToContinue();
    //calculate the vars needed to calculate a win or not
    //weapons calculations. index's 2,3,4 are weapons that add bonus damage

    double w = 5 * (totalWeapons) + 1 * (weapons[2]) + 2 * (weapons[3]) + 3 * (weapons[4]);

    //d is the number of unique weapons the player has. +1 for each unique weapon type
    int d = uniqueWeapons;

    int a = merchant.getArmor();

    int c = 6;

    int r1 = randomNumberBetween(1,4);
    int r2 = randomNumberBetween(1,8);
    //calculate the win chance
    bool hasWon;
    //avoid division by 0
    if(a == 0)
    {
        hasWon = ((r1 * w + d) - ((r2 * c))) > 0;
    }
    else
    {
        hasWon = ((r1 * w + d) - ((r2 * c)/a)) > 0;
    }

    //if the player has won, then they move on to the second phase
    if(hasWon)
    {
        //before the second phase fight, give the player a chance to use their ingredients to heal
        int ingredients = merchant.getIngredients();
        if(ingredients > 0)
        {
            cout << "Traveler, if you are to even have a chance of defeating me, you should heal." << endl;
            cout << "I'm feeling generous today, I can take your ingredients and heal you." << endl;
            cout << "Normally you need to use cookware to cook, but I will cut you a deal player, I will heal you in a 2:1 ratio, without cookware." << endl;
            cout << "Would you like to use " << ingredients << "kg of food to heal your team " << ingredients/2 << " fullness? (y/n)" << endl;
            string input;
            cin >> input;
            bool healed = false;
            if(input == "y")
            {
                healed = true;
                //heal the team
                for(int i = 0; i < 5; i++)
                {
                    if(players[i].isPlayerDead() == false)
                    {
                        players[i].changeFullness(ingredients/2);
                    }
                }
                //remove the ingredients
                merchant.changeIngredients(-ingredients);
            }
            //the second phase of the battle is a battle of fullness, if they have enough fullness, they win
            cout << "I hope you chose to heal your team." << endl;
            cout << "The second phase is a battle of fullness." << endl;
            cout << "Let the battle begin!" << endl;
            int totalFullness = 0;
            for(int i = 0; i < 5; i++)
            {
                totalFullness += players[i].getFullness();
            }
            //they automatically win if they have 200 fullness
            if(totalFullness >= 170)
            {
                cout << "Congrats, you have defeated me." << endl;
                cout << "I suppose I should let you leave now." << endl;
                returnValue = true;
            }
            //if they have 50% of the total starting health, then there is a 1 in 6 chance they win
            else if(totalFullness >= 120)
            {
                int randomNum = randomNumberBetween(0,6);
                if(randomNum == 0)
                {
                    cout << "Congrats, you have defeated me." << endl;
                    cout << "You were very lucky traveler, I almost had you." << endl;
                    cout << "I suppose I should let you leave now." << endl;
                    returnValue = true;
                }
                else
                {
                    cout << "You have lost the game." << endl;
                    returnValue = false;
                }
            }
            else
            {
                cout << "I have defeated you." << endl;
                cout << "You will now be stuck in this dungeon forever." << endl;
                if(!healed)
                {
                    cout << "There was a reason I asked if you wanted to use your ingredients. I'm disappointed in you." << endl;
                }
                else 
                {
                    cout << "Thank you for heeding my advice to heal, but you weren't careful enough in my dungeon." << endl;
                }

                returnValue = false;
            }
        }
    }
    return returnValue;
}
