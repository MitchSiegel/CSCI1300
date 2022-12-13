//classDriver.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Project 3

#include "Menu.h"
#include "Map.h"
#include "Player.h"
#include "Monster.h"
#include "Probability.h"
#include "Merchant.h"
#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

int main()
{
    //test the player class
    Player player1;
    player1.setName("Mitch");
    assert(player1.getName() == "Mitch");
    player1.setFullness(100);
    assert(player1.getFullness() == 100);
    player1.changeFullness(-75);
    assert(player1.getFullness() == 25);
    player1.setDead();
    assert(player1.isPlayerDead() == true);
    assert(player1.getFullness() == 0);
    
    //test the monster class
    vector<Monster> monsters;
    Monster monster1;
    monster1.fillArray(monsters);
    assert(monsters.size() == 32);
    assert(monsters[0].getName() == "Animated Armor");
    assert(monsters[31].getName() == "Sorcerer");

    //test the probability class
    Probability prob;
    Map map;
    prob.generateRandomPlacement(map);
    assert(map.getRoomCount() == 5);

    //test the merchant class
    Merchant merchant;
    assert(merchant.getKeys() == 0);
    merchant.changeKeys(5);
    assert(merchant.getKeys() == 5);
    merchant.changeKeys(-3);
    assert(merchant.getKeys() == 2);
    cout << merchant.getArmor() << endl;
    assert(merchant.getArmor() == 0);
    merchant.changeArmor(5);
    assert(merchant.getArmor() == 5);
    merchant.changeArmor(-3);
    assert(merchant.getArmor() == 2);
    cout << merchant.getWeaponsByIndex(0) << endl;
    assert(merchant.getWeaponsByIndex(0) == 0);
    merchant.changeWeaponsByIndex(0, 1);
    assert(merchant.getWeaponsByIndex(0) == 1);
    merchant.changeWeaponsByIndex(0, -1);
    assert(merchant.getWeaponsByIndex(0) == 0);

    //test the menu class
    Menu menu;
    //Expected output:
    /*
    +-------------+
    |   STATUS    |
    +-------------+
    | Rooms Cleared: 0 | Keys: 0 | Anger Level: 0
    */
    menu.displayStatusUpdatePart1(0, 0, 0);
}