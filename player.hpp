#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);

    Move *move_minimax(Board *board, Side side, int depth);
    float minimax(Board *board, Side side, int depth);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;

	Board * board;
	Side my_side;
};

#endif
