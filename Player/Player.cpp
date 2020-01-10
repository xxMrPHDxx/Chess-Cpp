#include "Player.h"
#include "../Board/Board.h"
#include "../Move/MoveFactory.h"
#include "../Move/MoveTransition.h"

Player::Player(int ally, Board* board, std::vector<Move*> moves, std::vector<Move*> opponentMoves) {
	this->ally = ally;
	this->board = board;
	this->legalMoves = moves;
	this->king = NULL; 
	for(Piece* piece : board->getAllActivePieces()){
		if(piece->getAlliance() == ally && piece->getType() == 4){
			this->king = piece;
		}
	}
	if(this->king == NULL){
		std::stringstream ss;
		ss << "Illegal State: King not found for ";
		ss << (this->ally == 0 ? "White" : "Black");
		ss << " Player!";
		throw std::invalid_argument(ss.str());
	}
	this->inCheck = calculateAttackOnTile(opponentMoves, king->getPosition()).size() > 0;
}

bool Player::isInCheckMate(){
	return inCheck && !hasEscapeMoves();
}

bool Player::isInStaleMate(){
	return !inCheck && !hasEscapeMoves();
}

bool Player::hasEscapeMoves(){
	std::vector<Move*> escapeMoves;
	int i = 1;
	if(inCheck)
	for(Move* move : legalMoves){
		std::cout << "Executing move: " << move->toString() << std::endl;
		// move->execute();
		MoveTransition transition = MoveFactory::createMove(move);
		// std::cout << transition.getStatus() << std::endl;
		// if(board == NULL) std::cout << "Board is NULL!" << std::endl;
		if(!transition.isSuccess()) continue;
		escapeMoves.push_back(move); i++;
	}
	// if(player->inCheck) std::cout << "Found " << i << " escape moves" << std::endl;
	return escapeMoves.size() > 0;
}

std::vector<Move*> Player::calculateAttackOnTile(std::vector<Move*> legalMoves, int pos){
	std::vector<Move*> attackMoves;
	for(Move* move : legalMoves){
		if(!move->isAttack()) continue;
		if(move->getDestination() == pos) attackMoves.push_back(move);
	}
	return attackMoves;
}

Player* WhitePlayer::getOpponent(){
	return board->getBlackPlayer();
}

Player* BlackPlayer::getOpponent(){
	return board->getWhitePlayer();
}

std::vector<Piece*> WhitePlayer::getActivePieces(){
	return this->board->getWhitePieces();
}

std::vector<Piece*> BlackPlayer::getActivePieces(){
	return this->board->getBlackPieces();
}