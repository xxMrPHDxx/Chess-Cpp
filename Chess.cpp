#include <SFML/Graphics.hpp>
#include <iostream>

#include <Board/Tile.h>
#include <Board/Board.cpp>

#include <Piece/Rook.cpp>
#include <Piece/Knight.cpp>
#include <Piece/Bishop.cpp>
#include <Piece/Queen.cpp>
#include <Piece/King.cpp>
#include <Piece/Pawn.cpp>

#include <Move/AttackMove.cpp>
#include <Move/CastlingMove.cpp>
#include <Move/MajorMove.cpp>
#include <Move/PawnMove.cpp>
#include <Move/PawnJump.cpp>
#include <Move/PawnAttackMove.cpp>
#include <Move/PawnEnPassantAttackMove.cpp>
#include <Move/PawnPromotion.cpp>
#include <Move/MoveFactory.cpp>

#include <Player/Player.cpp>

using namespace sf;

class Game {
public:
	struct Hint
	{
		bool attack;
		Vector2i pos;
	};
private:
	Board* board;
	Tile *source, *dest;
	std::vector<Hint>* hintPositions;
	Player* player;
public:
	Game(){
		this->board = Board::createStandardBoard();
		this->source = this->dest = NULL;
	}
	Board* getBoard() const { return board; }
	Player* getProblematicPlayer() const { return player; }
	int getPlayerStatus() {
		int i=-1;
		if(board->getCurrentPlayer()->isInCheckMate() || board->getOpponentPlayer()->isInCheckMate()){
			player = board->getCurrentPlayer()->isInCheckMate() ? board->getCurrentPlayer() : board->getOpponentPlayer();
			i = 4;
		}else if(board->getCurrentPlayer()->isInCheck() || board->getOpponentPlayer()->isInCheck()){
			player = board->getCurrentPlayer()->isInCheck() ? board->getCurrentPlayer() : board->getOpponentPlayer();
			i = 3;
		}else if(board->getCurrentPlayer()->isInStaleMate() || board->getOpponentPlayer()->isInStaleMate()){
			player = board->getCurrentPlayer()->isInStaleMate() ? board->getCurrentPlayer() : board->getOpponentPlayer();
			i = 5;
		}
		return i;
	}
	void setSourceTile(int index) {
		source = board->getTile(index);
		if(!source->isOccupied()) source = NULL;
		else{
			float rr, cc;
			Piece* piece = source->getPiece();
			std::vector<Move*> moves = piece->calculateLegalMoves(board);
			hintPositions = new std::vector<Hint>();
			if(board->getCurrentPlayer()->getAlliance() != piece->getAlliance() || 
				moves.size() == 0){
				source = NULL; return;
			}
			for(Move* move : moves){
				rr = move->getDestination() / BoardUtils::NUM_ROWS;
				cc = move->getDestination() % BoardUtils::NUM_ROWS;
				hintPositions->push_back({move->isAttack(), Vector2i((cc+0.5f)*56, (rr+0.5f)*56)});
			}
		}
	}
	bool hasSourceTile() const { return source != NULL; }
	Tile* getSourceTile() const { return source; }
	bool hasDestinationTile() const { return dest != NULL; }
	Tile* getDestinationTile() const { return dest; }
	void moveTile(int index) {
		if(dest == NULL){
			dest = board->getTile(index);
			MoveTransition transition = MoveFactory::createMove(
				board, 
				source->getPosition(),
				dest->getPosition()
			);
			if(transition.isSuccess()){
				Move* move = transition.getMove();
				std::cout << "Executing Move: " << move->toString() << std::endl;
				hintPositions = new std::vector<Hint>();
				delete board;
				board = transition.getBoard();
			}else{
				std::cout << transition.getStatus() << std::endl;
			}
		}
		resetTiles();
	}
	void resetTiles() { source = dest = NULL; }
	std::vector<Hint> getHintPositions() const { return *this->hintPositions; }
};