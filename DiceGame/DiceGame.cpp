#include <array>
#include <algorithm>
#include <iostream>
#include <windows.h>

#include "ChipStack.hpp"
#include "ChipManager.hpp"
#include "Dice.hpp"
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
* Checks if "sub" is a sub-array of "parent"
*/
bool isSubArray(int sub[], int parent[], int sublen, int parentlen) {
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

int countValue(int arr[], int val, int arrlen) {
    int ct = 0;
    for (int i = 0; i < arrlen; i++) {
        if (arr[i] == val) ct++;
    }
    return ct;
}

/*
* Based on 5 dice rolls, checks for valid scoring options (i.e. two pairs)
*/
// TODO: move values/occurences + basically all of this code, into GameState checkValid() function after creation of DiceManager/ChipManager
void checkDice(DiceManager dman, ChipManager cman, GameState state) {
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

    state.checkValidity(values, occurences, VALUES_LEN, OCCURENCES_LEN, dman, cman);
}

int main()
{
    srand(time(NULL)); // seed RNG

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);;
    SetConsoleTextAttribute(hConsole, 15); // set console text to white

    DiceManager diceMan;
    ChipManager chipMan;
    GameState state{};

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

        cout << "==TWO PAIRS TESTING==\n";
        diceMan.d1.value = 2;
        diceMan.d2.value = 2;
        diceMan.d3.value = 3;
        diceMan.d4.value = 3;
        diceMan.d5.value = 4;
        printAllDice(diceMan, hConsole);
        checkDice(diceMan, chipMan, state);

        cout << "==3 OF A KIND TESTING==\n";
        diceMan.d1.value = 2;
        diceMan.d2.value = 2;
        diceMan.d3.value = 2;
        diceMan.d4.value = 3;
        diceMan.d5.value = 4;
        printAllDice(diceMan, hConsole);
        checkDice(diceMan, chipMan, state);

        cout << "==SMALL STRAIGHT TESTING==\n";
        diceMan.d1.value = 2;
        diceMan.d2.value = 3;
        diceMan.d3.value = 4;
        diceMan.d4.value = 5;
        diceMan.d5.value = 4;
        printAllDice(diceMan, hConsole);
        checkDice(diceMan, chipMan, state);

        cout << "==FLUSH TESTING==\n";
        diceMan.d1.value = 2;
        diceMan.d2.value = 4;
        diceMan.d3.value = 4;
        diceMan.d4.value = 2;
        diceMan.d5.value = 6;
        printAllDice(diceMan, hConsole);
        checkDice(diceMan, chipMan, state);

        cout << "==FULL HOUSE TESTING==\n";
        diceMan.d1.value = 2;
        diceMan.d2.value = 2;
        diceMan.d3.value = 3;
        diceMan.d4.value = 3;
        diceMan.d5.value = 3;
        printAllDice(diceMan, hConsole);
        checkDice(diceMan, chipMan, state);

        cout << "==LARGE STRAIGHT TESTING==\n";
        diceMan.d1.value = 2;
        diceMan.d2.value = 3;
        diceMan.d3.value = 5;
        diceMan.d4.value = 4;
        diceMan.d5.value = 6;
        printAllDice(diceMan, hConsole);
        checkDice(diceMan, chipMan, state);

        cout << "==YAHTZEE TESTING==\n";
        diceMan.d1.value = 2;
        diceMan.d2.value = 2;
        diceMan.d3.value = 2;
        diceMan.d4.value = 2;
        diceMan.d5.value = 2;
        printAllDice(diceMan, hConsole);
        checkDice(diceMan, chipMan, state);

        // TODO: implemenet remaining player's turn code
        
        // change turn
        ++playerTurn %= numPlayers;

        // check if any chips are left
        allChipsGone = chipMan.twoPairs.getQuantity() == 0 && chipMan.threeOfAKind.getQuantity() == 0 &&
            chipMan.smallStraight.getQuantity() == 0 && chipMan.flush.getQuantity() == 0 &&
            chipMan.fullHouse.getQuantity() == 0 && chipMan.fourOfAKind.getQuantity() == 0 &&
            chipMan.largeStraight.getQuantity() == 0;

        allChipsGone = true;
    } while (!allChipsGone);

    return 0;
}
