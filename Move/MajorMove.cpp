#include "MajorMove.h"
#include "../Board/Board.h"

Board* MajorMove::execute(){
	BoardBuilder builder;
	for(Piece* piece : board->getAllActivePieces()){
		if(this->piece == piece) continue;
		builder.setPiece(piece);
	}
	builder.setPiece(piece->makeMove(destination));
	builder.setMoveMaker(1-board->getCurrentPlayer()->getAlliance());
	return builder.build();
}

std::string MajorMove::toString(){
	std::stringstream ss;
	ss << "MajorMove[" << this->piece->toString() << ", " << this->destination << "]"; 
	return ss.str();
}