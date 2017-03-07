#include "player.hpp"
#define DEPTH 4
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
 *
 */
Move *Player::move_minimax(Board *board, Side side, int depth)
{
	Side other = (side == BLACK) ? WHITE : BLACK;
	std::vector<Move*> moves;
	    for (int i = 0; i < 8; ++i)
        {
        	for (int j = 0; j < 8; ++j)
        	{
        		Move *a_move = new Move(i, j);
        		if (board->checkMove(a_move, side))
        		{
                    moves.push_back(a_move);
        		}
        		// free memory!
        		else
        		{
        			delete a_move;
        		}
        	}
        }
        
        float best_score = -500000;
        Move *best_move = moves[0];

        // check out each move on a copy of the board
        for (int i = 0; i < (int) moves.size(); ++i)
        {
        	// check out each move on a copy of the board
            Board *copyboard = board->copy();

        	copyboard->doMove(moves[i], side);
        	float score = - minimax(copyboard, other, depth + 1);
        	if (moves[i]->getX() == 0 || moves[i]->getX() == 7)
        	{
        		// corners are very good!
        		if (moves[i]->getY() == 0 || moves[i]->getY() == 7)
        		{
        			if (score > 0)
        			{
        				score *= 5;
        			}
        			else
        			{
        				score *= -1;
        			}
        		}
        		//next to corners is bad
        		else if (moves[i]->getY() == 1 || moves[i]-> getY() == 6)
        		{
        			if(score > 0)
        		    {
        				score *= 0.5;
        			}
        			else
        			{
        				score *= 2;
        			}
        		}
        		// edges are good!
        		else
        		{
        			if(score > 0)
        			{	
        			    score *= 2;
        			}
        			else
        			{
        				score *= -.5;
        			}
        		}
        	}
        	// diagonal from corners is very bad!
        	else if ((moves[i]->getX() == 1 || moves[i]->getX() == 6) &&
        		     (moves[i]->getY() == 1 || moves[i]->getY() == 6))
        	{
        		if (score > 0)
        		{
        			score *= -1;
        		}
        		else
        		{
        			score *= 3;
        		}
        	}
        	if(best_score < score)
        	{
                best_score = score;
                best_move = moves[i];
        	}

        	// free memory!
            delete copyboard;
        }
        return best_move;
}

/*
 * Implement minimax 
 */
float Player::minimax(Board *board, Side side, int depth)
{
	Side other = (side == BLACK) ? WHITE : BLACK;
	if (depth == DEPTH)
	{
		return board->count(side) - board->count(other);
	}

	else 
	{
        std::vector<Move*> moves;
        for (int i = 0; i < 8; ++i)
        {
        	for (int j = 0; j < 8; ++j)
        	{
        		Move *a_move = new Move(i, j);
        		if (board->checkMove(a_move, side))
        		{
                    moves.push_back(a_move);
        		}
        		// free memory!
        		else
        		{
        			delete a_move;
        		}
        	}
        }
        
        float best_score = -500000;

        // check out each move on a copy of the board
        for (int i = 0; i < (int) moves.size(); ++i)
        {
        	// check out each move on a copy of the board
            Board *copyboard = board->copy();

        	copyboard->doMove(moves[i], side);
        	float score = - minimax(copyboard, other, depth + 1);
        	if(best_score < score)
        	{
                best_score = score;
        	}

        	// free memory!
            delete copyboard;
        }
        return best_score;
	}
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
    // A positiont score should have the same index as its corresponding move
    // Arbitrarily, position score:
    // +---+---+---+---+---+---+---+---+
    // | 3 |-1 | 2 | 2 | 2 | 2 |-1 | 3 |
    // +---+---+---+---+---+---+---+---+
    // |-1 |-2 | 1 | 1 | 1 | 1 |-2 |-1 |
    // +---+---+---+---+---+---+---+---+
    // | 2 | 1 | 1 | 1 | 1 | 1 | 1 | 2 |
    // +---+---+---+---+---+---+---+---+
    // | 2 | 1 | 1 | 1 | 1 | 1 | 1 | 2 |
    // +---+---+---+---+---+---+---+---+
    // | 3 | 1 | 1 | 1 | 1 | 1 | 1 | 2 |
    // +---+---+---+---+---+---+---+---+
    // | 2 | 1 | 1 | 1 | 1 | 1 | 1 | 2 |
    // +---+---+---+---+---+---+---+---+
    // |-1 |-2 | 1 | 1 | 1 | 1 |-2 |-1 |
    // +---+---+---+---+---+---+---+---+
    // | 3 |-1 | 2 | 2 | 2 | 2 |-1 | 3 |
    // +---+---+---+---+---+---+---+---+
    std::vector<Move*> moves;
    /*std::vector<float> positionscores;
    std::vector<float> boardscores;*/
    
    // If there are possible moves, push them back to the vector
    if (board->hasMoves(my_side))
    {
    	
    	/*for (int i = 0; i < 8; ++i)
        {
    	    for (int j = 0; j < 8; ++j)
    	    {
    		    Move *a_move = new Move(i, j);
    		    if (board->checkMove(a_move, my_side))
    		    {
    		    	moves.push_back(a_move);
    		    	// diagonal from corners is very bad!
    		    	if ((i == 1 || i == 6) && (j == 1 || j == 6))
    		    	{
    		    		positionscores.push_back(-1);
    		    	}
    		    	else if (i == 0 || i == 7)
    		    	{
    		    		// corners are very good!
    		    		if (j == 0 || j == 7)
    		    		{
    		    			positionscores.push_back(5);
    		    		}
    		    		// next to corners is bad!
    		    		else if (j == 1 || j == 6)
    		    		{
    		    			positionscores.push_back(.2);
    		    		}
    		    		// edges are good!
    		    		else
    		    		{
    		    			positionscores.push_back(2);
    		    		}
    		    	}
    		    	// everything else is meh
    		    	else
    		    	{
    		    		positionscores.push_back(1);
    		    	}
    		    }
    		    // free memory!
    		    else 
    		    {
    		    	delete a_move;
    		    }
    	    }
        }*/
        
        
/*
        // find the resulting score of each move
        for (int i = 0; i < (int) moves.size(); ++i)
        {
        	// check out each move on a copy of the board
            Board *copyboard = board->copy();
        	copyboard->doMove(moves[i], my_side);
        	boardscores.push_back(copyboard->count(my_side) 
        		                  - copyboard->count(opp_side));
        	// free memory!
            delete copyboard;
        }

        

        // scale our board scores by their position scores
        for (int i = 0; i < (int) boardscores.size(); ++i)
        {
        	boardscores[i] = boardscores[i] * positionscores[i];
        }

        // Select a find the index with the maximum score
        int my_move_index = 0;
        for (int i = 0; i < (int) boardscores.size(); ++i)
        {
        	if (boardscores[i] > boardscores[my_move_index])
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
        }*/
        Move *move = move_minimax(board, my_side, 0);

        board->doMove(move, my_side);

        return move;
    }
    return nullptr;
}

