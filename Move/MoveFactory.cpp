#include "MoveFactory.h"
#include "Move.h"
#include "MoveTransition.h"
#include "MoveStatus.h"
#include "../Board/Board.h"

MoveTransition MoveFactory::createMove(Board* board, int source, int destination){
	for(Move* move : board->getCurrentPlayer()->getLegalMoves()){
		if(move->getPosition() == source && move->getDestination() == destination){
			Board* tBoard = move->execute();
			if(tBoard->getOpponentPlayer()->isInCheck()){
				return MoveTransition(board, MoveStatus::LEAVES_PLAYER_IN_CHECK);
			}
			return MoveTransition(tBoard, move, MoveStatus::SUCCESS);
		}
	}
	return MoveTransition(board, MoveStatus::ILLEGAL);
}