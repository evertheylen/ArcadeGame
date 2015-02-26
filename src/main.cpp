#include "lib/tinyxml.h"
#include "game/game.h"
#include <iostream>

int main() {
	TiXmlDocument doc;

	Game g = Game(doc);
	g.popMove();
	g.writeBoard(std::cout);
	g.writeMovements(std::cout);
}
