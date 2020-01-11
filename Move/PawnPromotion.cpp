#include "PawnPromotion.h"

Board* PawnPromotion::execute(){
	BoardBuilder builder;
	for(Piece* piece : board->getAllActivePieces()){
		if(this->piece == piece) continue;
		builder.setPiece(piece);
	}
	builder.setPiece(new Queen(destination, piece->getAlliance()));
	builder.setMoveMaker(1-board->getCurrentPlayer()->getAlliance());
	return builder.build();
}