#include "Player.h"
#include "../Board/Board.h"

Player::Player(int ally, Board* board, 
		std::vector<Piece*> activePieces, 
		std::vector<Piece*> opponentActivePieces) {
	this->ally = ally;
	this->activePieces = activePieces;

	std::vector<Move*> legals         = calculateLegalMoves(board, activePieces, ally);
	std::vector<Move*> opponentLegals = calculateLegalMoves(board, opponentActivePieces, 1-ally);

	this->legalMoves = legals;
	this->king = NULL;
	for(Tile* tile : board->getTiles()){
		if(tile->isOccupied() && tile->getPiece()->getAlliance() == ally && tile->getPiece()->getType() == 4){
			this->king = tile->getPiece();
		}
	}
	if(this->king == NULL){
		std::stringstream ss;
		ss << "Illegal State: King not found for ";
		ss << (this->ally == 0 ? "White" : "Black");
		ss << " Player!";
		throw std::invalid_argument(ss.str());
	}
}

std::vector<Move*> Player::calculateLegalMoves(Board* board, std::vector<Piece*> pieces, int ally){
	std::vector<Move*> legalMoves;
	for(Piece* piece : pieces){
		for(Move* move : piece->calculateLegalMoves(board)){
			legalMoves.push_back(move);
		}
	}
	return legalMoves;
}