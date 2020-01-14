#include "Chess.cpp"

int main(){
	Game chess;
	std::cout << chess.getBoard() << std::endl;

	IntRect boardBounds(28, 28, 56*8, 56*8);

	RenderWindow app(VideoMode(504, 504), "Chess Game!");

	Texture t1, t2, t3;
	t1.loadFromFile("img/board.png");
	t2.loadFromFile("img/figures.png");
	t3.loadFromFile("img/ui.png");

	Sprite sBoard(t1), sFigures[12], sHints[6];
	for(int i=0,n1=0,n2=0;i<2;i++){
		for(int j=0;j<6;j++){
			sFigures[n1] = Sprite(t2);
			sFigures[n1++].setTextureRect(IntRect(j*56, i*56, 56, 56));
		}
		for(int j=0;j<3;j++){
			sHints[n2] = Sprite(t3);
			sHints[n2++].setTextureRect(IntRect(j*56, i*56, 56, 56));
		}
	}

	Event e;
	Vector2i mouse;
	bool shouldRedraw=true, shouldRedrawHint;
	int mRow, mCol, mIndex;
	while(app.isOpen()){
		while(app.pollEvent(e)){
			switch(e.type){
				case Event::Closed: app.close(); break;
				case Event::MouseButtonPressed:
					switch(e.key.code){
						case Mouse::Left:
							mouse = Mouse::getPosition(app);
							if(!boardBounds.contains(mouse.x, mouse.y)) break;
							mRow = (mouse.y - 28) / 56;
							mCol = (mouse.x - 28) / 56;
							mIndex = mRow * BoardUtils::NUM_ROWS + mCol;
							if(!chess.hasSourceTile()){ // First click
								chess.setSourceTile(mIndex);
								shouldRedrawHint = true;
							}else if(!chess.hasDestinationTile()){ // Second click
								chess.moveTile(mIndex);
							}
							break;
						case Mouse::Right: chess.resetTiles(); break;
					}
					shouldRedraw = true;
					break;
			}
		}

		if(shouldRedraw){
			// Draw board background
			app.draw(sBoard);

			// Draw check, checkmate hint for king
			int s = chess.getPlayerStatus();
			if(s != -1){
				Sprite& sp = sHints[s];
				int pos = chess.getProblematicPlayer()->getKing()->getPosition();
				int r = pos / BoardUtils::NUM_ROWS, c = pos % BoardUtils::NUM_ROWS;
				sp.setPosition((c+0.5f)*56, (r+0.5f)*56);
				app.draw(sp);
			}

			// Draw board pieces
			Board* board = chess.getBoard();
			Tile* tile;
			for(int i=0,n=0,k;i<BoardUtils::NUM_ROWS;i++){
				for(int j=0;j<BoardUtils::NUM_ROWS;j++,n++){
					tile = board->getTile(n);
					if(!tile->isOccupied()) continue;
					Sprite& s = sFigures[tile->getPiece()->getSpriteIndex()];
					s.setPosition(28+j*56, 28+i*56);
					app.draw(s);
				}
			}
		}
		if(shouldRedrawHint){
			int i; Vector2i pos;
			for(Game::Hint hint : chess.getHintPositions()){
				i=0; pos = hint.pos;
				if(hint.attack) i++;
				sHints[i].setPosition(pos.x, pos.y);
				app.draw(sHints[i]);
			}
			shouldRedrawHint = false;
		}
		if(shouldRedraw){
			app.display();
			shouldRedraw = false;
		}
	}

	return 0;
}