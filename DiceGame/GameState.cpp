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
void GameState::checkValidity(int values[], int occurences[], int vlen, int olen, ChipManager cman) {
    twoPairsValid = false;
    threeOfAKindValid = false;
    smallStraightValid = false;
    flushValid = false;
    fullHouseValid = false;
    fourOfAKindValid = false;
    largeStraightValid = false;
    yahtzeeValid = false;

    // two pairs
    if (countValue(occurences, 2, olen, false) == 2) {
        twoPairsValid = true;
    }

    // three of a kind
    if (countValue(occurences, 3, olen, false) == 1) {
        threeOfAKindValid = true;
    }

    // small straight
    int validSStraights[3][4] = { {1,2,3,4}, {2,3,4,5}, {3,4,5,6} };
    int combinations = 3;
    bool valid = ((occurences[0] >= 1 && occurences[1] >= 1 && occurences[2] >= 1 && occurences[3] >= 1) 
        || (occurences[1] >= 1 && occurences[2] >= 1 && occurences[3] >= 1 && occurences[4] >= 1)
        || (occurences[2] >= 1 && occurences[3] >= 1 && occurences[4] >= 1 && occurences[5] >= 1));
    if (valid) {
        smallStraightValid = true;
    }

    // flush
    if ((occurences[0] == 0 && occurences[2] == 0 && occurences[4] == 0) || (occurences[1] == 0 && occurences[3] == 0 && occurences[5] == 0)) {
        flushValid = true;
    }

    // full house
    if (countValue(occurences, 3, olen, true) == 1 && countValue(occurences, 2, olen, true) == 1) {
        fullHouseValid = true;
    }

    // four of a kind
    if (countValue(occurences, 4, olen, false) == 1) {
        fourOfAKindValid = true;
    }

    // large straight
    int validLStraights[2][5] = { {1,2,3,4,5}, {2,3,4,5,6} };
    combinations = 2;
    for (int i = 0; i < combinations; i++) {
        if (isSubArray(validLStraights[i], values, 5, vlen)) {
            largeStraightValid = true;
            break;
        }
    }

    // yahtzee
    if (countValue(occurences, 5, olen, false) == 1) {
        yahtzeeValid = true;

        // also enable every other stack
        twoPairsValid = true;
        threeOfAKindValid = true;
        smallStraightValid = true;
        flushValid = true;
        fullHouseValid = true;
        largeStraightValid = true;
        yahtzeeValid = true;
    }

    // disable chips if quantity is 0
    if (cman.twoPairs.getQuantity() == 0) twoPairsValid = false;
    if (cman.threeOfAKind.getQuantity() == 0) threeOfAKindValid = false;
    if (cman.smallStraight.getQuantity() == 0) smallStraightValid = false;
    if (cman.flush.getQuantity() == 0) flushValid = false;
    if (cman.fullHouse.getQuantity() == 0) fullHouseValid = false;
    if (cman.fourOfAKind.getQuantity() == 0) fourOfAKindValid = false;
    if (cman.largeStraight.getQuantity() == 0) largeStraightValid = false;
}

/*
* Returns true if any scoring options are valid
*/
bool GameState::anyValid() {
    return twoPairsValid || threeOfAKindValid || smallStraightValid || flushValid || fullHouseValid || fourOfAKindValid || largeStraightValid || yahtzeeValid;
}