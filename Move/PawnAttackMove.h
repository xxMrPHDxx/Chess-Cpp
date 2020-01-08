#ifndef PAWN_ATTACK_MOVE_H
#define PAWN_ATTACK_MOVE_H

#include "Move.h"

class PawnAttackMove : public Move {
public:
	PawnAttackMove() : Move() {}
	PawnAttackMove(Board* b, Piece* p, int d, Piece* ap) : Move(b, p, d, ap) {}
	~PawnAttackMove(){
		// Destructor
	}
	Board* execute() override;
	std::string toString() override {
		std::stringstream ss;
		ss << "PawnAttackMove[" << piece << ", " << destination << "]";
		return ss.str();
	}
};

#endif