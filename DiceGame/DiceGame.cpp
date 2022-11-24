#include <array>
#include <algorithm>
#include <iostream>
#include <windows.h>

#include "ChipManager.hpp"
#include "DiceManager.hpp"
#include "GameState.hpp"
#include "Player.hpp"

using namespace std;

/*
* Clears the screen.
*/
void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

/*
* Prints all dice values to console. Even values printed in red.
*/
void printAllDice(DiceManager dman, HANDLE hConsole) {
    dman.d1.printValue(hConsole);
    cout << "\t";
    dman.d2.printValue(hConsole);
    cout << "\t";
    dman.d3.printValue(hConsole);
    cout << "\t";
    dman.d4.printValue(hConsole);
    cout << "\t";
    dman.d5.printValue(hConsole);
    cout << "\t\n";
}

/*
* Based on 5 dice rolls, checks for valid scoring options (i.e. two pairs)
*/
void checkDice(DiceManager dman, ChipManager cman, GameState* state) {
    int values[] = { dman.d1.value, dman.d2.value, dman.d3.value, dman.d4.value, dman.d5.value };
    int occurences[] = { 0, 0, 0, 0, 0, 0 };
    const int VALUES_LEN = 5;
    const int OCCURENCES_LEN = 6;

    // sort the dice rolls (to check for straights)
    sort(begin(values), end(values));

    // update occurences
    for (int i = 0; i < VALUES_LEN; i++) {
        occurences[values[i] - 1]++;
    }

    state->checkValidity(values, occurences, VALUES_LEN, OCCURENCES_LEN, dman, cman);
}

char getInput(int roll, DiceManager dman, ChipManager cman, GameState* state) {
    if (roll == 1 || roll == 2) {
        // A = roll again
        // B = pick chip (if valid)
        cout << "is any valid? " << state->anyValid() << "\n";
        if (state->anyValid()) {
            cout << "Available Chips:\n";
            if (state->twoPairsValid) {
                cout << "\t(5) Two Pairs:\t[quantity: " << cman.twoPairs.getQuantity() << "]\n";
            }
            if (state->threeOfAKindValid) {
                cout << "\t(10) Three of a Kind:\t[quantity: " << cman.threeOfAKind.getQuantity() << "]\n";
            }
            if (state->smallStraightValid) {
                cout << "\t(20) Small Straight:\t[quantity: " << cman.smallStraight.getQuantity() << "]\n";
            }
            if (state->flushValid) {
                cout << "\t(25) Flush:\t[quantity: " << cman.flush.getQuantity() << "]\n";
            }
            if (state->fullHouseValid) {
                cout << "\t(30) Full House:\t[quantity: " << cman.fullHouse.getQuantity() << "]\n";
            }
            if (state->fourOfAKindValid) {
                cout << "\t(40) Four of a Kind:\t[quantity: " << cman.fourOfAKind.getQuantity() << "]\n";
            }
            if (state->largeStraightValid) {
                cout << "\t(50) Large Straight:\t[quantity: " << cman.largeStraight.getQuantity() << "]\n";
            }
        }
        else {
            cout << "No chips to select.\n";
        }
    }
    else {

    }
    return 'x';
}

int main()
{
    srand(time(NULL)); // seed RNG

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);;
    SetConsoleTextAttribute(hConsole, 15); // set console text to white

    DiceManager diceMan;
    ChipManager chipMan;
    GameState* state = new GameState();

    vector<Player> players; // who is playing
    int playerTurn = 0; // index (in players vector) of who's turn it is
    int currentRoll = 1; // what roll this player is on (1, 2, or 3)

    cout << "=== Welcome to Yahtzee ===\n";
    
    // get players
    int numPlayers = 0;
    do {
        cout << "How many players are playing? (1-4) > ";
        cin >> numPlayers;
    } while (numPlayers < 1 || numPlayers > 4);

    for (int i = 0; i < numPlayers; i++) {
        Player p;
        players.push_back(p);
    }

    // game loop
    bool allChipsGone = false;
    do {
        // roll 1
        clearScreen();
        diceMan.r1 = true;
        diceMan.r2 = true;
        diceMan.r3 = true;
        diceMan.r4 = true;
        diceMan.r5 = true;

        cout << "=== It is now Player " << playerTurn + 1 << "'s Turn ===\n";
        system("pause");
        cout << "\nYou rolled:\n";

        diceMan.roll();

        printAllDice(diceMan, hConsole);

        checkDice(diceMan, chipMan, state);

        // TODO: implemenet remaining player's turn code
        getInput(currentRoll, diceMan, chipMan, state);
        
        // change turn
        ++playerTurn %= numPlayers;

        // check if any chips are left
        allChipsGone = chipMan.twoPairs.getQuantity() == 0 && chipMan.threeOfAKind.getQuantity() == 0 &&
            chipMan.smallStraight.getQuantity() == 0 && chipMan.flush.getQuantity() == 0 &&
            chipMan.fullHouse.getQuantity() == 0 && chipMan.fourOfAKind.getQuantity() == 0 &&
            chipMan.largeStraight.getQuantity() == 0;

        allChipsGone = true;
    } while (!allChipsGone);

    delete state;

    return 0;
}
