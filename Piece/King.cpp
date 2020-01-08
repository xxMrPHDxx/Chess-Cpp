#include "King.h"

std::vector<Move*> King::calculateLegalMoves(Board* board){
	std::vector<Move*> legalMoves;
	int dest;
	for(const int offset : CANDIDATE_OFFSETS){
		dest = this->position + offset;
		if(BoardUtils::isValidTile(dest)){
			if(hasExclusion(this->position, offset)) continue;

			Tile* tile = board->getTile(dest);
			if(tile->isOccupied()){
				Piece* piece = tile->getPiece();
				if(piece->getAlliance() != this->ally){
					legalMoves.push_back(new AttackMove(board, this, dest, piece));
				}
			}else{
				legalMoves.push_back(new MajorMove(board, this ,dest));
			}
		}
	}
	return legalMoves;
}