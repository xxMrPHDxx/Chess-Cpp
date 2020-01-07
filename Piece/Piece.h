#ifndef PIECE_H
#define PIECE_H

#include <ostream>
#include <sstream>

class Move;
class Board;

class Piece {
protected:
	unsigned int position;
	unsigned int type;
	unsigned int ally;
public:
	Piece(){
		position = type = ally = -1;
	}
	Piece(unsigned int position, unsigned int type, unsigned int ally){
		this->position = position;
		this->type = type;
		this->ally = ally;
	}
	virtual ~Piece(){
		// Nothing to destruct!
	}
	unsigned int getPosition(){ return this->position; }
	unsigned int getType(){ return this->type; }
	unsigned int getAlliance(){ return this->ally; }
	friend std::ostream& operator <<(std::ostream& out, Piece* piece){
		unsigned int position, type, ally;
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
	virtual std::vector<Move*> calculateLegalMoves(const Board* board) = 0;
};

#endif