#ifndef BOARD_H
#define BOARD_H

class Board {
private:
	std::vector<Tile*> tiles;
public:
	Board(){
		for(int i=0;i<BoardUtils::NUM_TILES;i++){
			
		}
	}
};

#endif