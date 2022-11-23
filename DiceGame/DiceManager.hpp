#ifndef DICEMAN_HPP
#define DICEMAN_HPP

#include "Dice.hpp"

struct DiceManager {
	Dice d1, d2, d3, d4, d5;
	bool r1, r2, r3, r4, r5;

	void roll();
};

#endif