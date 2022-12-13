//cardGame.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 7 - Problem 3

#include <iostream>
#include <vector>
using namespace std;


int main()
{
    vector<int> cards;
    int counter = 0;
    int card;
    //loop until the card is 14 (the joker, which ends the game.)
    while (card != 14)
    {
        //get user card
        cout << "Please enter a number: " << endl;
        cin >> card;
        //make sure the card is valid
        if (card < 1 || card > 14)
        {
            cout << "The number should be an integer between 1 and 14." << endl;
        }
        else
        {
            //if the card is valid, add it to the vector
            cards.push_back(card);
            //handle the card value now.
            //if the card is one, remove the last two cards in the vector (unless there is only 1 card in the vector)
            if (card == 1)
            {

                if (cards.size() == 1)
                {
                    cards.erase(cards.begin());
                    counter++;
                }
                else
                {
                    cards.erase(cards.begin());
                    cards.erase(cards.begin());
                    counter += 2;
                }
            }
            //if the card is 11,12,13
            else if (card == 11 || card == 12 || card == 13)
            {
                if (cards.size() == 1)
                {
                    cards.erase(cards.begin());
                    counter++;
                }
                else
                {
                    cards.pop_back();
                    cards.pop_back();
                    counter += 2;
                }
            }
            else if (card == 14)
            {
                cards.pop_back();
            }
        }
    }
    cout << "Your remaining cards are: ";
    for (int i = 0; i < cards.size(); i++)
    {
        cout << cards[i] << " ";
    }
    cout << endl;
    cout << "I have " << counter << " card(s)." << endl;
    if (counter > cards.size())
    {
        cout << "I win!" << endl;
    }
    else if (counter < cards.size())
    {
        cout << "You win!" << endl;
    }
    else
    {
        cout << "Tie!" << endl;
    }
    return 0;
}