#include <iostream>
#include <vector>
#include "Player.hpp"
using namespace std;

void Player::addChip(int value) {
	chips.push_back(value);
}

void Player::printAllChips() {
	if (chips.size() == 0) cout << "No chips";
	else {
		for (int i = 0; i < chips.size(); i++) {
			cout << chips[i] << "\t";
		}
	}
	cout << "\n";
}

int Player::getTotalScore() {
	int score = 0;
	for (int i = 0; i < chips.size(); i++) {
		score += chips[i];
	}
	return score;
}