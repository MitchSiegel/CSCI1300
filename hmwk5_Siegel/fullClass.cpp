//fullClass.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 5 - Problem # 5

#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;

int fullClass(bool classroom[][4],int rows,int waitlist)
{
    int empty_space = 0;
    int spaces_left = waitlist;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(classroom[i][j] == 0){
                empty_space++;
                if(spaces_left > 0){
                    classroom[i][j] = 1;
                    spaces_left--;
                }
            }
            cout << classroom[i][j];
        }
        cout << endl;
    }
    cout << "Remaining Students: " << spaces_left << endl;
    return spaces_left;
}

int main()
{
	
    bool classroom[3][4] = {{0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0}};
    int waitlist = 9;
    fullClass(classroom, 3, waitlist);
    /* paste here */
    return 0;
}