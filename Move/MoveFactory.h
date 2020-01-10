#ifndef MOVE_FACTORY_H
#define MOVE_FACTORY_H

#include "MoveTransition.h"

class Move;
class Board;

class MoveFactory {
public:
	MoveFactory(){ throw std::invalid_argument("Cannot instantiate MoveFactory!"); }
	static MoveTransition createMove(Board* board, int source, int destination);
	static MoveTransition createMove(Move* move){
		return MoveFactory::createMove(move->getBoard(), move->getPosition(), move->getDestination());
	}
};

#endif