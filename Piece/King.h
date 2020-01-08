#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
private:
	int CANDIDATE_OFFSETS[8] = { -9, -8, -7, -1, 1, 7, 8, 9 };
public:
	King() : Piece() {}
	~King() {
		// Destroy stuff!
	}
	King(int position, int ally) : Piece(position, 4, ally) {}
	King(int p, int a, bool fm) : Piece(p, 4, a, fm) {}
	std::vector<Move*> calculateLegalMoves(Board* board) override;
	bool isFirstColumnExclusion(int pos, int offset) override {
		return BoardUtils::isFirstColumn(pos) && (offset == -9 || offset == -1 || offset == 7);
	}
	bool isSecondColumnExclusion(int pos, int offset) override { return false; }
	bool isSeventhColumnExclusion(int pos, int offset) override { return false; }
	bool isEighthColumnExclusion(int pos, int offset) override {
		return BoardUtils::isEighthColumn(pos) && (offset == -7 || offset == 1 || offset == 9);
	}
	King* makeMove(int dest) override {
		return new King(dest, ally, false);
	}
};

#endif