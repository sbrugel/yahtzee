#ifndef STATE_HPP
#define STATE_HPP

#include "Dice.hpp"

class GameState {
public:
    bool twoPairsValid, threeOfAKindValid, smallStraightValid, flushValid, fullHouseValid, fourOfAKindValid, largeStraightValid, yahtzeeValid;

    bool isSubArray(int sub[], int parent[], int sublen, int parentlen);
    int countValue(int arr[], int val, int arrlen);
    void checkValidity(int values[], int occurences[], int vlen, int olen);
};

#endif
