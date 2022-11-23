#include "DiceManager.hpp"
#include "Dice.hpp"
using namespace std;

void DiceManager::roll() {
	if (r1) d1.roll();
	if (r2) d2.roll();
	if (r3) d3.roll();
	if (r4) d4.roll();
	if (r5) d5.roll();
}