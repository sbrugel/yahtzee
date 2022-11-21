#include <array>
#include <algorithm>
#include <iostream>
#include <windows.h>

#include "ChipStack.hpp"
#include "Dice.hpp"
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
void printAllDice(Dice d1, Dice d2, Dice d3, Dice d4, Dice d5, HANDLE hConsole) {
    d1.printValue(hConsole);
    cout << "\t";
    d2.printValue(hConsole);
    cout << "\t";
    d3.printValue(hConsole);
    cout << "\t";
    d4.printValue(hConsole);
    cout << "\t";
    d5.printValue(hConsole);
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
void checkDice(Dice d1, Dice d2, Dice d3, Dice d4, Dice d5) {
    int values[] = { d1.value, d2.value, d3.value, d4.value, d5.value };
    int occurences[] = { 0, 0, 0, 0, 0, 0 };
    const int VALUES_LEN = 5;
    const int OCCURENCES_LEN = 6;

    // sort the dice rolls (to check for straights)
    sort(begin(values), end(values));

    // update occurences
    for (int i = 0; i < VALUES_LEN; i++) {
        occurences[values[i] - 1]++;
    }
    sort(begin(occurences), end(occurences));
}

int main()
{
    srand(time(NULL)); // seed RNG

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);;
    SetConsoleTextAttribute(hConsole, 15); // set console text to white

    Dice d1, d2, d3, d4, d5;

    vector<Player> players;
    int playerTurn = 0; // index (in players vector) of who's turn it is

    ChipStack twoPairs(5);
    ChipStack threeOfAKind(10);
    ChipStack smallStraight(20);
    ChipStack flush(25);
    ChipStack fullHouse(30);
    ChipStack fourOfAKind(40);
    ChipStack largeStraight(50);

    GameState state;

    int currentRoll = 1;

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
        d1.rollable = true;
        d2.rollable = true;
        d3.rollable = true;
        d4.rollable = true;
        d5.rollable = true;

        cout << "=== It is now Player " << playerTurn + 1 << "'s Turn ===\n";
        system("pause");
        cout << "\nYou rolled:\n";

        d1.roll();
        d2.roll();
        d3.roll();
        d4.roll();
        d5.roll();

        printAllDice(d1, d2, d3, d4, d5, hConsole);
        checkDice(d1, d2, d3, d4, d5);

        // TODO: implemenet remaining player's turn code
        
        // change turn
        ++playerTurn %= numPlayers;

        // check if any chips are left
        allChipsGone = twoPairs.getQuantity() == 0 && threeOfAKind.getQuantity() == 0 &&
            smallStraight.getQuantity() == 0 && flush.getQuantity() == 0 &&
            fullHouse.getQuantity() == 0 && fourOfAKind.getQuantity() == 0 &&
            largeStraight.getQuantity() == 0;

        allChipsGone = true;
    } while (!allChipsGone);

    return 0;
}
