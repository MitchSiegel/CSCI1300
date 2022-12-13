//potionCrafting.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 4 - Problem # 3

#include <iostream>
using namespace std;
/*
    This program will calculate the number of potions that can be made from various ingredients.
    It will ask the user which potion they want to prioritize, and then calculate the number of potions that can be made of that type.
    It will then calculate the number of potions that can be made of the other type.
    It will ask the user to input the number of ingredients they have and then calculate the number of potions that can be made.
    The program will make sure the user inputs all valid numbers, and will ask them to re-enter the number if it is invalid.
    Finally, it will output the number of mana or health potions that can be made. (The potion they prioritized will be calculated first.)
*/
int main(){
    //declare variables
    int preferred_potion, honeycombs, dandelions, coal, toadstools = 0;
    int minor_healing_potions = 0;
    int minor_mana_potions = 0;
    bool has_valid_input = false;
    //repeat until the user inputs a valid number of which potion they want to prioritize
    while(!has_valid_input)
    {
        cout << "Select a potion crafting priority:\n1. Minor Mana\n2. Minor Healing" << endl;
        cin >> preferred_potion;
        if(preferred_potion == 1 || preferred_potion == 2)
        {
            has_valid_input = true;
        }
        else
        {
            cout << "Invalid input." << endl;
        }
    }
    //reset the input validation variable
    has_valid_input = false;
    //repeat until the user inputs a valid number of honeycombs
    while(!has_valid_input)
    {
        cout << "How many Honeycombs do you have?" << endl;
        cin >> honeycombs;
        if(honeycombs >= 0)
        {
            has_valid_input = true;
        }
        else
        {
            cout << "Invalid input. ";
        }
    }
    //reset the input validation variable
    has_valid_input = false;
    //repeat until the user inputs a valid number of dandelions
    while(!has_valid_input)
    {
        cout << "How many Dandelions do you have?" << endl;
        cin >> dandelions;
        if(dandelions >= 0)
        {
            has_valid_input = true;
        }
        else
        {
            cout << "Invalid input. ";
        }
    }
    //reset the input validation variable
    has_valid_input = false;
    //repeat until the user inputs a valid number of coal
    while(!has_valid_input)
    {
        cout << "How many Coal do you have?" << endl;
        cin >> coal;
        if(coal >= 0)
        {
            has_valid_input = true;
        }
        else
        {
            cout << "Invalid input. ";
        }
    }
    //reset the input validation variable
    has_valid_input = false;
    //repeat until the user inputs a valid number of toadstools
    while(!has_valid_input)
    {
        cout << "How many Toadstools do you have?" << endl;
        cin >> toadstools;
        if(toadstools >= 0)
        {
            has_valid_input = true;
        }
        else
        {
            cout << "Invalid input. ";
        }
    }
    //begin calculations
    //minor health potions: 5 honeycombs, 0 dandelions, 2 coal, 3 toadstools
    //minor mana potions: 5 honeycombs, 3 dandelions, 1 coal, 0 toadstools
    //if the user wants to prioritize minor mana potions
    if(preferred_potion ==  1)
    { 
        //calculate minor mana potions first (since they are prioritized)
        while(honeycombs >= 5 && dandelions >= 3 && coal >= 1)
        {
            honeycombs = honeycombs - 5;
            dandelions = dandelions - 3;
            coal = coal - 1;
            minor_mana_potions = minor_mana_potions + 1;
        }
        //calculate minor health potions second (since they are not prioritized)
        while(honeycombs >= 5 && coal >= 2 && toadstools >= 3)
        {
            honeycombs = honeycombs - 5;
            coal = coal - 2;
            toadstools = toadstools - 3;
            minor_healing_potions = minor_healing_potions + 1;
        }
        //output the results
        cout << "You can make " << minor_mana_potions << " Mana potion(s) and " << minor_healing_potions << " Healing potion(s)." << endl;
    }
    //if the user wants to prioritize minor health potions
    else
    {
        //calculate minor health potions first (since they are prioritized)
        while(honeycombs >= 5 && coal >= 2 && toadstools >= 3)
        {
            honeycombs = honeycombs - 5;
            coal = coal - 2;
            toadstools = toadstools - 3;
            minor_healing_potions = minor_healing_potions + 1;
        }
        //calculate minor mana potions second (since they are not prioritized)
        while(honeycombs >= 5 && dandelions >= 3 && coal >= 1)
        {
            honeycombs = honeycombs - 5;
            dandelions = dandelions - 3;
            coal = coal - 1;
            minor_mana_potions = minor_mana_potions + 1;
        }
        //output the results
        cout << "You can make " << minor_healing_potions << " Healing potion(s) and " << minor_mana_potions << " Mana potion(s)." << endl;
    }

    return 0;
}