#include "Board.h"

#include "../Player/Player.h"

#include "../Piece/Rook.h"
#include "../Piece/Knight.h"
#include "../Piece/Bishop.h"
#include "../Piece/Queen.h"
#include "../Piece/King.h"
#include "../Piece/Pawn.h"

#include "../Move/Move.h"

Board::Board(BoardBuilder& builder){
	this->tiles = builder.tiles;

	std::vector<Piece*> whiteActivePieces, blackActivePieces;
	for(Tile* tile : tiles){
		if(tile->isOccupied()){
			Piece* piece = tile->getPiece();
			if(piece->getAlliance() == 0){
				whiteActivePieces.push_back(piece);
			}else if(piece->getAlliance() == 1){
				blackActivePieces.push_back(piece);
			}
		}
	}
	
	this->whitePlayer = new WhitePlayer(this, whiteActivePieces, blackActivePieces);
	this->blackPlayer = new BlackPlayer(this, blackActivePieces, whiteActivePieces);
	this->currentPlayer = builder.choosePlayer(whitePlayer, blackPlayer);
}

std::vector<Piece*> Board::getAllActivePieces(){
	std::vector<Piece*> activePieces;
	for(Piece* piece : whitePlayer->getActivePieces()){
		activePieces.push_back(piece);
	}
	for(Piece* piece : blackPlayer->getActivePieces()){
		activePieces.push_back(piece);
	}
	return activePieces;
}

Board* Board::createStandardBoard(){
	BoardBuilder builder;
	// Black and White Pawns
	for(int i=0;i<2;i++){ 
		for(int j=i?8:48,k=0;k<8;k++){
			builder.setPiece(new Pawn(j+k, i));
		}
	}

	return builder
		// Black Pieces
		.setPiece(new Rook(0, 1))
		.setPiece(new Knight(1, 1))
		.setPiece(new Bishop(2, 1))
		.setPiece(new King(3, 1))
		.setPiece(new Queen(4, 1))
		.setPiece(new Bishop(5, 1))
		.setPiece(new Knight(6, 1))
		.setPiece(new Rook(7, 1))
		// White Pieces
		.setPiece(new Rook(63-0, 0))
		.setPiece(new Knight(63-1, 0))
		.setPiece(new Bishop(63-2, 0))
		.setPiece(new Queen(63-3, 0))
		.setPiece(new King(63-4, 0))
		.setPiece(new Bishop(63-5, 0))
		.setPiece(new Knight(63-6, 0))
		.setPiece(new Rook(63-7, 0))

		// Pawn Attack Test
		.setPiece(new Pawn(41, 1))
		.setPiece(new Pawn(43, 1))
		// End Pawn Attack Test

		// White moves first!
		.setMoveMaker(0)

		.build();
}

BoardBuilder::BoardBuilder(){
	for(int i=0;i<BoardUtils::NUM_TILES;i++){
		this->tiles.push_back(new Tile(i));
	}
}

BoardBuilder& BoardBuilder::setPiece(Piece* piece){
	if(piece == NULL) return *this;
	this->tiles[piece->getPosition()] = new Tile(piece);
	return *this;
}

BoardBuilder& BoardBuilder::setMoveMaker(int ally){
	this->ally = ally;
}

Board* BoardBuilder::build(){
	return new Board(*this);
}

Player* BoardBuilder::choosePlayer(WhitePlayer* white, BlackPlayer* black){
	switch(this->ally){
		case 0: return white;
		case 1: return black;
		default: throw std::invalid_argument("Invalid move maker alliance!");
	}
}