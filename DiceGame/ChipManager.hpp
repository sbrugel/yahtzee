#ifndef CHIPMAN_HPP
#define CHIPMAN_HPP

#include "ChipStack.hpp"

struct ChipManager {
    ChipStack twoPairs = ChipStack(5);
    ChipStack threeOfAKind = ChipStack(10);
    ChipStack smallStraight = ChipStack(20);
    ChipStack flush = ChipStack(25);
    ChipStack fullHouse = ChipStack(30);
    ChipStack fourOfAKind = ChipStack(40);
    ChipStack largeStraight = ChipStack(50);
};

#endif
