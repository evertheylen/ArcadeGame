#include "../lib/tinyxml.h"
#include "movement/movement.h"
#include "board/board.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>

#ifndef _Game
#define _Game

class Game {
public:
	typedef std::map<std::string, Player> Playermap;
	typedef std::pair<std::string, Player> Playerpair;

	Game(TiXmlDocument& board_doc, TiXmlDocument& moves_doc); // TODO 2 xml docs?

	std::string readElement(TiXmlElement* elem, const char* tag);
	std::string readAttribute(TiXmlElement* elem, const char* tag);

	void forceLowerCase(TiXmlElement* elem);

	void writeBoard(std::ostream& stream);

	void writeMovements(std::ostream& stream);

	void popMove();

	void doMove(Movement& movement);

private:
	Board _board;
	std::vector<Movement> _movements;
	Playermap _players;


};

#endif // _Game
