# Yahtzee
This is a C++ re-creation of a modified version of Yahtzee, a dice game created by Milton Bradley. The rules of this version of the game are similar to the rules of the original game, with some differences - more on that below.

## The Rules
This is a game that can be played by 2 - 4 people. My re-creation of the game is local; there is no networked multiplayer, so everyone should be at the same computer. Everyone starts with 0 points (of course). 

### Scoring Categories
There are eight types of dice combinations that award points, they are as follows:

- **Two Pairs (5 points):** Two pairs of dice showing the same value

- **Three of a Kind (10 points):** Three dice showing the same value

- **Small Straight (20 points):** Four dice showing consecutive values (1-2-3-4, 2-3-4-5, 3-4-5-6)

- **Flush (25 points):** All dice are either entirely odd or entirely even

- **Full House (30 points):** Three-of-a-kind and a single pair

- **Four of a Kind (40 points):** Four dice showing the same value

- **Large Straight (50 points):** Five dice showing consecutive values (1-2-3-4-5, 2-3-4-5-6)

- **Yahtzee:** All five dice showing the same value. There are no chips for this; if you score a Yahtzee, choose any other available chip and replay your turn.

There are four chips each for every category above except Yahtzees. So if there are no Two Pairs chips left (all are taken by players), and the player rolls 1-1-2-2-5, they will not earn 5 points and must either re-roll for another category or change turns.

### Game Flow
Each turn, a player rolls five dice to start. The values of all dice are displayed, and the player will have one or two options depending on their roll:

- The player will always have the option to roll again, selecting which dice to keep the values of (aka, they will not be rolled). The player can re-roll a maximum of two times.
- If the roll wins one or more chips, you can instead choose a valid chip of your choosing and end your turn immediately.

If on your third roll, your roll does not win any chips, the game will advance to the next player.

The game ends when all chips are taken; the winner is the player with the most points.

## Notes
This will only run on Windows systems currently due to usage of a library that changes the console text color; this may be modified later to make the program work on other operating systems.