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
void printAllDice(DiceManager* dman, HANDLE hConsole) {
    dman->d1.printValue(hConsole);
    cout << "\t";
    dman->d2.printValue(hConsole);
    cout << "\t";
    dman->d3.printValue(hConsole);
    cout << "\t";
    dman->d4.printValue(hConsole);
    cout << "\t";
    dman->d5.printValue(hConsole);
    cout << "\t\n\n";
}

/*
* Prints the current scores and chips left.
*/
void printGameStats(vector<Player> players, ChipManager cman) {
    cout << "SCORES:\n";
    for (int i = 0; i < players.size(); i++) {
        cout << "\tPLAYER " << (i + 1) << ":\t" << players[i].getTotalScore() << "\n";
    }
    cout << "\nCHIPS LEFT:\n";
    cout << "\t(1) Two Pairs\t\t[quantity: " << cman.twoPairs.getQuantity() << "; value: 5]\n";
    cout << "\t(2) Three of a Kind\t[quantity: " << cman.threeOfAKind.getQuantity() << "; value: 10]\n";
    cout << "\t(3) Small Straight\t[quantity: " << cman.smallStraight.getQuantity() << "; value: 20]\n";
    cout << "\t(4) Flush\t\t[quantity: " << cman.flush.getQuantity() << "; value: 25]\n";
    cout << "\t(5) Full House\t\t[quantity: " << cman.fullHouse.getQuantity() << "; value: 30]\n";
    cout << "\t(6) Four of a Kind\t[quantity: " << cman.fourOfAKind.getQuantity() << "; value: 40]\n";
    cout << "\t(7) Large Straight\t[quantity: " << cman.largeStraight.getQuantity() << "; value: 50]\n\n";
}

/*
* Based on 5 dice rolls, checks for valid scoring options (i.e. two pairs)
*/
void checkDice(DiceManager* dman, ChipManager cman, GameState* state) {
    int values[] = { dman->d1.value, dman->d2.value, dman->d3.value, dman->d4.value, dman->d5.value };
    int occurences[] = { 0, 0, 0, 0, 0, 0 };
    const int VALUES_LEN = 5;
    const int OCCURENCES_LEN = 6;

    // sort the dice rolls (to check for straights)
    sort(begin(values), end(values));

    // update occurences
    for (int i = 0; i < VALUES_LEN; i++) {
        occurences[values[i] - 1]++;
    }

    state->checkValidity(values, occurences, VALUES_LEN, OCCURENCES_LEN, cman);
}

/*
* Gets user input after a roll. Returns one of the following:
* 'a': Means user is intending to roll again (if roll is 1 or 2)
* 'c': Means user will give up turn on roll 3, grabbing no chips
* number: Category of chip the user is grabbing (turn ends afterwards):
*   1 = two pairs
*   2 = three of a kind
*   3 = small straight
*   4 = flush
*   5 = full house
*   6 = four of a kind
*   7 = large straight
*/
char getInput(int roll, GameState* state) {
    char choice = 'x';

    if (state->anyValid()) {
        cout << "Available chips:\n";
        if (state->twoPairsValid) {
            cout << "\t(1) Two Pairs\n";
        }
        if (state->threeOfAKindValid) {
            cout << "\t(2) Three of a Kind\n";
        }
        if (state->smallStraightValid) {
            cout << "\t(3) Small Straight\n";
        }
        if (state->flushValid) {
            cout << "\t(4) Flush\n";
        }
        if (state->fullHouseValid) {
            cout << "\t(5) Full House\n";
        }
        if (state->fourOfAKindValid) {
            cout << "\t(6) Four of a Kind\n";
        }
        if (state->largeStraightValid) {
            cout << "\t(7) Large Straight\n";
        }
    }
    else {
        cout << "No chips to select.\n";
    }

    if (roll == 1 || roll == 2) {
        bool validChoice = false;
        do {
            choice = 'x';
            cout << "\Available actions:\n";
            cout << "\tA) Roll again (" << (3 - roll) << " remaining)\n";
            if (state->anyValid()) {
                cout << "\tB) Pick a chip from above list\n";
            }
            cout << "\n";
            cin >> choice;
            if ((choice == 'a' || choice == 'A') || ((choice == 'b' || choice == 'B') && state->anyValid())) validChoice = true;
        } while (!validChoice);

        if (choice == 'A') choice = 'a'; // lowercase for return value consistency
    }
    else {
        bool validChoice = false;
        do {
            choice = 'x';
            cout << "\nAvailable actions:\n";
            if (state->anyValid()) {
                cout << "\tB) Pick a chip from above list\n";
            }
            cout << "\tC) Next turn\n";
            
            cout << "\n";
            cin >> choice;
            if ((choice == 'c' || choice == 'C') || ((choice == 'b' || choice == 'B') && state->anyValid())) validChoice = true;
        } while (!validChoice);

        if (choice == 'C') choice = 'c'; // lowercase for return value consistency
    }

    if (choice == 'b' || choice == 'B' && state->anyValid()) {
        bool validChipChoice = false;
        do {
            choice = 'x';
            cout << "\nChoose a chip (enter number left of category name): ";
            cin >> choice;

            switch (choice) {
            case '1':
                if (state->twoPairsValid) validChipChoice = true;
                break;
            case '2':
                if (state->threeOfAKindValid) validChipChoice = true;
                break;
            case '3':
                if (state->smallStraightValid) validChipChoice = true;
                break;
            case '4':
                if (state->flushValid) validChipChoice = true;
                break;
            case '5':
                if (state->fullHouseValid) validChipChoice = true;
                break;
            case '6':
                if (state->fourOfAKindValid) validChipChoice = true;
                break;
            case '7':
                if (state->largeStraightValid) validChipChoice = true;
                break;
            }
        } while (!validChipChoice);
    }

    return choice;
}

/*
* Play one of three rounds of a player's turn. The player will roll the dice and enter a character for input. That input gets returned from here. (See docs for getInput())
*/
char playRound(vector<Player> players, DiceManager* dman, ChipManager cman, GameState* state, HANDLE hConsole) {
    clearScreen();

    // set color of header based on whos turn it is
    switch (state->playerTurn) {
    case 0:
        SetConsoleTextAttribute(hConsole, 10);
        break;
    case 1:
        SetConsoleTextAttribute(hConsole, 11);
        break;
    case 2:
        SetConsoleTextAttribute(hConsole, 12);
        break;
    case 3:
        SetConsoleTextAttribute(hConsole, 14);
        break;
    }
    cout << "=== It is now Player " << (state->playerTurn) + 1 << "'s Turn ===\n";
    SetConsoleTextAttribute(hConsole, 15);
    printGameStats(players, cman);

    system("pause");
    cout << "\nYou rolled:\n";

    dman->roll();

    printAllDice(dman, hConsole);
    checkDice(dman, cman, state);

    return getInput(state->currentRoll, state);
}

void handleReRoll(DiceManager* dman, HANDLE hConsole) {
    char rollInput;
    dman->r1 = true;
    dman->r2 = true;
    dman->r3 = true;
    dman->r4 = true;
    dman->r5 = true;

    do {
        clearScreen();

        cout << "Your roll last round was:\n";
        printAllDice(dman, hConsole);

        cout << "You will be re-rolling the following dice:\n";
        if (dman->r1) cout << "\tDice 1\n";
        if (dman->r2) cout << "\tDice 2\n";
        if (dman->r3) cout << "\tDice 3\n";
        if (dman->r4) cout << "\tDice 4\n";
        if (dman->r5) cout << "\tDice 5\n";

        cout << "\nEnter a dice to toggle whether it will be rollable. Enter '0' to stop entering dice, and to advance to the next round. > ";
        cin >> rollInput;
        switch (rollInput) {
        case '0':
            break; // advance to next round
        case '1':
            dman->r1 = !dman->r1;
            break;
        case '2':
            dman->r2 = !dman->r2;
            break;
        case '3':
            dman->r3 = !dman->r3;
            break;
        case '4':
            dman->r4 = !dman->r4;
            break;
        case '5':
            dman->r5 = !dman->r5;
            break;
        }
    } while (rollInput != '0');
}

int main()
{
    srand(time(NULL)); // seed RNG

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);;
    SetConsoleTextAttribute(hConsole, 15); // set console text to white

    ChipManager cman;
    DiceManager* dman = new DiceManager(); // pointer; passed/modified in playRound() and other called funcs
    GameState* state = new GameState(); // pointer; passed/modified in checkValidity()

    vector<Player> players; // who is playing
    bool allChipsGone = false;

    cout << "=== Welcome to Yahtzee ===\n";
    
    // get players
    int numPlayers = 0;
    do {
        cout << "How many players are playing? (2-4) > ";
        cin >> numPlayers;
    } while (numPlayers < 2 || numPlayers > 4);

    for (int i = 0; i < numPlayers; i++) {
        Player p;
        players.push_back(p);
    }

    // game loop
    do {
        char input;
        dman->r1 = true;
        dman->r2 = true;
        dman->r3 = true;
        dman->r4 = true;
        dman->r5 = true;

        state->currentRoll = 1;

        // roll 1
        input = playRound(players, dman, cman, state, hConsole);

        if (input == 'a') { // player rolls again
            handleReRoll(dman, hConsole);

            state->currentRoll++;

            input = playRound(players, dman, cman, state, hConsole);

            if (input == 'a') { // player rolls one more time
                handleReRoll(dman, hConsole);

                state->currentRoll++;

                input = playRound(players, dman, cman, state, hConsole);
            }
        }

        if (input != 'c') { // in case we reach this after 3rd roll, and player cannot grab a chip
            switch (input) {
            case '1':
                players[state->playerTurn].addChip(cman.twoPairs.removeChip());
                break;
            case '2':
                players[state->playerTurn].addChip(cman.threeOfAKind.removeChip());
                break;
            case '3':
                players[state->playerTurn].addChip(cman.smallStraight.removeChip());
                break;
            case '4':
                players[state->playerTurn].addChip(cman.flush.removeChip());
                break;
            case '5':
                players[state->playerTurn].addChip(cman.fullHouse.removeChip());
                break;
            case '6':
                players[state->playerTurn].addChip(cman.fourOfAKind.removeChip());
                break;
            case '7':
                players[state->playerTurn].addChip(cman.largeStraight.removeChip());
                break;
            }
        }
        
        // change turn
        state->playerTurn++;
        state->playerTurn %= players.size();

        // check if any chips are left
        allChipsGone = cman.twoPairs.getQuantity() == 0 && cman.threeOfAKind.getQuantity() == 0 &&
            cman.smallStraight.getQuantity() == 0 && cman.flush.getQuantity() == 0 &&
            cman.fullHouse.getQuantity() == 0 && cman.fourOfAKind.getQuantity() == 0 &&
            cman.largeStraight.getQuantity() == 0;
    } while (!allChipsGone);

    clearScreen();
    cout << "Game complete!\n\n";

    int maxScore = -1;
    int maxPlayer = -1;
    cout << "SCORES:\n";
    for (int i = 0; i < players.size(); i++) {
        cout << "\tPLAYER " << (i + 1) << ":\t" << players[i].getTotalScore() << "\n";
        if (players[i].getTotalScore() > maxScore) {
            maxScore = players[i].getTotalScore();
            maxPlayer = i;
        }
    }

    cout << "Player " << (maxPlayer + 1) << " wins!\n";

    delete state;
    delete dman;

    return 0;
}
