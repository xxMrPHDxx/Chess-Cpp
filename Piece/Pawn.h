#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {
private:
	const int CANDIDATE_OFFSETS[4] = { 7, 8, 9, 16 };
public:
	Pawn() : Piece() {}
	Pawn(int position, int ally) : Piece(position, 5, ally) {}
	Pawn(int p, int a, bool fm) : Piece(p, 5, a, fm) {}
	~Pawn(){
		// Destructor
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
	Pawn* makeMove(int dest) override{
		return new Pawn(dest, ally, false);
	}
};

#endif