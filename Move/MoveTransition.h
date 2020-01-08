#ifndef MOVE_TRANSITION_H
#define MOVE_TRANSITION_H

#include "MoveStatus.h"

class Board;

class MoveTransition{
private:
	Board* board;
	MoveStatus status;
public:
	MoveTransition(){
		this->board = NULL;
	}
	MoveTransition(Board* board, MoveStatus status){
		this->board = board;
		this->status = status;
	}
	~MoveTransition(){
		// Destructor
	}
	Board* getBoard(){ return this->board; }
	bool isSuccess(){ return this->status == MoveStatus::SUCCESS; }
};

#endif