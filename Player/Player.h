#ifndef PLAYER_H
#define PLAYER_H

class Move;
class Board;
class Piece;

class Player {
private:
	static std::vector<Move*> calculateLegalMoves(Board* board, std::vector<Piece*> pieces, int ally);
protected:
	int ally = -1;
	std::vector<Piece*> activePieces;
	std::vector<Move*> legalMoves;
	Piece* king;
	bool inCheck = false;
public:
	Player(){}
	Player(int ally, Board* board, std::vector<Piece*> activePieces, std::vector<Piece*> opponentActivePieces);
	virtual ~Player(){
		// Destructor
	}
	int getAlliance(){ return this->ally; }
	std::vector<Piece*> getActivePieces(){ return this->activePieces; }
	std::vector<Move*> getLegalMoves(){ return this->legalMoves; }
	Piece* getKing(){ return this->king; }
	Player* getOpponent();
	bool isInCheck(){ return this->inCheck; }
	bool isInCheckMate();
	bool isInStaleMate(){ return false; }
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
	WhitePlayer(Board* b, std::vector<Piece*> ap, std::vector<Piece*> oap) : Player(0, b, ap, oap) {}
};

class BlackPlayer : public Player {
public:
	BlackPlayer() : Player() {}
	BlackPlayer(Board* b, std::vector<Piece*> ap, std::vector<Piece*> oap) : Player(1, b, ap, oap) {}
};

#endif