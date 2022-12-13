//menu.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 3

#include "Menu.h"
#include "Map.h"
#include "Player.h"
#include "Merchant.h"
#include "Monster.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


Menu::Menu()
{
    //Might need later but not now
}

/*
 * menu.cpp contains the implementation of the Menu class.
 * The menu class handles the display of the action menu, and the status update.
 * It will basically handle the cout's if the are longer than one line, and re-occur during the game.
 * it also handles the final status update, and the saving and displaying of the high scores.
*/


/*
 * The setUpUsers functions handles the setting up of the users' names.
 * It handles all of the input and setting of the users' info.
*/
void Menu::setupUsers(Player players[5])
{
    cout << "Welcome to the game!" << endl;
    cout << "We just need to setup a few things to get started!" << endl;
    cout << "Please enter the name of your main character: " << endl;
    string mainName;
    cin >> mainName;
    players[0].setName(mainName);
    int numParty;
    string partyName;
    for(int i = 0; i < 4; i++)
    {
        cout << "Please enter the name of your party member " << i + 1 << ": " << endl;
        cin >> partyName;
        players[i + 1].setName(partyName);
    }
}

/*
 * displayStatusUpdatePart1 handles printing out the first part of the status update.
 * the status update is split into three parts, and the merchant handles printing out the inventory (second part).
*/
void Menu::displayStatusUpdatePart1(int sorcererLevel, int keys, int roomsCleared)
{
    cout << "+-------------+" << endl; 
    cout << "|   STATUS    |" << endl;
    cout << "+-------------+" << endl;
    cout << "| Rooms Cleared: " << roomsCleared << " | Keys: " << keys << " | Anger Level: " << sorcererLevel << endl;

}
/*
 * displayStatusUpdatePart2 handles printing out the third part of the status update.
 * This function prints out the players' names, fullness, and if they are dead or not. 
 * It will also print out the map.
*/
void Menu::displayStatusUpdatePart2(Map map, Player players[5])
{
    cout << "|    PARTY    |" << endl;
    cout << "+-------------+" << endl;
    for(int i = 0; i < 5; i++)
    {
        string isPlayerDead = "";
        if(players[i].isPlayerDead())
        {
            //adds a "☠️" to the start of the name if the player is dead
            isPlayerDead = "☠️  ";
        }
        cout << "| " << isPlayerDead << players[i].getName() << " | Fullness: " << players[i].getFullness() << endl;
    }
    cout << "+-------------+" << endl;
    cout << endl;
    map.displayMap();
    cout << endl;
    cout << "+-------------+" << endl;
    
}

/*
 * displayActionMenu handles the printing of the action menu.
 * It has return codes that will tell the main function what type of space the player is currently on.
 * 0 = free space, 1 = room, 2 = npc, 3 = dungeon exit.
 * It will also print out the available actions for the player.
*/
int Menu::displayActionMenu(Map &map)
{
    int x = map.getPlayerRow();
    int y = map.getPlayerCol();
    bool isFree = map.isFreeSpace(x, y);
    if(!isFree)
    {
        //space is not free, so its either a room or an NPC, so we need to check
        if(map.isRoomLocation(x, y))
        {
            cout << "Select one:" << endl;
            cout << "1. Move" << endl;
            cout << "2. Open the Door" << endl;
            cout << "3. Give up" << endl;
            cout << endl;
            return 1;
        }
        if(map.isNPCLocation(x, y))
        {
            cout << "Select one:" << endl;
            cout << "1. Move" << endl;
            cout << "2. Speak to NPC" << endl;
            cout << "3. Give Up" << endl;
            cout << endl;
            return 2;
        }
        if(map.isDungeonExit(x,y))
        {
            //printing is handled by the main function here
            return 3;
        }
    }
    else
    {
        cout << "Select one:" << endl;
        cout << "1. Move" << endl;
        if(map.isExplored(x, y))
        {
            cout << "2. Investigate (this option is not available as the space has already been explored)" << endl;
        }
        else
        {
            cout << "2. Investigate" << endl;
        }
        cout << "3. Pick a Fight" << endl;
        cout << "4. Cook and Eat" << endl;
        cout << "5. Give up" << endl;
        cout << endl;
    
        return 0;
    }
    //should never get here, but just in case
    return -1;
}

/*
 * printEndingOfGame takes in almost all of the game's variables, and prints out the ending of the game.
 * It handles the final stats printing and will save the results to a file.
 * It will also print out the high scores and the current player's score and rank.
*/
void Menu::printEndingOfGame(Player players[5],int roomsCleared, Merchant &merchant, int spacesExplored, int turns, int monstersDefeated, bool won)
{
    if(won)
    {
        cout << "+----------------------------------------------+" << endl;
        cout << "|                     🎉🎉                      |" << endl;
        cout << "|   You have escaped the dungeon, well done!   |" << endl;
        cout << "|                     🎉🎉                      |" << endl;
        cout << "+----------------------------------------------+" << endl;
    }
    else
    {
        cout << "+------------------------------------------------------+" << endl;
        cout << "|                            🪦🪦                       |" << endl;
        cout << "|   You have failed to escape the dungeon. Game over.  |" << endl;
        cout << "|                            🪦🪦                       |" << endl;
        cout << "+------------------------------------------------------+" << endl;

    }
    cout << endl;
    cout << endl;
    cout << "+-------------------------+" << endl;
    cout << "|         STATS           |" << endl;
    cout << "+-------------------------+" << endl;
    cout << "| Rooms Cleared: " << roomsCleared << endl; 
    cout << "| Spaces Explored: " << spacesExplored << endl;
    cout << "| Turns Taken: " << turns << endl;
    cout << "| Monsters Defeated: " << monstersDefeated << endl;
    cout << "| Treasure Items Left: " << merchant.getTotalTreasure() << endl;
    cout << "| Gold Left: " << merchant.getGold() << endl;
    //need to print out the players name and their fullness
    cout << "| Party Members remaining: " << endl;
    for(int i = 0; i < 5; i++)
    {
        if(!players[i].isPlayerDead())
        {
            cout << "| " << players[i].getName() << " | Fullness: " << players[i].getFullness() << endl;
        }
    }
    cout << "+-------------------------+" << endl;
    cout << endl;

    //print out "Game Made by Mitch Siegel"
    cout << endl;
    cout << "+-------------------------------------+" << endl;
    cout << "|      Game Made by Mitch Siegel      |" << endl;
    cout << "+-------------------------------------+" << endl;
    cout << endl;
    cout << endl;

    //save the results to a file
    ofstream outputFile;
    outputFile.open("results.txt");
    
    //save the results in just a single line of text, separated by commas, without any spaces
    //this will make it easier to read the results in the main function
    //the results will be in the order of: roomsCleared, spacesExplored, turns, monstersDefeated, treasureItemsLeft, goldLeft, won, the party leaders first name
    outputFile << roomsCleared << "," << spacesExplored << "," << turns << "," << monstersDefeated << "," << merchant.getTotalTreasure() << "," << merchant.getGold() << "," << won << endl;
    outputFile.close();
    cout << "Results have been saved to results.txt" << endl;

    int score = 0;
    //score is based on the number of rooms cleared, the number of spaces explored, the number of monsters defeated, and the number of turns taken
    score += roomsCleared * 100;
    score += spacesExplored * 10;
    score += monstersDefeated * 50;
    score += turns * 5;
    score += merchant.getGold() * 2;
    score += players[0].numPlayersAlive(players) * 100;
    //if the player won, add 1000 points to the score
    if(won)
    {
        score += 1000;
    }
    //add their score to the leaderboard (file called score.txt), and sort the score, so the highest score is at the top
    //line format: score, name
    //we should also print out what place they got on the leaderboard
    ifstream inputFile;
    inputFile.open("./data/score.txt");
    //create a vector of strings, where each string is a line from the file
    vector<string> lines;
    string line;
    while(getline(inputFile, line))
    {
        lines.push_back(line);
    }
    inputFile.close();
    //add the new score to the vector
    lines.push_back(to_string(score) + "," + players[0].getName());
    //sort the vector by using a bubble sort
    string splitLine[2];
    //initial loop to go through all of the lines
    for(int i = 0; i < lines.size(); i++)
    {
        //secondary loop to compare the current line to the next line
        for(int j = 0; j < lines.size() - 1; j++)
        {
            //get the score of the current line
            string currentLine = lines[j];
            //the find function will return the index of the first comma, which is where the score ends and the name begins
            int currentScore = stoi(currentLine.substr(0, currentLine.find(",")));
            //get the score of the next line
            string nextLine = lines[j + 1];
            int nextScore = stoi(nextLine.substr(0, nextLine.find(",")));
            //if the current score is less than the next score, swap the two lines
            if(currentScore < nextScore)
            {
                string temp = lines[j];
                lines[j] = lines[j + 1];
                lines[j + 1] = temp;
            }
        }
    }
    //print out the leaderboard
    cout << endl;
    cout << "+-------------------------------------+" << endl;
    cout << "|               LEADERBOARD           |" << endl;
    cout << "+-------------------------------------+" << endl;
    for(int i = 0; i < lines.size(); i++)
    {
        //split the line into the score and the name
        string currentLine = lines[i];
        splitLine[0] = currentLine.substr(0, currentLine.find(","));
        splitLine[1] = currentLine.substr(currentLine.find(",") + 1);
        //handles the placement of the score
        if(splitLine[1] == players[0].getName()){
            cout << "| " << i + 1 << ". " << splitLine[1] << " - " << splitLine[0] << " points" << " (YOU)" << endl;
        }
        else{
            cout << "| " << i + 1 << ". " << splitLine[1] << " - " << splitLine[0] << " points" << endl;
        }
    }
    cout << "+-------------------------------------+" << endl;
    cout << endl;

    //save the leaderboard to the file
    ofstream outputFile2;
    outputFile2.open("./data/score.txt");
    //loop through the vector and save each line to the file
    for(int i = 0; i < lines.size(); i++)
    {
        outputFile2 << lines[i] << endl;
    }
}