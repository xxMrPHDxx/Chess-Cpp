#ifndef MOVE_FACTORY_H
#define MOVE_FACTORY_H

class Move;
class Board;

class MoveFactory {
public:
	MoveFactory(){ throw std::invalid_argument("Cannot instantiate MoveFactory!"); }
	static Move* createMove(Board* board, int source, int destination);
};

#endif