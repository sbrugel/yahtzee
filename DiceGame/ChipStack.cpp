#include "ChipStack.hpp"
#include <iostream>
using namespace std;

ChipStack::ChipStack(int val) {
	pointsValue = val;
	quantity = 4;
}

int ChipStack::removeChip() {
	if (quantity - 1 < 0) {
		cout << "No chips are left in this stack!\n";
		return 0;
	}
	quantity--;
	return pointsValue;
}