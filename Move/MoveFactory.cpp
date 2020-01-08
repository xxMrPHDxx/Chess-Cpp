#include "MoveFactory.h"
#include "Move.h"
#include "../Board/Board.h"

Move* MoveFactory::createMove(Board* board, int source, int destination){
	for(Move* move : board->getCurrentPlayer()->getLegalMoves()){
		if(move->getPosition() == source && move->getDestination() == destination){
			return move;
		}
	}
	return NULL;
}