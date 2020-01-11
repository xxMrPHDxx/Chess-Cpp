#include "CastlingMove.h"

Board* CastlingMove::execute(){
	BoardBuilder builder;
	for(Piece* piece : board->getAllActivePieces()){
		if(this->piece == piece || this->king == piece) continue;
		builder.setPiece(piece);
	}
	builder.setPiece(piece->makeMove(destination)); // Set new rook position
	builder.setPiece(king->makeMove(kingDest)); // Set new king position
	builder.setMoveMaker(1-board->getCurrentPlayer()->getAlliance());
	return builder.build();
}