#ifndef PAWN_JUMP_H
#define PAWN_JUMP_H

#include "Move.h"

class PawnJump : public Move {
public:
	PawnJump() : Move() {}
	PawnJump(Board* board, Piece* piece, int dest) : Move(board, piece, dest, NULL) {}
	~PawnJump(){ 
		// Destructor
	} 
	Board* execute() override;
	std::string toString() {
		std::stringstream ss;
		ss << "PawnJump[" << piece << ", " << destination << "]";
		return ss.str();
	}
};

#endif