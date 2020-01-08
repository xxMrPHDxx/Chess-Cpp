#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece {
private:
	const int CANDIDATE_OFFSETS[8] = { -9, -8, -7, -1, 1, 7, 8, 9 };
public:
	Queen() : Piece() {}
	Queen(int position, int ally) : Piece(position, 3, ally) {}
	Queen(int p, int a, bool fm) : Piece(p, 3, a, fm) {}
	~Queen(){
		// Destructor
	}
	std::vector<Move*> calculateLegalMoves(Board* board) override;
	bool isFirstColumnExclusion(int pos, int offset) override {
		return BoardUtils::isFirstColumn(pos) && (offset == -9 || offset == -1 || offset == 7);
	}
	bool isSecondColumnExclusion(int pos, int offset) override { return false; }
	bool isSeventhColumnExclusion(int pos, int offset) override { return false; }
	bool isEighthColumnExclusion(int pos, int offset) override {
		return BoardUtils::isEighthColumn(pos) && (offset == -7 || offset == 1 || offset == 9);
	}
	Queen* makeMove(int dest) override {
		return new Queen(dest, ally, false);
	}
};

#endif