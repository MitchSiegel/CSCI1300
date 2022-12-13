//testMe.cpp

// CSCI 1300 Fall 2022
// Author: Mitch Siegel
// Recitation: 201 – Elise Tate
// Homework 5 - Problem # ?

#include <iostream> 
#include <cassert>
using namespace std;


/*
 * Taken from the github for homework 5.
*/
int zeroesToFives(int arr[], int arr_size)
{
	int count = 0;
	//loops through input array
	for(int i = 0; i < arr_size; i++) 
	{ 
		if(arr[i] == 0) //if an element is zero, set it to five
		{ 
    			arr[i] = 5; 
                count++;
		}
	}
	return count;
}

int main()
{
    //Test 1: testing to make sure single arrays work.
    int array_test_1[] = {0};
    zeroesToFives(array_test_1,1);

    assert(array_test_1[0] == 5);

    //test 2: testing to make sure repeated zeros work
    int array_test_2[] = {0,0,0,0,0,1};
    zeroesToFives(array_test_2,6);

    assert(array_test_2[0] == 5);
    assert(array_test_2[4] == 5);
    assert(array_test_2[5] == 1);

    //test 3: testing to make sure it doesn't change values it shouldn't
    int array_test_3[] = {0,0,6,7,5,0};
    zeroesToFives(array_test_3,6);

    assert(array_test_3[2] == 6);
    assert(array_test_3[3] == 7);
    assert(array_test_3[4] == 5);

    //test 4: testing to make sure function works with single arrays that aren't zero.
    int array_test_4[] = {4};
    zeroesToFives(array_test_4,1);

    assert(array_test_4[0] == 4);

    //test 5: testing to just make sure it works
    int array_test_5[7] = {45,3,63,0,652,0,1};
    zeroesToFives(array_test_5,7);

    assert(array_test_5[4] == 652);
    assert(array_test_5[0] == 45);

    //test 6: making sure that numbers with zeros in them don't get changed to 5
    int array_test_6[4] = {450,3,0,105};
    zeroesToFives(array_test_6,4);

    assert(array_test_6[0] == 450);
    assert(array_test_6[3] == 105);

    //test 7: testing to make sure that the function works with negative numbers
    int array_test_7[4] = {-450,3,0,-105};
    zeroesToFives(array_test_7,4);

    assert(array_test_7[0] == -450);
    assert(array_test_7[3] == -105);

    //test 8: more negative numbers tests
    int array_test_8[4] = {-650,3,0,-521};
    zeroesToFives(array_test_8,4);

    assert(array_test_8[0] == -650);
    assert(array_test_8[3] == -521);

    //test 9: testing to make sure that the function doesn't work with doubles (converts to int)
    int array_test_9[4] = {-650.5,3,0,-521};
    zeroesToFives(array_test_9,4);

    assert(array_test_9[0] == -650);

    //final test: make sure it doesn't crash with an empty array. No assert needed.
    int array_test_10[0] = {};
    zeroesToFives(array_test_10,0);

    return 0;
}