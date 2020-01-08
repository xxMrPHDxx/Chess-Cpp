#include "AttackMove.h"

Board* AttackMove::execute(){
	BoardBuilder builder;
	for(Piece* piece : board->getAllActivePieces()){
		if(this->piece == piece || this->attackedPiece == piece) continue;
		builder.setPiece(piece);
	}
	builder.setPiece(piece->makeMove(destination));
	builder.setMoveMaker(1-board->getCurrentPlayer()->getAlliance());
	return builder.build();
}

std::string AttackMove::toString(){
	std::stringstream ss;
	ss << "AttackMove[" << this->piece->toString() << ", ";
	ss << this->destination << ", " << this->attackedPiece << "]"; 
	return ss.str();
}