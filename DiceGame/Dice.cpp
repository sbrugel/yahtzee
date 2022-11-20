#include <iostream>
#include <windows.h>
#include "Dice.hpp"
using namespace std;

void Dice::roll() {
    value = 1 + rand() % 6;
}

void Dice::printValue(HANDLE h) {
    if (value % 2 == 0) SetConsoleTextAttribute(h, 12); // set text to red for evens only
    cout << value;
    SetConsoleTextAttribute(h, 15); // reset to white when we return to main
}
