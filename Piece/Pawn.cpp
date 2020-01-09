#include "Pawn.h"
#include "../Move/PawnJump.h"
#include "../Move/PawnMove.h"
#include "../Move/PawnAttackMove.h"
#include "../Move/PawnEnPassantAttackMove.h"

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
						// EnPassant Pawn
						Tile *left = board->getTile(dest-1), *right = board->getTile(dest+1);
						bool enPassantAttack = true;
						int enPassantPosition;
						if(!BoardUtils::isFirstColumn(dest-1) &&  left->isOccupied()){
							enPassantPosition = left->getPosition();
						}else if(!BoardUtils::isEighthColumn(dest+1) && right->isOccupied()){
							enPassantPosition = right->getPosition();
						}else enPassantAttack = false;
						legalMoves.push_back(new PawnJump(board, this, dest, enPassantAttack));
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
				case 7:
				case 9:
					if(tile->isOccupied()){ // PawnAttackMove
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
					}else if(board->hasEnPassantPawn()){ // EnPassant Attack
						Piece* enPassantPawn = board->getEnPassantPawn();
						Tile* behind = board->getTile(enPassantPawn->getPosition() + 8*getDirection());
						if(Piece::getDistance(this, enPassantPawn) == 1 &&
							behind->getPosition() == dest && 
							enPassantPawn->getAlliance() != ally){
							std::cout << "Pawn::this" << std::endl;
							std::cout << "\t" << this << std::endl;
							std::cout << "Pawn::enPassantPawn" << std::endl;
							std::cout << "\t" << enPassantPawn << std::endl;
							legalMoves.push_back(new PawnEnPassantAttackMove(
								board, 
								this, 
								dest, 
								enPassantPawn
							));
						}
					}
			}
		}
	}
	return legalMoves;
}