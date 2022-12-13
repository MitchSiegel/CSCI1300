//sumElements.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 7 - Problem 1

#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;
/*
* sumElements.cpp contains the function sumElements, which takes in a vector of integers, a start index, and an end index.
* The function will return the sum of all the elements in the vector. (unless there is an error)
*/


/*
 * the sumElements function takes in a vector of ints, a start index, and an end index.
 * if the start index is greater than the end index, the function will return -1.
 * if either index is out of bounds of the vector, it will return -2.
 * if everything else works, it will return the sum of the elements between the start index and the end index.
*/
int sumElements(vector <int> vec,int start_index, int end_index)
{

    int sum = 0;
    //if the start of the vector is greater than the end, return -1
    if (start_index > end_index)
    {
        return -1;
    }
    //if the start of the vector is less than zero, or if the vector size 
    else if (start_index < 0 || end_index > vec.size() - 1)
    {
        return -2;
    }
    else
    {
        //add the elements of the vector from the start index to the end index
        for (int i = start_index; i <= end_index; i++)
        {
            sum += vec[i];
        }
        //return the value of the sum
        return sum;
    }
}

int main()
{
    
    //test 1 - normal testing
    vector<int> vect1{10, 20, 30, 40, 50};
    int start_index = 1, end_index = 3;
    int result =  sumElements(vect1, start_index, end_index); 
    assert(result == 90);

    //test 2 - start index is greater than end index
    vector<int> vect2{50, 20, 30, 40, 10};
    int start_index2 = 5, end_index2 = 0;
    int result2 =  sumElements(vect2, start_index2, end_index2);
    assert(result2 == -1);

    //test 3 - start index is less than 0
    vector<int> vect3{50, 20, 30, 40, 10};
    int start_index3 = -1, end_index3 = 5;
    int result3 =  sumElements(vect3, start_index3, end_index3);
    assert(result3 == -2);

    return 0;
}