#ifndef PIECE_H
#define PIECE_H

#include <ostream>
#include <sstream>
#include "../BoardUtils.h"

class Move;
class Board;

class Piece {
protected:
	int position;
	int type;
	int ally;
	bool firstMove = true;
public:
	Piece(){
		position = type = ally = -1;
	}
	Piece(int position, int type, int ally){
		this->position = position;
		this->type = type;
		this->ally = ally;
	}
	Piece(int p, int t, int a, bool firstMove) : Piece(p, t, a) {
		this->firstMove = firstMove;
	}
	virtual ~Piece(){
		// Nothing to destruct!
	}
	int getPosition(){ return this->position; }
	int getType(){ return this->type; }
	int getAlliance(){ return this->ally; }
	bool isWhite(){ return this->ally == 0; }
	bool isBlack(){ return this->ally == 1; }
	bool isFirstMove(){ return this->firstMove; }
	virtual int getDirection(){ return this->ally == 0 ? -1 : 1; }
	virtual int getSpriteIndex(){
		return (1-ally) * 6 + type;
	}
	virtual std::string toString(){
		bool w = false;
		switch(ally){
			case 0: // WHITE
				w = !w; break;
			case 1: // BLACK
				break;
			default: throw std::invalid_argument("Invalid ALliance!");
		}
		switch(type){ // ROOK, KNIGHT, BISHOP, QUEEN, KING, PAWN
			case 0: // ROOK
				return w ? "R" : "r"; break;
			case 1: // KNIGHT
				return w ? "N" : "n"; break;
			case 2: // BISHOP
				return w ? "B" : "b"; break;
			case 3: // QUEEN
				return w ? "Q" : "q"; break;
			case 4: // KING
				return w ? "K" : "k"; break;
			case 5: // Pawn
				return w ? "P" : "p"; break;
			default: throw std::invalid_argument("Invalid Piece Type!");
		}
	}
	// Abstract methods
	virtual std::vector<Move*> calculateLegalMoves(Board* board) = 0;
	virtual bool hasExclusion(int pos, int offset){
		return isFirstColumnExclusion(pos, offset) ||
			isSecondColumnExclusion(pos, offset) ||
			isSeventhColumnExclusion(pos, offset) ||
			isEighthColumnExclusion(pos, offset);
	}
	virtual bool isFirstColumnExclusion(int pos, int offset) = 0;
	virtual bool isSecondColumnExclusion(int pos, int offset) = 0;
	virtual bool isSeventhColumnExclusion(int pos, int offset) = 0;
	virtual bool isEighthColumnExclusion(int pos, int offset) = 0;
	virtual Piece* makeMove(int dest) = 0;
	static int getDistance(Piece* p1, Piece* p2){
		int a = p1->getPosition(), b = p2->getPosition();
		return a > b ? (a - b) : (b - a);
	}
	friend std::ostream& operator <<(std::ostream& out, Piece* piece){
		int position, type, ally;
		position = piece->position;
		type = piece->type;
		ally = piece->ally;
		if(position == -1 || type == -1 || ally == -1) throw std::invalid_argument("Invalid Piece!");
		std::stringstream ss;
		switch(ally){
			case 0: // WHITE
				ss << "White"; break;
			case 1: // BLACK
				ss << "Black"; break;
		}
		switch(type){ // ROOK, KNIGHT, BISHOP, QUEEN, KING, PAWN
			case 0: // ROOK
				ss << "Rook"; break;
			case 1: // KNIGHT
				ss << "Knight"; break;
			case 2: // BISHOP
				ss << "Bishop"; break;
			case 3: // QUEEN
				ss << "Queen"; break;
			case 4: // KING
				ss << "King"; break;
			case 5: // Pawn
				ss << "Pawn"; break;
			default: throw std::invalid_argument("Invalid Piece Type!");
		}
		if(position < 0 || position >= 64) throw std::invalid_argument("Invalid board position!");
		ss << "[" << position << "]";
		return out << ss.str();
	}
};

#endif