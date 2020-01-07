#include <iostream>
#include <SFML/Graphics.hpp>

#include <Board/Tile.h>
#include <Piece/Knight.cpp>

using namespace sf;

int main(){
	RenderWindow app(VideoMode(400, 400), "Chess");


	Knight* k = new Knight(1, 1);
	Tile* tile = new Tile(1, k);
	// std::cout << k << std::endl;
	// k->calculateLegalMoves(NULL);
	std::cout << tile->toString() << std::endl;

	Event e;
	while(app.isOpen()){
		while(app.pollEvent(e)){
			switch(e.type){
				case Event::Closed: app.close(); break;
			}
		}

		app.clear();
		app.display();
	}

	return 0;
}