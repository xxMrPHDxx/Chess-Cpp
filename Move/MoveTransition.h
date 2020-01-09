#ifndef MOVE_TRANSITION_H
#define MOVE_TRANSITION_H

#include "MoveStatus.h"

class Board;

class MoveTransition{
private:
	Board* board;
	Move* move;
	MoveStatus status;
public:
	MoveTransition(){
		this->board = NULL;
		this->move = NULL;
	}
	MoveTransition(Board* board, Move* move, MoveStatus status){
		this->board = board;
		this->move = move;
		this->status = status;
	}
	MoveTransition(Board* board, MoveStatus status) : MoveTransition(board, NULL, status) {}
	~MoveTransition(){
		// Destructor
	}
	Board* getBoard(){ return this->board; }
	Move* getMove(){ return this->move; }
	MoveStatus getStatus(){ return this->status; }
	bool isSuccess(){ return this->status == MoveStatus::SUCCESS; }
};

#endif