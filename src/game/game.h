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

class ParseError: std::exception {
	const char* what()throw() {
		return "Error while parsing the xml file.";
	}
};

class Game {
public:
	typedef std::map<std::string, Player*> Playermap;
	typedef std::pair<std::string, Player*> Playerpair;

	// copy constructor
	Game(const Game& that);
	//ENSURE(properlyInitialized(), "Copy constructor must end...");

	// copy assignment
	Game& operator=(const Game& that);
	//ENSURE(properlyInitialized(), "Copy by assignment must end...");

	Game(TiXmlDocument& board_doc, TiXmlDocument& moves_doc);
	// ENSURE(properlyInitialized(), "constructor must end ...");

	void writeBoard(std::ostream& stream);
	// REQUIRE(properlyInitialized(), "Game wasn't initialized when calling writeBoard");// REQUIRE(properlyInitialized(), "Game wasn't initialized when calling writeBoard");

	void writeMovements(std::ostream& stream);
	// REQUIRE(properlyInitialized(), "Game wasn't initialized when calling writeMovements");

	std::list<Movement>& get_movements();
	// REQUIRE(properlyInitialized(), "Game wasn't initialized when calling get_movements");

	void popMove(std::ostream& out);
	// REQUIRE(properlyInitialized(), "Game wasn't initialized when calling doMove");
	// REQUIRE(!get_movements().empty(), "Movements was empty, can't be done");
	// ENSURE(_movements.size() == original_size - 1, "Movement was not popped");
	
	void doMove(Movement& movement, std::ostream& out);
	// REQUIRE(properlyInitialized(), "Game wasn't initialized when calling doMove");
	// ENSURE(x_original != x || y_original != y, "Movement not completed, location stayed the same");

	void doAllMoves(std::ostream& out);
	// REQUIRE(properlyInitialized(), "Game wasn't initialized when calling doAllMoves");
	// ENSURE(get_movements().empty(), "Not all movements are executed");

	bool properlyInitialized() const;

private:
	Board _board;
	std::list<Movement> _movements;
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
