#ifndef ENPASSANT_ATTACK_MOVE_H
#define ENPASSANT_ATTACK_MOVE_H

#include "Move.h"
#include "../Piece/Pawn.h"

class PawnEnPassantAttackMove : public Move {
public:
	PawnEnPassantAttackMove() : Move() {}
	PawnEnPassantAttackMove(Board* b, Piece* p, int d, Piece* ap) : Move(b, p, d, ap) {}
	~PawnEnPassantAttackMove(){ 
		// Destructor
	} 
	Board* execute() override;
	std::string toString() {
		std::stringstream ss;
		ss << "PawnEnPassantAttackMove[" << piece << ", " << destination << "]";
		return ss.str();
	}
};

#endif