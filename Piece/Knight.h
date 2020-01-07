#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {
private:
	int CANDIDATE_OFFSETS[8] = { -17, -15, -10, -6, 6, 10, 15, 17 };
public:
	Knight() : Piece() {}
	~Knight() {
		// Destroy stuff!
	}
	Knight(unsigned int position, unsigned int ally) : Piece(position, 1, ally) {}
	std::vector<Move*> calculateLegalMoves(const Board* board) override;
};

#endif