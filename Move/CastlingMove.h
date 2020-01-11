#ifndef CASTLING_MOVE_H
#define CASTLING_MOVE_H

#include "Move.h"

class CastlingMove : public Move {
private:
	Piece* king;
	int kingDest;
public:
	CastlingMove() : Move() {}
	CastlingMove(Board* b, Piece* rook, int rookDest, Piece* king, int kingDest) : Move(b, rook, rookDest, NULL) {
		this->king = king;
		this->kingDest = kingDest;
	}
	~CastlingMove(){
		// Destructor
	}
	Piece* getKing() { return this->king; }
	int getKingDestination() { return this->kingDest; }
	Board* execute() override;
	std::string toString() override {
		std::stringstream ss;
		ss << "CastlingMove[" << piece << "," << king << "]"; 
		return ss.str();
	}
};

#endif