#include <array>
#include <iostream>
#include "GameState.hpp"
using namespace std;

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

int GameState::countValue(int arr[], int val, int arrlen) {
    int ct = 0;
    for (int i = 0; i < arrlen; i++) {
        if (arr[i] == val) ct++;
    }
    return ct;
}

void GameState::checkValidity(int values[], int occurences[], int vlen, int olen) {
    twoPairsValid = false;
    threeOfAKindValid = false;
    smallStraightValid = false;
    flushValid = false;
    fullHouseValid = false;
    largeStraightValid = false;
    yahtzeeValid = false;

    // two pairs
    

    // three of a kind
    

    // small straight
    int validStraights[3][4] = { {1,2,3,4}, {2,3,4,5}, {3,4,5,6} };
    int combinations = 3;
    for (int i = 0; i < combinations; i++) {
        if (isSubArray(validStraights[i], occurences, 4, olen)) {
            cout << "Small straight valid!\n";
            smallStraightValid = true;
            break;
        }
    }

    // flush
    bool valid = (occurences[0] == 0 && occurences[2] == 0 && occurences[4] == 0) || (occurences[1] == 0 && occurences[3] == 0 && occurences[5] == 0);
    if (valid) {
        cout << "Flush valid!\n";
        flushValid = true;
    }

    // full house
    

    // four of a kind
    

    // large straight
    int validStraights[2][5] = { {1,2,3,4,5}, {2,3,4,5,6} };
    int combinations = 2;
    for (int i = 0; i < combinations; i++) {
        if (isSubArray(validStraights[i], occurences, 5, olen)) {
            cout << "Large straight valid!\n";
            largeStraightValid = true;
            break;
        }
    }

    // yahtzee

}