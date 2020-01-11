#ifndef PAWN_PROMOTION_H
#define PAWN_PROMOTION_H

#include "Move.h"

class PawnPromotion : public Move {
public:
	PawnPromotion() : Move() {}
	PawnPromotion(Board* board, Piece* piece, int dest) : Move(board, piece, dest, NULL) {}
	PawnPromotion(Board* b, Piece* p, int d, Piece* attackedPiece) : Move(b, p, d, attackedPiece) {}
	~PawnPromotion(){
		// Destructor
	}
	Board* execute() override;
	std::string toString() override {
		std::stringstream ss;
		ss << "PawnPromotion[" << piece << "," << destination << "]";
		return ss.str();
	}
};

#endif