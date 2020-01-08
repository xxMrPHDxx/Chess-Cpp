#ifndef ATTACK_MOVE
#define ATTACK_MOVE

#include "Move.h"

class AttackMove : public Move {
public:
	AttackMove() : Move() {}
	AttackMove(Board* board, Piece* piece, int destination, Piece* attackedPiece) : Move(board, piece, destination, attackedPiece) {}
	~AttackMove(){
		// Destroy stuff
	}
	Board* execute() override;
	std::string toString() override;
};

#endif