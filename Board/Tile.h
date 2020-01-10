#ifndef TILE_H
#define TILE_H

#include <sstream>
#include "../Piece/Piece.h"

class Piece;
class Board;

class Tile {
private:
	int position;
	Piece* piece;
public:
	Tile(){
		this->position = -1;
		this->piece = NULL;
	}
	Tile(int position, Piece* piece){
		this->position = position;
		this->piece = piece;
	}
	Tile(Piece* piece) : Tile(piece->getPosition(), piece) {}
	Tile(int position) : Tile(position, NULL) {}
	int getPosition(){ return this->position; }
	bool isOccupied(){ return this->piece != NULL; }
	Piece* getPiece(){ return this->piece; }
	friend std::ostream& operator <<(std::ostream& out, Tile* tile){
		if(tile->position < 0 || tile->position >= 64) throw std::invalid_argument("Invalid Tile Position!");
		std::stringstream ss;
		if(tile->isOccupied()) ss << "Occupied";
		out << ss.str() << "Tile[";
		if(tile->piece == NULL) out << tile->position;
		else out << tile->piece;
		return out << "]";
	}
	virtual std::string toString(){
		std::stringstream ss;
		ss << (!isOccupied() ? "-" : this->piece->toString());
		// ss << "[" << (this->position < 10 ? "0" : "") << this->position << "]";
		return ss.str();
	}
};

#endif