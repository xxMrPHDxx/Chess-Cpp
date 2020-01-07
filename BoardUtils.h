#ifndef BOARD_H
#define BOARD_H

class BoardUtils {
public:
	static unsigned int NUM_TILES = 64;
	static unsigned int NUM_ROWS = 64;
	static bool isValidTile(unsigned int pos){
		return pos >= 0 && pos < 64;
	}
};

#endif