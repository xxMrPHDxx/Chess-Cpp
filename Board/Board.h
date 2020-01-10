#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include "../BoardUtils.h"
#include "../Player/Player.h"

class BoardBuilder;

class Board {
private:
	std::vector<Tile*> tiles;
	WhitePlayer* whitePlayer;
	BlackPlayer* blackPlayer;
	std::vector<Piece*> blackPieces, whitePieces;
	Player* currentPlayer;
	Piece* enPassantPawn;
public:
	Board(){ throw std::invalid_argument("Cannot instantiate Board! Use builder instead."); }
	Board(BoardBuilder& builder);
	virtual ~Board(){
		delete whitePlayer, blackPlayer, currentPlayer, enPassantPawn;
	}
	Tile* getTile(int position){
		return this->tiles[position];
	}
	std::vector<Tile*>& getTiles(){ return this->tiles; }
	Player* getWhitePlayer(){ return this->whitePlayer; } 
	Player* getBlackPlayer(){ return this->blackPlayer; } 
	std::vector<Piece*> getWhitePieces(){ return this->whitePieces; }
	std::vector<Piece*> getBlackPieces(){ return this->blackPieces; }
	Player* getCurrentPlayer(){ return this->currentPlayer; } 
	Player* getOpponentPlayer(){
		return currentPlayer == whitePlayer ? (Player*)blackPlayer : (Player*)whitePlayer;
	} 
	Piece* getEnPassantPawn(){ return this->enPassantPawn; }
	bool hasEnPassantPawn(){ return this->enPassantPawn != NULL; }
	std::vector<Piece*> getAllActivePieces() {
		std::vector<Piece*> pieces;
		for(Piece* piece : whitePieces) pieces.push_back(piece);
		for(Piece* piece : blackPieces) pieces.push_back(piece);
		return pieces;
	}
	friend std::ostream& operator <<(std::ostream& out, Board* board){
		for(int i=0,r=0;r<8;r++){
			for(int c=0;c<8;c++,i++){
				out << board->getTile(i)->toString();
				if(c < 7) out << " "; 
			}
			if(r < 7) out << "\n"; 
		}
		return out;
	}
	// static methods
	static Board* createStandardBoard();
};

class BoardBuilder {
private:
	int ally = -1;
public:
	std::vector<Tile*> tiles;
	Piece* enPassantPawn = NULL;
	BoardBuilder();
	BoardBuilder& setPiece(Piece* piece);
	BoardBuilder& setMoveMaker(int ally);
	BoardBuilder& setEnPassantPawn(Piece* pawn);
	Board* build();
	Player* choosePlayer(WhitePlayer* white, BlackPlayer* black);
};

#endif