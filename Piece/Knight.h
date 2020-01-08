#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {
private:
	int CANDIDATE_OFFSETS[8] = { -17, -15, -10, -6, 6, 10, 15, 17 };
public:
	Knight() : Piece() {}
	Knight(int position, int ally) : Piece(position, 1, ally) {}
	Knight(int p, int a, bool fm) : Piece(p, 1, a, fm) {}
	~Knight() {
		// Destroy stuff!
	}
	std::vector<Move*> calculateLegalMoves(Board* board) override;
	bool isFirstColumnExclusion(int pos, int offset) override {
		return BoardUtils::isFirstColumn(pos) && (offset == -17 || offset == -10 || offset == 6 || offset == 15);
	}
	bool isSecondColumnExclusion(int pos, int offset) override {
		return BoardUtils::isSecondColumn(pos) && (offset == -10 || offset == 6);
	}
	bool isSeventhColumnExclusion(int pos, int offset) override {
		return BoardUtils::isSeventhColumn(pos) && (offset == -6 || offset == 10);
	}
	bool isEighthColumnExclusion(int pos, int offset) override {
		return BoardUtils::isEighthColumn(pos) && (offset == -15 || offset == -6 || offset == 10 || offset == 17);
	}
	Knight* makeMove(int dest){
		return new Knight(dest, ally, false);
	}
};

#endif