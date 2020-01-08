#ifndef BOARDUTILS_H
#define BOARDUTILS_H

class BoardUtils {
private:
	static bool inRow(int pos, int row){ return pos / BoardUtils::NUM_ROWS == row; }
	static bool inColumn(int pos, int col){ return pos % BoardUtils::NUM_ROWS == col; }
public:
	static const int NUM_TILES = 64;
	static const int NUM_ROWS = 8;
	static bool isValidTile(int pos){
		return pos >= 0 && pos < 64;
	}
	static bool isFirstColumn(int pos){ return BoardUtils::inColumn(pos, 0); }
	static bool isSecondColumn(int pos){ return BoardUtils::inColumn(pos, 1); }
	static bool isSeventhColumn(int pos){ return BoardUtils::inColumn(pos, 6); }
	static bool isEighthColumn(int pos){ return BoardUtils::inColumn(pos, 7); }
	static bool isSecondRow(int pos){ return BoardUtils::inRow(pos, 1); }
	static bool isSeventhRow(int pos){ return BoardUtils::inRow(pos, 6); }
};

#endif