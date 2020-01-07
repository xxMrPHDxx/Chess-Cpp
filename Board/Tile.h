#ifndef TILE_H
#define TILE_H

#include <sstream>
#include "../Piece/Piece.h"

class Board;

class Tile {
private:
	int position;
	Piece* piece;
public:
	Tile(){
		position = -1;
		piece = NULL;
	}
	Tile(int position, Piece* piece){
		this->position = position;
		this->piece = piece;
	}
	Tile(int position) : Tile(position, NULL) {}
	bool isOccupied(){
		return this->piece != NULL;
	}
	Piece* getPiece(){ return this->piece; }
	friend std::ostream& operator <<(std::ostream& out, Tile* tile){
		if(tile->position < 0 || tile->position >= 64) throw std::invalid_argument("Invalid Tile Position!");
		std::stringstream ss;
		if(tile->isOccupied()) ss << "Occupied";
		out << ss.str() << "Tile[";
		if(tile->piece != NULL) out << tile->piece;
		else out << tile->position;
		return out << "]";
	}
	virtual std::string toString(){
		return !isOccupied() ? "-" : this->piece->toString();
	}
};

#endif