#include "../../lib/tinyxml/tinyxml.h"
#include "movement/movement.h"
#include "board/board.h"

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>

#ifndef _Game
#define _Game

class Game {
public:
	typedef std::map<std::string, Player*> Playermap;
	typedef std::pair<std::string, Player*> Playerpair;

	Game(TiXmlDocument& board_doc, TiXmlDocument& moves_doc); // TODO 2 xml docs?

	std::string readElement(TiXmlElement* elem, const char* tag);
	std::string readElement(TiXmlElement* elem);
	std::string readAttribute(TiXmlElement* elem, const char* tag);

	void parsePlayer(TiXmlElement* elem);

	void parseObstacle(TiXmlElement* elem);

	void forceLowerCase(TiXmlElement* elem);

	void writeBoard(std::ostream& stream);

	void writeMovements(std::ostream& stream);

	void popMove();

	void doMove(Movement& movement);

	void doAllMoves();

private:
	Board _board;
	std::list<Movement> _movements;
	Playermap _players;


};

#endif // _Game
