#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece {
private:
	int CANDIDATE_OFFSETS[4] = { -9, -7, 7, 9 };
public:
	Bishop() : Piece() {}
	Bishop(int position, int ally) : Piece(position, 2, ally) {}
	Bishop(int p, int a, bool fm) : Piece(p, 2, a, fm) {}
	~Bishop(){
		// Destruct pointers
	}
	std::vector<Move*> calculateLegalMoves(Board* board) override;
	bool isFirstColumnExclusion(int pos, int offset) override {
		return BoardUtils::isFirstColumn(pos) && (offset == -9 || offset == 7);
	}
	bool isSecondColumnExclusion(int pos, int offset) override { return false; }
	bool isSeventhColumnExclusion(int pos, int offset) override { return false; }
	bool isEighthColumnExclusion(int pos, int offset) override {
		return BoardUtils::isEighthColumn(pos) && (offset == -7 || offset == 9);
	}
	Bishop* makeMove(int dest) override {
		return new Bishop(dest, ally, false);
	}
};

#endif