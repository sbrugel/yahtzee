#include <array>
#include <iostream>
#include "GameState.hpp"
#include "DiceManager.hpp"
#include "ChipManager.hpp"
using namespace std;

/*
* Checks if "sub" is a sub-array of "parent"
*/
bool GameState::isSubArray(int sub[], int parent[], int sublen, int parentlen) {
    int i = 0; // sub iterator
    int j = 0; // parent iterator

    while (i < sublen && j < parentlen) {
        if (sub[i] == parent[j]) {
            i++;
            j++;

            // subarray fully traversed now?
            if (i == sublen) return true;
        }
        else { // increment main array iterator; set subarray iterator to start
            j = j - i + 1;
            i = 0;
        }
    }
    return false;
}

/*
* Counts occurences of an exact value in int array "arr" if "static" is true. Otherwise, counts values that are AT LEAST the target value.
*/
int GameState::countValue(int arr[], int val, int arrlen, bool strict) {
    int ct = 0;
    for (int i = 0; i < arrlen; i++) {
        if (strict) {
            if (arr[i] == val) ct++;
        }
        else {
            if (arr[i] >= val) ct++;
        }
            
    }
    return ct;
}

/*
* Checks for valid scoring methods.
* values (int[]) = the rolled dice values (sorted)
* occurences (int[]) = how often each dice value occured on this roll
* vlen / olen = lengths of the above two arrays
* dman = Dice manager
* cman = Chips manager
*/
void GameState::checkValidity(int values[], int occurences[], int vlen, int olen, DiceManager dman, ChipManager cman) {
    twoPairsValid = false;
    threeOfAKindValid = false;
    smallStraightValid = false;
    flushValid = false;
    fullHouseValid = false;
    largeStraightValid = false;
    yahtzeeValid = false;

    // two pairs
    if (countValue(occurences, 2, olen, false) == 2) {
        cout << "Two pairs valid!\n";
        twoPairsValid = true;
    }

    // three of a kind
    if (countValue(occurences, 3, olen, false) == 1) {
        cout << "Three of a kind valid!\n";
        threeOfAKindValid = true;
    }

    // small straight
    int validSStraights[3][4] = { {1,2,3,4}, {2,3,4,5}, {3,4,5,6} };
    int combinations = 3;
    bool valid = ((occurences[0] >= 1 && occurences[1] >= 1 && occurences[2] >= 1 && occurences[3] >= 1) 
        || (occurences[1] >= 1 && occurences[2] >= 1 && occurences[3] >= 1 && occurences[4] >= 1)
        || (occurences[2] >= 1 && occurences[3] >= 1 && occurences[4] >= 1 && occurences[5] >= 1));
    if (valid) {
        cout << "Small straight valid!\n";
        smallStraightValid = true;
    }

    // flush
    valid = true;
    for (int i = 0; i < vlen; i++) {
        if (values[i] % 2 != 0) {
            valid = false;
            break;
        }
    }
    if (valid) {
        cout << "Flush valid!\n";
        flushValid = true;
    }

    // full house
    if (countValue(occurences, 3, olen, true) == 1 && countValue(occurences, 2, olen, true) == 1) {
        cout << "Full house valid!\n";
        fullHouseValid = true;
    }

    // four of a kind
    if (countValue(occurences, 4, olen, false) == 1) {
        cout << "Four of a kind valid!\n";
        fourOfAKindValid = true;
    }

    // large straight
    int validLStraights[2][5] = { {1,2,3,4,5}, {2,3,4,5,6} };
    combinations = 2;
    for (int i = 0; i < combinations; i++) {
        if (isSubArray(validLStraights[i], values, 5, vlen)) {
            cout << "Large straight valid!\n";
            largeStraightValid = true;
            break;
        }
    }

    // yahtzee
    if (countValue(occurences, 5, olen, false) == 1) {
        cout << "Yahtzee valid!\n";
        yahtzeeValid = true;
    }
}