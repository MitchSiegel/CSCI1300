#include <iostream>
#include <cassert>
using namespace std;

/*
    Thi function takes in an input text string, and will count the number of times each character appears in the string.
    It will then return the number of times each character appears in the string and how many times each character appears.
*/
int charCount(string input_text)
{
    //define the array that will hold the number of times each character appears, it is 52 because there are 26 lowercase and 26 uppercase letters.
    int char_count[52] = {0};
    //define the unique character count
    int unique_count = 0;
    //loop through the input text
    for(int i = 0; i < input_text.length(); i++)
    {
        //if the character is an uppercase letter
        if(input_text[i] >= 'A' && input_text[i] <= 'Z')
        { 
            char_count[input_text[i] - 'A']++;
        }
        //if the character is a lowercase letter
        else if(input_text[i] >= 'a' && input_text[i] <= 'z')
        {
            char_count[input_text[i] - 'a' + 26]++;
        }
    }
    //count the number of unique characters
    for(int i = 0; i < 52; i++)
    {  
        //if the character appears at least once add one to the unique count
        if(char_count[i] > 0)
        {
            unique_count++;
            //print the character and the number of times it appears
            if(i < 26)
            {
                cout << char(i + 'A') << ": " << char_count[i] << endl;
            }
            else
            {
                //if the character is lowercase, add 26 to the index to get the correct character
                cout << char(i + 'a' - 26) << ": " << char_count[i] << endl;
            }
        }
    }
    //return the number of unique characters
    return unique_count;
}

int main()
{
    string text_input = "Colorado";
    // num_chars will store the values returned by charCount
    int num_chars = charCount(text_input);
    cout << "Unique characters: " << num_chars << endl;
}