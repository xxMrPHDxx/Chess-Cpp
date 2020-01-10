#ifndef PLAYER_H
#define PLAYER_H

class Move;
class Board;
class Piece;

class Player {
protected:
	int ally = -1;
	Board* board;
	std::vector<Move*> legalMoves;
	Piece* king;
	bool inCheck = false;
public:
	Player(){}
	Player(int ally, Board* board, std::vector<Move*> moves, std::vector<Move*> opponentMoves);
	virtual ~Player(){
		// Destructor
	}
	int getAlliance(){ return this->ally; }
	std::vector<Move*> getLegalMoves(){ return this->legalMoves; }
	Piece* getKing(){ return this->king; }
	bool isInCheck(){ return this->inCheck; }
	bool isInCheckMate();
	bool isInStaleMate();
	bool hasEscapeMoves();
	virtual Player* getOpponent() = 0;
	virtual std::vector<Piece*> getActivePieces() = 0;
	static std::vector<Move*> calculateAttackOnTile(std::vector<Move*> legalMoves, int pos);
	friend std::ostream& operator <<(std::ostream& out, Player* player){
		if(player->ally == -1) throw std::invalid_argument("Invalid player ally!");
		switch(player->ally){
			case 0: // White
				out << "White"; break;
			case 1: //
				out << "Black"; break;
			default: throw std::invalid_argument("Invalid player ally!");
		}
		return out << "Player[]";
	}
};

class WhitePlayer : public Player {
public:
	WhitePlayer() : Player() {}
	WhitePlayer(Board* b, std::vector<Move*> m, std::vector<Move*> om) : Player(0, b, m, om) {}
	Player* getOpponent() override;
	std::vector<Piece*> getActivePieces() override;
};

class BlackPlayer : public Player {
public:
	BlackPlayer() : Player() {}
	BlackPlayer(Board* b, std::vector<Move*> m, std::vector<Move*> om) : Player(1, b, m, om) {}
	Player* getOpponent() override;
	std::vector<Piece*> getActivePieces() override;
};

#endif