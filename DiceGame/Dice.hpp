#ifndef DICE_HPP
#define DICE_HPP

#include <iostream>
#include <windows.h>
using namespace std;

struct Dice {
    int value;
    bool rollable;
    void roll();
    void printValue(HANDLE h);
};

#endif
