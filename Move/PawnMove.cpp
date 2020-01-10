#include "PawnMove.h"

Board* PawnMove::execute(){
	// std::cout << "In PawnMove::execute():" << std::endl;
	BoardBuilder builder;
	for(Piece* piece : board->getAllActivePieces()){
		if(this->piece == piece) continue;
		// std::cout << "\tSetting piece: " << piece << std::endl;
		builder.setPiece(piece);
	}
	// std::cout << "\tSetting moving piece: " << piece->makeMove(destination) << std::endl;
	builder.setPiece(piece->makeMove(destination));
	// std::cout << "\tSetting next move maker." << std::endl;
	// std::cout << "\tCurrentPlayer: " << board->getCurrentPlayer() << std::endl;
	builder.setMoveMaker(1-board->getCurrentPlayer()->getAlliance());
	// std::cout << "\tBuilding new Board!" << std::endl;
	return builder.build();
}