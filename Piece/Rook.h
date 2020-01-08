#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {
private:
	const int CANDIDATE_OFFSETS[4] = { -8, -1, 1, 8 };
public:
	Rook() : Piece() {}
	Rook(int position, int ally) : Piece(position, 0, ally) {}
	Rook(int p, int a, bool fm) : Piece(p, 0, a, fm) {}
	std::vector<Move*> calculateLegalMoves(Board* board) override;
	bool isFirstColumnExclusion(int pos, int offset) override {
		return BoardUtils::isFirstColumn(pos) && offset == -1;
	}
	bool isSecondColumnExclusion(int pos, int offset) override { return false; }
	bool isSeventhColumnExclusion(int pos, int offset) override { return false; }
	bool isEighthColumnExclusion(int pos, int offset) override {
		return BoardUtils::isEighthColumn(pos) && offset == 1;
	}
	Rook* makeMove(int dest) override {
		return new Rook(dest, ally, false);
	}
};

#endif