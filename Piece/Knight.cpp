#include "Knight.h"
#include "../Move/AttackMove.h"
#include "../Move/MajorMove.h"

std::vector<Move*> Knight::calculateLegalMoves(Board* board) {
	std::vector<Move*> legalMoves;
	for(const int offset : CANDIDATE_OFFSETS){
		int dest = position + offset;
		if(BoardUtils::isValidTile(dest)){
			if(hasExclusion(position, offset)) continue;

			if(board->getTile(dest)->isOccupied()){
				Piece* piece = board->getTile(dest)->getPiece();
				if(piece->getAlliance() != ally){
					legalMoves.push_back(new AttackMove(board, this, dest, piece));
				} 
			}else{
				legalMoves.push_back(new MajorMove(board, this, dest));
			}
		}
	}
	return legalMoves;
}