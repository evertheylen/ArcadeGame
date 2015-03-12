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

	Game(TiXmlDocument& board_doc, TiXmlDocument& moves_doc);
	// ENSURE(properlyInitialized(), "constructor must end ...");

	void writeBoard(std::ostream& stream);
	// REQUIRE(properlyInitialized(), "Game wasn't initialized when calling writeBoard");// REQUIRE(properlyInitialized(), "Game wasn't initialized when calling writeBoard");

	void writeMovements(std::ostream& stream);
	// REQUIRE(properlyInitialized(), "Game wasn't initialized when calling writeMovements");



	void doMove(Movement& movement, std::ostream& out);
	// REQUIRE(properlyInitialized(), "Game wasn't initialized when calling doMove");
	// REQUIRE(!_movements.empty(), "Movements was empty, can't be done");
	// ENSURE(x_original != x || y_original != y, "Movement not completed, location stayed the same");

	void doAllMoves(std::ostream& out);
	// REQUIRE(properlyInitialized(), "Game wasn't initialized when calling doAllMoves");
	// ENSURE(_movements.empty(), "Not all movements are executed");

	bool properlyInitialized() const;

private:
	Board _board;
	std::list<Movement> _movements;		// TODO Misschien zit de fout met de properlyInit van movements hier? En moet dit Movement& worden?
	Playermap _players;
	Game* _initCheck;

	std::string readElement(TiXmlElement* elem, const char* tag);

	std::string readElement(TiXmlElement* elem);

	std::string readAttribute(TiXmlElement* elem, const char* tag);

	void parsePlayer(TiXmlElement* elem);
	// REQUIRE(reqElement(elem, "NAAM",, "Player must have a name specified.");

	void parseObstacle(TiXmlElement* elem);
	// REQUIRE(reqElement(elem, "TYPE"), "Obstacle must have a type specified.");

	void forceLowerCase(TiXmlElement* elem);

	bool reqElement(TiXmlElement* elem, const char* tag);


};

#endif // _Game
