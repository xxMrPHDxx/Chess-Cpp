#ifndef PAWN_JUMP_H
#define PAWN_JUMP_H

#include "Move.h"

class PawnJump : public Move {
private:
	bool enPassant;
public:
	PawnJump() : Move() {}
	PawnJump(Board* b, Piece* p, int d, bool enPassant) : Move(b, p, d, NULL) {
		this->enPassant = enPassant;
	}
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