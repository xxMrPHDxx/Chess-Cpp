#include "Bishop.h"
#include "../Move/AttackMove.h"
#include "../Move/MajorMove.h"

std::vector<Move*> Bishop::calculateLegalMoves(Board* board){
	std::vector<Move*> legalMoves;
	for(const int offset : CANDIDATE_OFFSETS){
		int dest = this->position;
		while(BoardUtils::isValidTile(dest) && BoardUtils::isValidTile(dest+offset)){
			if(hasExclusion(dest, offset)) break;
			dest += offset;

			Tile* tile = board->getTile(dest);
			if(tile->isOccupied()){
				Piece* piece = tile->getPiece();
				if(piece->getAlliance() != ally){
					legalMoves.push_back(new AttackMove(board, this, dest, piece));
				}
				break;
			}else{
				legalMoves.push_back(new MajorMove(board, this, dest));
			}
		}
	}
	return legalMoves;
}