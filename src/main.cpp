#include "lib/tinyxml.h"
#include "game/game.h"
#include <iostream>

int main(int argc, char const* argv[]) {
	TiXmlDocument doc;

	if(argc <= 1 || !doc.LoadFile(argv[1])) {
		std::cerr << doc.ErrorDesc() << std::endl;
		return 1;
	}

	Game g = Game(doc);
	g.popMove();
	g.writeBoard(std::cout);
	g.writeMovements(std::cout);
}
