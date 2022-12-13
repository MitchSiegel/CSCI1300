------------------------
HOW TO COMPILE AND RUN
------------------------
Compile: g++ main.cpp map.cpp menu.cpp merchant.cpp monster.cpp player.cpp probability.cpp --std=c++17 -o main
Run: ./main
------------------------
DEPENDENCIES
------------------------
Map.h, Merchant.h, Player.h, Menu.h, Monster.h and probability.h need to be in the root directory for this to compile correctly.
------------------------
SUBMISSION INFORMATION
------------------------
CSCI 1300 Fall 2022
Author: Mitch Siegel
Recitation: 201 – Elise Tate
Project 3
------------------------
ABOUT THIS PROJECT
------------------------
The base game is a dungeon escape game where the objective is to escape the dungeon, but with a set of challenges along the way.
When you are first placed in the dungeon, you are given 100 gold, and taken to the first Merchant, or an NPC.
You are given a chance to buy items at a non inflated price, because the price of the merchant increases by 25% for every room you clear. 
After the first merchant visit, you are put on the map, and given access to the controls, where you can move around freely
You can explore open spaces in hopes to find a merchant, or to find a key to a door. Occasional you will find a monster when exploring a space.
The goal of the game is to explore the dungeon until you clear the rooms, which is done by fighting a monster 2 levels higher than the number of rooms cleared.
The final part of the game is beating the sorcerer, which is a custom battle with two stages.