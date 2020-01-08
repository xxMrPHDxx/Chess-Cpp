#ifndef MAJORMOVE_H
#define MAJORMOVE_H 

#include "Move.h"

class MajorMove : public Move {
public:
	MajorMove() : Move() {}
	MajorMove(Board* board, Piece* piece, int dest) : Move(board, piece, dest, NULL) {}
	~MajorMove(){
		// Nothing here
	}
	Board* execute() override;
	std::string toString() override;
};

#endif