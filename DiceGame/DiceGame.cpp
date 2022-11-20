#include <iostream>
#include <windows.h>
#include "Dice.hpp"
#include "ChipStack.hpp"
#include "Player.hpp"
using namespace std;

int main()
{
    srand(time(NULL)); // seed RNG

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);;
    SetConsoleTextAttribute(hConsole, 15); // set console text to white

    Dice d1, d2, d3, d4, d5;
    vector<Player> players;
    ChipStack twoPairs(5);
    ChipStack threeOfAKind(10);
    ChipStack smallStraight(20);
    ChipStack flush(25);
    ChipStack fullHouse(30);
    ChipStack fourOfAKind(40);
    ChipStack largeStraight(50);
}
