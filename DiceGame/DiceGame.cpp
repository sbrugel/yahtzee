#include <iostream>
#include <windows.h>
using namespace std;

struct Dice {
    int value;
    void roll() {
        value = 1 + rand() % 6;
    }
    void printValue(HANDLE h) {
        if (value % 2 == 0) SetConsoleTextAttribute(h, 12); // red
        cout << value;
        SetConsoleTextAttribute(h, 15);
    }
};

int main()
{
    srand(time(NULL)); // seed RNG

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);;
    SetConsoleTextAttribute(hConsole, 15); // set console text to white

    Dice d1, d2, d3, d4, d5;
    d1.roll();
    d2.roll();
    d3.roll();
    d4.roll();
    d5.roll();

    d1.printValue(hConsole);
    cout << "\t";
    d2.printValue(hConsole);
    cout << "\t";
    d3.printValue(hConsole);
    cout << "\t";
    d4.printValue(hConsole);
    cout << "\t";
    d5.printValue(hConsole);
    cout << "\t";
}
