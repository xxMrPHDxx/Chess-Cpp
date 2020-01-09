#include "PawnEnPassantAttackMove.h"
#include "../Board/Board.h"

Board* PawnEnPassantAttackMove::execute(){
	BoardBuilder builder;
	for(Piece* piece : board->getAllActivePieces()){
		if(this->piece == piece || this->attackedPiece == piece) continue;
		builder.setPiece(piece);
	}
	builder.setPiece(piece->makeMove(destination));
	builder.setMoveMaker(1-board->getCurrentPlayer()->getAlliance());
	return builder.build();
}