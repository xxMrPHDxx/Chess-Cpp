#include "Pawn.h"
#include "../Move/PawnJump.h"
#include "../Move/PawnMove.h"
#include "../Move/PawnAttackMove.h"

std::vector<Move*> Pawn::calculateLegalMoves(Board* board){
	std::vector<Move*> legalMoves;
	for(int offset : CANDIDATE_OFFSETS){
		int dest = position + offset * getDirection();

		if(BoardUtils::isValidTile(dest)){
			if(hasExclusion(position, offset * getDirection())) continue;

			Tile* tile = board->getTile(dest);
			Tile* behindTile = board->getTile(dest - 8 * getDirection());
			switch(offset){
				case 16: // Pawn Jump
					if(!tile->isOccupied() && !behindTile->isOccupied() && isFirstMove()){
						legalMoves.push_back(new PawnJump(board, this, dest));
					}
					break;
				case 8: // Pawn Move
					if(!tile->isOccupied()){
						if(isWhite() && BoardUtils::isSecondRow(position)){
							// White's Pawn Promotion
						}else if(isBlack() && BoardUtils::isSeventhRow(position)){
							// Black's Pawn Promotion
						}else{
							legalMoves.push_back(new PawnMove(board, this, dest));
						}
					}
					break;
				case 7: // PawnAttackMove
				case 9:
					if(tile->isOccupied()){
						Piece* piece = tile->getPiece();
						if(piece->getAlliance() != ally){
							if(isWhite() && BoardUtils::isSecondRow(position)){
								// White's Pawn Promotion
							}else if(isBlack() && BoardUtils::isSeventhRow(position)){
								// Black's Pawn Promotion
							}else{
								legalMoves.push_back(new PawnAttackMove(board, this, dest, piece));
							}
						}
					}
			}
		}
	}
	return legalMoves;
}