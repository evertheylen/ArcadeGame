#include "../lib/tinyxml.h"
#include "movement/movement.h"
#include "board/board.h"

#include <iostream>
#include <vector>

#ifndef _Game
#define _Game

class Game {
public:
	Game(TiXmlDocument& doc);

	std::string readElement(TiXmlElement* elem, const char* tag);

	void writeBoard(std::ostream& stream);

	void writeMovements(std::ostream& stream);

	void popMove();

	void doMove(Movement& movement);

private:
	Board _board;
	std::vector<Movement> _movements;
	std::vector<Player> _players;
};

#endif // _Game
