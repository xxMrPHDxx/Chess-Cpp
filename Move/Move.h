#ifndef MOVE_H
#define MOVE_H

#include "MoveStatus.h"
#include "MoveTransition.h"

class Board;
class Piece;

class Move {
protected:
	Board *board;
	Piece *piece, *attackedPiece;
	int destination; 
public:
	Move() {
		this->board = NULL;
		this->piece = NULL;
		this->destination = -1;
		this->attackedPiece = NULL;
	}
	Move(Board* board, Piece* piece, int destination, Piece* attackedPiece) {
		this->board = board;
		this->piece = piece;
		this->destination = destination;
		this->attackedPiece = attackedPiece;
	}
	virtual ~Move(){
		// Destroy pointers
	}
	Board* getBoard() { return this->board; }
	Piece* getPiece() { return this->piece; }
	int getPosition() { return this->piece->getPosition(); }
	int getDestination() { return this->destination; }
	bool isAttack() { return this->attackedPiece != NULL; }
	Piece* getAttackedPiece() { return this->attackedPiece; }
	// Abstract methods
	virtual Board* execute() = 0;
	virtual std::string toString() { return "Move[]"; }
};

#endif