#include <iostream>
#include <SFML/Graphics.hpp>

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

template<typename T> std::ostream& operator <<(std::ostream& out, std::vector<T> vec){
	int length = vec.size();
	for(int i=0;i<length;i++){
		out << vec[i];
		if(i < length-1) out << ", ";
	}
	return out;
}

void drawBoard(RenderWindow& app, Sprite sPieces[], Board* board){
	for(int i=0, row, col;i<BoardUtils::NUM_TILES;i++){
		Tile* tile = board->getTile(i);
		if(tile->isOccupied()){
			row = i / BoardUtils::NUM_ROWS;
			col = i % BoardUtils::NUM_ROWS;
			Piece* piece = tile->getPiece();
			Sprite& s = sPieces[piece->getSpriteIndex()];
			s.setPosition(28 + col*56, 28 + row*56);
			app.draw(s);
		}
	}
}

class Hint {
public:
	bool attack;
	Vector2i pos;
	Hint(){}
	Hint(bool attack, Vector2i pos){
		this->attack = attack;
		this->pos = pos;
	}
};

int main(){
	RenderWindow app(VideoMode(504, 504), "Chess");

	Board* board = Board::createStandardBoard();

	Texture t1, t2, t3;
	t1.loadFromFile("img/board.png");
	t2.loadFromFile("img/figures.png");
	t3.loadFromFile("img/ui.png");

	Sprite sBoard(t1), sPieces[12], sGreenDot(t3), sRedDot(t3), sCheck(t3), sCheckMate(t3), sStaleMate(t3);
	for(int i=0,n=0;i<2;i++){
		for(int j=0;j<6;j++){
			sPieces[n] = Sprite(t2);
			sPieces[n++].setTextureRect(IntRect(j*56, i*60, 56, 56));
		}
	}
	sGreenDot.setTextureRect(IntRect(0*56, 0*56, 56, 56));
	sRedDot.setTextureRect(IntRect(1*56, 0*56, 56, 56));
	sCheck.setTextureRect(IntRect(0*56, 1*56, 56, 56));
	sCheckMate.setTextureRect(IntRect(1*56, 1*56, 56, 56));
	sStaleMate.setTextureRect(IntRect(2*56, 1*56, 56, 56));

	Event e;
	Vector2i mouse;
	int mRow, mCol, mIndex;
	Tile *sourceTile, *destTile;
	IntRect boardBounds(28, 28, 56*8, 56*8);
	bool shouldRedraw = true, shouldRedrawHint;
	while(app.isOpen()){
		std::vector<Hint> hintPositions;

		while(app.pollEvent(e)){
			switch(e.type){
				case Event::Closed: app.close(); break;
				case Event::MouseButtonPressed:
					switch(e.key.code){
						case Mouse::Left:
							mouse = Mouse::getPosition(app);
							if(boardBounds.contains(mouse.x, mouse.y)){
								mRow = (mouse.y - 28) / 56;
								mCol = (mouse.x - 28) / 56;
								mIndex = mRow * BoardUtils::NUM_ROWS + mCol;
								if(sourceTile == NULL){
									sourceTile = board->getTile(mIndex);
									if(!sourceTile->isOccupied()) sourceTile = NULL;
									else{
										float rr, cc;
										Piece* piece = sourceTile->getPiece();
										std::vector<Move*> moves = piece->calculateLegalMoves(board);
										if(board->getCurrentPlayer()->getAlliance() != piece->getAlliance() || 
											moves.size() == 0){
											sourceTile = NULL; break;
										}
										for(Move* move : moves){
											rr = move->getDestination() / BoardUtils::NUM_ROWS;
											cc = move->getDestination() % BoardUtils::NUM_ROWS;
											hintPositions.push_back(
												Hint(move->isAttack(), Vector2i((cc+0.5f)*56, (rr+0.5f)*56))
											);
										}
										shouldRedrawHint = true;
									}
								}else{
									destTile = board->getTile(mIndex);
									MoveTransition transition = MoveFactory::createMove(
										board, 
										sourceTile->getPosition(),
										destTile->getPosition()
									);
									if(transition.isSuccess()){
										Move* move = transition.getMove();
										std::cout << "Executing Move: " << move->toString() << std::endl;
										delete board;
										board = transition.getBoard();
									}else{
										std::cout << transition.getStatus() << std::endl;
									}

									sourceTile = destTile = NULL;
								}
							}
							shouldRedraw = true;
							break;
						case Mouse::Right:
							sourceTile = destTile = NULL;
							shouldRedraw = true;
							break;
					}
					break;
			}
		}

		if(shouldRedraw){
			app.draw(sBoard);
			if(shouldRedrawHint){
				Sprite s; Player* p = NULL;
				if(board->getCurrentPlayer()->isInCheckMate() || board->getOpponentPlayer()->isInCheckMate()){
					p = board->getCurrentPlayer()->isInCheckMate() ? board->getCurrentPlayer() : board->getOpponentPlayer();
					s = sCheckMate;
				}else if(board->getCurrentPlayer()->isInCheck() || board->getOpponentPlayer()->isInCheck()){
					p = board->getCurrentPlayer()->isInCheck() ? board->getCurrentPlayer() : board->getOpponentPlayer();
					s = sCheck;
				}else if(board->getCurrentPlayer()->isInStaleMate() || board->getOpponentPlayer()->isInStaleMate()){
					p = board->getCurrentPlayer()->isInStaleMate() ? board->getCurrentPlayer() : board->getOpponentPlayer();
					s = sStaleMate;
				}
				if(p != NULL){
					int pos = p->getKing()->getPosition();
					int r = pos / BoardUtils::NUM_ROWS, c = pos % BoardUtils::NUM_ROWS;
					s.setPosition((c+0.5f)*56, (r+0.5f)*56);
					app.draw(s);
				}
			}
			drawBoard(app, sPieces, board);
		}
		if(shouldRedrawHint){
			Vector2i pos;
			for(Hint hint : hintPositions){
				Sprite s = hint.attack ? sRedDot : sGreenDot;
				pos = hint.pos;
				s.setPosition(pos.x, pos.y);
				app.draw(s);
			}
		}
		if(shouldRedraw){
			app.display();
			shouldRedraw = false;
		}
	}

	return 0;
}