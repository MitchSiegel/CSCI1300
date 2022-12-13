// Aquarium.h

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 9 - Supporting File

#include <string>
#include <vector>
using namespace std;

//This file contains the fish struct and the aquarium class

// Fish class (struct because it only has public members)
struct Fish
{
    string name;
    int gallons_required;
};

// Aquarium class
class Aquarium
{
    private:
    // private members
        string aquarist_name; // name of the aquarist
        static const int tank_size_gallons = 12; // tank size in gallons (always 12)
        int gallons_used; // gallons used by the fish in the tank (starts at 0)
        vector<Fish> available_fish; // vector of Fish objects that are available to add to the tank
        vector<Fish> selected_fish; // vector of Fish objects that are currently in the tank
    public:
        Aquarium(string name); // constructor, sets aquarist_name to name, gallons_used to 0
        string getAquaristName(); // returns aquarist_name
        int getGallonsUsed(); // returns gallons_used
        bool loadFish(string file_name); // loads fish from file_name into available_fish, returns true if successful, false otherwise
        void displayAvailableFish(); // displays the names of the fish in available_fish
        int addFish(string fish_name); // adds fish_name to selected_fish if it is in available_fish, returns the gallons required by the fish, -1 if fish_name is not in available_fish
        bool removeFish(string fish_name); // removes fish_name from selected_fish if it is in selected_fish, returns true if successful, false otherwise
        bool writeAquariumContents(string file_name); // writes the names of the fish in selected_fish to file_name, returns true if successful, false otherwise
};