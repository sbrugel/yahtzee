#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <vector>
using namespace std;

class Player {
    vector<int> chips; // the point values of all chips in this player's possession

public:
    void addChip(int value);
    void printAllChips();
    int getTotalScore();
};

#endif
