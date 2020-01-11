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
	this->enPassantPawn = builder.enPassantPawn;

	std::vector<Move*> whiteMoves, blackMoves;
	for(Tile* tile : tiles){
		if(tile->isOccupied()){
			Piece* piece = tile->getPiece();
			if(piece->getAlliance() == 0){
				whitePieces.push_back(piece);
				for(Move* move : piece->calculateLegalMoves(this)) whiteMoves.push_back(move);
			}
			else if(piece->getAlliance() == 1){
				blackPieces.push_back(piece);
				for(Move* move : piece->calculateLegalMoves(this)) blackMoves.push_back(move);
			}
		}
	}
	
	this->whitePlayer = new WhitePlayer(this, whiteMoves, blackMoves);
	this->blackPlayer = new BlackPlayer(this, blackMoves, whiteMoves);
	this->currentPlayer = builder.choosePlayer(whitePlayer, blackPlayer);
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

BoardBuilder& BoardBuilder::setEnPassantPawn(Piece* pawn){
	this->enPassantPawn = pawn;
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

/*======================   TEST BOARDS   ====================*/

Board* createCheckBoard(){
	return BoardBuilder()
		.setPiece(new King(3, 1))
		.setPiece(new King(63-4, 0))
		.setPiece(new Queen(17, 0))
		.setMoveMaker(1)
		.build();
}

Board* createCheckMateBoard(){
	return BoardBuilder()
		.setPiece(new King(3, 1))
		.setPiece(new King(63-4, 0))
		.setPiece(new Queen(10, 0))
		.setPiece(new Queen(12, 0))
		.setMoveMaker(1)
		.build();
}

Board* createStaleMateBoard(){
	return BoardBuilder()
		.setPiece(new King(3+1, 1))
		.setPiece(new King(63-4+1, 0))
		.setPiece(new Rook(10+1, 0))
		.setPiece(new Rook(12+1, 0))
		.setMoveMaker(1)
		.build();
}

Board* createCastlingBoard(){
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
		.setPiece(new King(3, 1))
		.setPiece(new Rook(7, 1))
		// White Pieces
		.setPiece(new Rook(63-0, 0))
		.setPiece(new King(63-4, 0))
		.setPiece(new Rook(63-7, 0))
		// White moves first!
		.setMoveMaker(0)
		.build();
}