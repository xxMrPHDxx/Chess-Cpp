#include "PawnJump.h"

Board* PawnJump::execute(){
	BoardBuilder builder;
	for(Piece* piece : board->getAllActivePieces()){
		if(this->piece == piece) continue;
		builder.setPiece(piece);
	}
	Piece* piece = piece->makeMove(destination);
	builder.setPiece(piece);
	if(enPassant) builder.setEnPassantPawn(piece);
	builder.setMoveMaker(1-board->getCurrentPlayer()->getAlliance());
	return builder.build();
}