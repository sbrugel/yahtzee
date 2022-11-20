#include <iostream>
#include <vector>
#include "Player.hpp"
using namespace std;

void Player::addChip(int value) {
	chips.push_back(value);
}

void Player::printAllChips() {
	for (int i = 0; i < chips.size(); i++) {
		cout << chips[i] << "\t";
	}
}

int Player::getTotalScore() {
	int score = 0;
	for (int i = 0; i < chips.size(); i++) {
		score += chips[i];
	}
	return score;
}