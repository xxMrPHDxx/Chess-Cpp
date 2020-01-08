#ifndef PAWN_MOVE_H
#define PAWN_MOVE_H

#include "Move.h"

class PawnMove : public Move {
public:
	PawnMove() : Move() {}
	PawnMove(Board* board, Piece* piece, int dest) : Move(board, piece, dest, NULL) {}
	~PawnMove(){
		// Destructor
	}
	Board* execute() override;
	std::string toString() {
		std::stringstream ss;
		ss << "PawnMove[" << piece << ", " << destination << "]";
		return ss.str();
	}
};

#endif