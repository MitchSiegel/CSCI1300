//Main.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 3

// g++ main.cpp map.cpp menu.cpp merchant.cpp monster.cpp player.cpp probability.cpp --std=c++17 -o main

#include "Map.h"
#include "Menu.h"
#include "Probability.h"
#include "Merchant.h"
#include "Player.h"
#include "Monster.h"
#include <iostream>
#include <string>
#include <ctype.h>
#include <vector>
#include <fstream>

using namespace std;

/*
 * Main.cpp is the game driver. It contains all of hte code needed to run and utilize the classes provided.
*/

//runs the entire game
int main()
{
    //initialize classes
    Map map;
    Probability prob;
    string userInput;
    Menu menu;
    Player players[5];
    Merchant merchant;
    Monster monster;
    vector<Monster> monsters;
    vector<string> riddleQuestions;
    vector<string> riddleAnswers;
    //set the random seed
    srand(time(0));
    //initialize variables
    int sorcererLevel = 0;
    int spacesExplored = 0;
    int turns = 0;
    int monstersDefeated = 0;
    string userChoiceString = "";
    int userChoice;
    int spaceType;
    int roomsCleared = 0;
    bool gameRunning = true;
    bool actionWasMoving = false;
    bool openedDoorWithKey = false;
    //can only resurrect once
    bool resurrected = false;

    //set up map
    prob.generateRandomPlacement(map);
    //set up monsters
    monster.fillArray(monsters);
    //set up riddles
    merchant.fillRiddles(riddleQuestions, riddleAnswers);
    //set up users
    menu.setupUsers(players);

    //set data for users for testing 
    // for(int i = 0; i < 5; i++)
    // {
    //     players[i].setName("Mitch" + to_string(i));
    // }
    //display the first status update
    menu.displayStatusUpdatePart1(sorcererLevel, merchant.getKeys(), roomsCleared);
    merchant.displayInventoryMenu();
    menu.displayStatusUpdatePart2(map, players);

    //initial merchant visit dialog
    merchant.firstVisit();
    //initialize the first visit to the merchant
    merchant.handleInteraction(players);
    //start the turn based aspect of the game
    while(gameRunning)
    {
        //do things before the players makes their choice 
        int x = map.getPlayerRow();
        int y = map.getPlayerCol();
        actionWasMoving = false;
        openedDoorWithKey = false;
        turns++;
        //display the action menu & get the space type
        //display a warning if any of the players (except the first one) fullness is 0 or less
        for(int i = 1; i < 5; i++)
        {
            if(players[i].getFullness() <= 0 && players[i].isPlayerDead() == false)
            {
                cout << "Warning: " << players[i].getName() << "'s fullness is 0 or less!" << endl;
                cout << "They will die if you do not feed them this turn!" << endl;
            }
        }
        spaceType = menu.displayActionMenu(map);
        //get the action choice
        cin >> userChoiceString;
        if(isdigit(userChoiceString[0]))
        {
            userChoice = stoi(userChoiceString, 0);
        }
        else{
            userChoice = -1;
        }
        //handle normal space type
        if(spaceType == 0)
        {
            //make sure its a valid choice and re-prompt if not 
            while(userChoice < 1 || userChoice > 5)
            {
                cout << "Please enter a valid choice: " << endl;
                cin >> userChoiceString;
                if(isdigit(userChoiceString[0]))
                {
                    userChoice = stoi(userChoiceString, 0);
                }
                else{
                    userChoice = -1;
                }
            }
            if(userChoice == 5)
            {
                cout << "You have chosen to give up. Thanks for playing!" << endl;
                gameRunning = false;
                break;
            }
            if(map.isExplored(x, y)== true && userChoice == 2)
            {
                cout << "You have already explored this space. Please choose another action." << endl;
                cin >> userChoice;
                break;
            }
            //handle the choice
            switch(userChoice)
            {
                case 1:
                    //move
                {
                    char moveInput;
                    cout << "Please enter the direction you would like to move (w, a, s, d): " << endl;
                    cin >> moveInput;
                    bool result = map.move(moveInput);
                    while(!result)
                    {
                        cout << "Please enter a valid direction (w, a, s, d): " << endl;
                        cin >> moveInput;
                        result = map.move(moveInput);
                        prob.handleMoving(players);
                    }
                    actionWasMoving = true;
                    break;
                }
                //investigate the space
                case 2:
                {
                    bool fightMonster = prob.handleInvestigation(map,players,roomsCleared,merchant);
                    spacesExplored++;
                    if(fightMonster)
                    {
                        bool result = prob.fightMonster(players, monsters, roomsCleared, merchant);
                        if(result)
                        {
                            monstersDefeated++;
                        }
                    }
                    break;                     
                }
                case 3:
                {
                    bool result = prob.fightMonster(players, monsters, roomsCleared, merchant);\
                    if(result)
                    {
                        monstersDefeated++;
                    }
                    break;
                }
                case 4:
                {
                    prob.handleCooking(players, merchant);
                    break;
                }
                //no need for a case 5 because it is handled above
            }
        }
        //space is a room space
        //random notes for myself:
        // 1. once they clear the room, we should get rid of all monsters below the level of the room number + 1
        else if(spaceType == 1)
        {
            //make sure its a valid choice and re-prompt if not
            while(userChoice < 1 || userChoice > 3)
            {
                cout << "Please enter a valid choice: " << endl;
                cin >> userChoice;
            }
            //check if they quit first
            if(userChoice == 3)
            {
                cout << "You have chosen to give up. Thanks for playing!" << endl;
                menu.printEndingOfGame(players, roomsCleared, merchant, spacesExplored, turns, monstersDefeated, false); 
                gameRunning = false;
                break;
            }
            switch(userChoice)
            {
                case 1:
                //move
                {
                    char moveInput;
                    cout << "Please enter the direction you would like to move (w, a, s, d): " << endl;
                    cin >> moveInput;
                    bool result = map.move(moveInput);
                    while(!result)
                    {
                        cout << "Please enter a valid direction (w, a, s, d): " << endl;
                        cin >> moveInput;
                        result = map.move(moveInput);
                        prob.handleMoving(players);
                    }
                    actionWasMoving = true;
                    break;
                }
                case 2:
                //open the door
                {
                    //check if they have a key
                    if(merchant.getKeys() > 0)
                    {
                        merchant.changeKeys(-1);
                        openedDoorWithKey = true;
                        cout << "You have opened the door with a key!" << endl;

                        //fight a monster that is 2 levels higher than the room number, we add one here because the function already adds one
                        bool result = prob.fightMonster(players, monsters, roomsCleared+1, merchant);
                        //if the player wins the fight, there is a 60% chance of misfortune, so we will need to roll a random number
                        if(result)
                        {
                            prob.handleMisfortuneAfterMonster(players, true, merchant);
                            roomsCleared++;
                            monstersDefeated++;
                            spacesExplored++;
                            //remove the room from the map
                            map.removeRoom(x,y);
                        }
                        else
                        {
                            prob.handleMisfortuneAfterMonster(players, false, merchant);
                            cout << endl;
                            cout << "You failed to open the door. You will need to find another way to open it." << endl;
                            cout << endl;
                        } 

                    }   
                    else
                    {
                        bool result = merchant.handleRpsDoorPuzzle(players);
                        if(result)
                        {
                            //fight a monster that is 2 levels higher than the room number, we add one here because the function already adds one
                            bool result2 = prob.fightMonster(players, monsters, roomsCleared+1, merchant);
                            if(result2)
                            {
                                prob.handleMisfortuneAfterMonster(players, true, merchant);
                                monstersDefeated++;
                                roomsCleared++;
                                spacesExplored++;
                                //remove the room from the map
                                map.removeRoom(x,y);
                            }
                        }
                    }
                }
            }
        }
        //space is an NPC
        else if(spaceType == 2)
        {
            //make sure its a valid choice and re-prompt if not
            while(userChoice < 1 || userChoice > 3)
            {
                cout << "Please enter a valid choice: " << endl;
                cin >> userChoice;
            }
            //check if they quit first
            if(userChoice == 3)
            {
                cout << "You have chosen to give up. Thanks for playing!" << endl;
                menu.printEndingOfGame(players, roomsCleared, merchant, spacesExplored, turns, monstersDefeated, false); 
                gameRunning = false;
                break;
            }
            switch(userChoice)
            {
                case 1:
                //move
                {
                    char moveInput;
                    cout << "Please enter the direction you would like to move (w, a, s, d): " << endl;
                    cin >> moveInput;
                    bool result = map.move(moveInput);
                    while(!result)
                    {
                        cout << "Please enter a valid direction (w, a, s, d): " << endl;
                        cin >> moveInput;
                        result = map.move(moveInput);
                        prob.handleMoving(players);
                    }
                    actionWasMoving = true;
                    break;
                }
                case 2:
                //speak to NPC (merchant)
                {
                    bool result = merchant.handleRiddle(riddleQuestions, riddleAnswers);
                    if(result)
                    {
                        merchant.increasePriceByRoomsCleared(roomsCleared);
                        merchant.handleInteraction(players);
                        spacesExplored++;
                    }
                    else
                    {
                        //user failed the riddle, so they have to fight a monster
                       bool result = prob.fightMonster(players, monsters, roomsCleared, merchant);
                       if(result)
                       {
                            monstersDefeated++;
                       }
                    }
                    //mark the space as explored
                    map.exploreSpace(x, y);
                    spacesExplored++;
                }
            }
        }
        //exit
        else if(spaceType == 3)
        {
         //check the win condition
            if(roomsCleared == 5 && players[0].numPlayersAlive(players) > 1)
            {
                //player will fight the boss (Sorcerer)
                bool result = prob.fightMonster(players, monsters, roomsCleared, merchant);
                //either way, the game is over
                menu.printEndingOfGame(players, roomsCleared, merchant, spacesExplored, turns, monstersDefeated, result);                
            }
        }
        //increase sorcerer level when they move to a non explored space.
        if(actionWasMoving && !map.isExplored(x, y))
        {
            sorcererLevel++;
        }
        //check if the game is over
        //game is instantly over if the player (main character) dies
        if(players[0].getFullness() == 0)
        {
            cout << "Your fullness reached 0. You have died. Thanks for playing!" << endl;
            menu.printEndingOfGame(players, roomsCleared, merchant, spacesExplored, turns, monstersDefeated, false);     
            gameRunning = false;
        }
        //game is over if the sorcerer level is 100
        if(sorcererLevel == 100)
        {
            cout << "The sorcerer got too angry and destroyed the dungeon. You have failed to escaped. Thank you for playing." << endl;
            menu.printEndingOfGame(players, roomsCleared, merchant, spacesExplored, turns, monstersDefeated, false);     
            gameRunning = false;
        }

        //check if the player's party members have less than 0 fullness
        for(int i = 1; i < 5; i++)
        {
            if(players[i].getFullness() <= 0 && !players[i].isPlayerDead())
            {
                cout << players[i].getName() << " has died." << endl;
                players[i].setDead();
                //check to see the number of party members left and weapons left too
                //make sure the number of weapons is equal to the number of players or else we shouldn't take a weapon away
                if(players[0].numPlayersAlive(players) > merchant.getNumWeapons())
                {
                    prob.removeRandomWeapon(players, merchant);
                }
            }
        }
        //do things after the players choice (check end conditions, etc)
        //check if a player is dead here, a few notes about that:
        //1 - if a player is dead, their index of weapons 0
        //misfortunes should be handled here
        if(!actionWasMoving)
        {
            prob.handleMisfortune(players, openedDoorWithKey, merchant);
        }
        //before we display status update, handle the resurrection of players.
        //check if any players are dead
        if(!resurrected)
        {
            for(int i = 0; i < 5; i++)
            {
                if(players[i].isPlayerDead())
                {
                    cout << "It looks like " << players[i].getName() << " is dead. Would you like to resurrect them? (y/n)" << endl;
                    cout << "Note: This will take 20 fullness from everyone else, and will resurrect " << players[i].getName() << " with 40 fullness" << endl;
                    cout << "You can only resurrect a player once." << endl;
                    cout << endl;
                    cout << endl;
                    cout << "⚠️ ⚠️ ⚠️ Warning, if any of your party members have less than 20 fullness, they will die. ⚠️ ⚠️ ⚠️" << endl;
                    cout << endl;
                    cout << endl;
                    cout << "Would you like to resurrect " << players[i].getName() << "? (y/n)" << endl;
                    string answer;
                    cin >> answer;
                    while(answer[0] != 'y' && answer[0] != 'y')
                    {
                        cout << "Please enter a valid answer (y/n): " << endl;
                        cin >> answer;
                    }
                    if(answer[0] == 'y')
                    {
                        resurrected = true;
                        //resurrect the player, and take 20 fullness from everyone else
                        players[i].setAlive();
                        //i is the player that was resurrected, so we skip them when we take 20 fullness from everyone else
                        //take 20 fullness from everyone else
                        for(int j = 0; j < 5; j++)
                        {
                            if(j != i)
                            {
                                players[j].setFullness(players[j].getFullness() - 20);
                                //check if the player died
                                if(players[j].getFullness() <= 0)
                                {
                                    cout << players[j].getName() << " died when resurrecting " << players[i].getName() << "." << endl;
                                    players[j].setDead();
                                    //check to see the number of party members left and weapons left too
                                    //make sure the number of weapons is equal to the number of players or else we shouldn't take a weapon away
                                    if(players[0].numPlayersAlive(players) > merchant.getNumWeapons())
                                    {
                                        prob.removeRandomWeapon(players, merchant);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        //display status update
        menu.displayStatusUpdatePart1(sorcererLevel, merchant.getKeys(), roomsCleared);
        merchant.displayInventoryMenu();
        menu.displayStatusUpdatePart2(map, players);
    }
    return 0;
}