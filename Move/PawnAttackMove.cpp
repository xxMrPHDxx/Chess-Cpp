#include "PawnAttackMove.h"
#include "../Board/Board.h"
#include "../Piece/King.h"

Board* PawnAttackMove::execute(){
	BoardBuilder builder;
	for(Piece* piece : board->getAllActivePieces()){
		if(this->piece == piece || this->attackedPiece == piece) continue;
		builder.setPiece(piece);
	}
	// Move and set the new piece
	builder.setPiece(piece->makeMove(destination));
	builder.setMoveMaker(1 - board->getCurrentPlayer()->getAlliance());
	return builder.build();
}