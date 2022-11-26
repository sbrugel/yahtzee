#include "ChipStack.hpp"
#include <iostream>
using namespace std;

ChipStack::ChipStack(int val) {
	pointsValue = val;
	quantity = 4;
}

/*
* Reduces chip quantity by 1 and returns the value of the chip stack's point value. To be used in conjunction with Player.addChip()
*/
int ChipStack::removeChip() {
	if (quantity - 1 < 0) {
		cout << "No chips are left in this stack!\n";
		return 0;
	}
	quantity--;
	return pointsValue;
}

int ChipStack::getQuantity() {
	return quantity;
}