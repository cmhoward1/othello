#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    board = new Board();
    my_side = side;

}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) 
{  
    // Set the opponent's side to whatever my side isn't
    Side opp_side = BLACK;
    if (my_side == BLACK)
    {
    	opp_side = WHITE;
    }
    
    // update the board to have the opponent's move
    board->doMove(opponentsMove, opp_side);

    // Store all of my possible moves in a vector
    // A score should have the same index as its corresponding move
    // Arbitrarily, score:
    // +---+---+---+---+---+---+---+---+
    // | 2 |-1 | 1 | 1 | 1 | 1 |-1 | 2 |
    // +---+---+---+---+---+---+---+---+
    // |-1 |-2 | 0 | 0 | 0 | 0 |-2 |-1 |
    // +---+---+---+---+---+---+---+---+
    // | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |
    // +---+---+---+---+---+---+---+---+
    // | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |
    // +---+---+---+---+---+---+---+---+
    // | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |
    // +---+---+---+---+---+---+---+---+
    // | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |
    // +---+---+---+---+---+---+---+---+
    // |-1 |-2 | 0 | 0 | 0 | 0 |-2 |-1 |
    // +---+---+---+---+---+---+---+---+
    // | 2 |-1 | 1 | 1 | 1 | 1 |-1 | 2 |
    // +---+---+---+---+---+---+---+---+
    std::vector<Move*> moves;
    std::vector<int> scores;
    
    // If there are possible moves, push them back to the vector
    if (board->hasMoves(my_side))
    {
    	for (int i = 0; i < 8; ++i)
        {
    	    for (int j = 0; j < 8; ++j)
    	    {
    		    Move *a_move = new Move(i, j);
    		    if (board->checkMove(a_move, my_side))
    		    {
    		    	moves.push_back(a_move);
    		    	if ((i == 1 || i == 6) && (j == 1 || j == 6))
    		    	{
    		    		scores.push_back(-2);
    		    	}
    		    	else if (i == 0 || i == 7)
    		    	{
    		    		if (j == 0 || j == 7)
    		    		{
    		    			scores.push_back(2);
    		    		}
    		    		else if (j == 1 || j == 6)
    		    		{
    		    			scores.push_back(-1);
    		    		}
    		    		else
    		    		{
    		    			scores.push_back(1);
    		    		}
    		    	}
    		    	else
    		    	{
    		    		scores.push_back(0);
    		    	}
    		    }
    		    // free memory!
    		    else 
    		    {
    		    	delete a_move;
    		    }
    	    }
        }
        // Select a find the index with the maximum score 
        int my_move_index = 0;
        for (int i = 0; i < (int) scores.size(); ++i)
        {
        	if (scores[i] > scores[my_move_index])
        	{
        		my_move_index = i;
        	}
        }
  
        board->doMove(moves[my_move_index], my_side);

        // free memory!
        for (int i = 0; i < (int) moves.size(); ++i)
        {
        	if (i != my_move_index)
        	{
        		delete moves[i];
        	}
        }
        return moves[my_move_index];
    }
    return nullptr;
}

