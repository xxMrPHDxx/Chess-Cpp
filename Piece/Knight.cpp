#include "Knight.h"

std::vector<Move*> Knight::calculateLegalMoves(const Board* board){
	std::vector<Move*> legalMoves;
	for(const int offset : this->CANDIDATE_OFFSETS){
		std::cout << "Offset: " << offset << std::endl;
	}
	return legalMoves;
}