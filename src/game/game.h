#include "../../lib/tinyxml/tinyxml.h"
#include "movement/movement.h"
#include "board/board.h"
#include "board/living_thing.h"
#include "board/gate.h"

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>

#ifndef _Game
#define _Game

class Game {
public:
	typedef std::map<std::string, LivingThing*> Playermap;
	typedef std::pair<std::string, LivingThing*> Playerpair;
	typedef std::map<std::string, Gate*> Gatemap;

	//! copy constructor
	Game(const Game& that);
	/**< ENSURE(properlyInitialized(), "Copy constructor must end...");*/

	//! copy assignment
	Game& operator=(const Game& that);
	/**< ENSURE(properlyInitialized(), "Copy by assignment must end...");*/

	Game(Board& board, std::list<Movement>& movements, Playermap& players, std::ostream& out);
	/**< ENSURE(properlyInitialized(), "constructor must end ...");*/

	void writeBoard(std::ostream& stream);
	/**< REQUIRE(properlyInitialized(), "Game wasn't initialized when calling writeBoard");*/

	void writeMovements(std::ostream& stream);
	/**< REQUIRE(properlyInitialized(), "Game wasn't initialized when calling writeMovements");*/

	std::list<Movement>& get_movements();
	/**< REQUIRE(properlyInitialized(), "Game wasn't initialized when calling get_movements");*/

	void popMove(std::ostream& out);
	/**< REQUIRE(properlyInitialized(), "Game wasn't initialized when calling doMove");
	 	REQUIRE(!get_movements().empty(), "Movements was empty, can't be done");
		ENSURE(_movements.size() == original_size - 1, "Movement was not popped");*/
	
	void doMove(Movement& movement, std::ostream& out);
	/**< REQUIRE(properlyInitialized(), "Game wasn't initialized when calling doMove");
		ENSURE(x_original != x || y_original != y, "Movement not completed, location stayed the same");*/

	void doAllMoves(std::ostream& out);
	/**< REQUIRE(properlyInitialized(), "Game wasn't initialized when calling doAllMoves");
		ENSURE(get_movements().empty(), "Not all movements are executed");*/

	bool properlyInitialized() const;

private:
	Board _board;
	std::list<Movement> _movements;
	Playermap _players;
	Game* _initCheck;

	//void parsePlayer(TiXmlElement* elem, std::ostream& out);

	//void parseObstacle(TiXmlElement* elem, std::ostream& out);

};

#endif // _Game
