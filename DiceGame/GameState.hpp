#ifndef STATE_HPP
#define STATE_HPP

#include "Dice.hpp"
#include "DiceManager.hpp"
#include "ChipManager.hpp"

class GameState {
public:
    int currentRoll, playerTurn;
    bool twoPairsValid, threeOfAKindValid, smallStraightValid, flushValid, fullHouseValid, fourOfAKindValid, largeStraightValid, yahtzeeValid;

    bool isSubArray(int sub[], int parent[], int sublen, int parentlen);
    int countValue(int arr[], int val, int arrlen, bool strict);
    void checkValidity(int values[], int occurences[], int vlen, int olen, ChipManager cman);
    bool anyValid();
};

#endif
