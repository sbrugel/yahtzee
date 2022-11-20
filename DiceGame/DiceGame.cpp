#include <iostream>
#include <windows.h>
#include "Dice.hpp"
#include "ChipStack.hpp"
#include "Player.hpp"
using namespace std;

void clearScreen() { // just so it's easier to type
    cout << "\033[2J\033[1;1H";
}

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

    cout << "=== Welcome to Yahtzee ===\n";
    
    int numPlayers = 0;
    do {
        cout << "How many players are playing? (1-4) > ";
        cin >> numPlayers;
    } while (numPlayers < 1 || numPlayers > 4);

    for (int i = 0; i < numPlayers; i++) {
        Player p;
        players.push_back(p);
    }

    players[0].addChip(40);
    players[0].printAllChips();

    return 0;
}
