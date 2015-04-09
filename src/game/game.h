#include "../../lib/tinyxml/tinyxml.h"
#include "action/action.h"
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

	Game(Board* board, std::list<Action>& actions, Playermap& players);
	/**< ENSURE(properlyInitialized(), "constructor must end ...");*/

	void writeBoard(std::ostream& stream);
	/**< REQUIRE(properlyInitialized(), "Game wasn't initialized when calling writeBoard");*/

	void writeActions(std::ostream& stream);
	/**< REQUIRE(properlyInitialized(), "Game wasn't initialized when calling writeActions");*/

	std::list<Action>& get_actions();
	/**< REQUIRE(properlyInitialized(), "Game wasn't initialized when calling get_actions");*/

	void popAction(std::ostream& out);
	/**< REQUIRE(properlyInitialized(), "Game wasn't initialized when calling doAction");
	 	REQUIRE(!get_actions().empty(), "Actions was empty, can't be done");
		ENSURE(_actions.size() == original_size - 1, "Action was not popped");*/
	
	void doAction(Action& action, std::ostream& out);
	/**< REQUIRE(properlyInitialized(), "Game wasn't initialized when calling doAction"); */

	void doAllActions(std::ostream& out);
	/**< REQUIRE(properlyInitialized(), "Game wasn't initialized when calling doAllActions");
		ENSURE(get_actions().empty(), "Not all actions are executed");*/

	bool properlyInitialized() const;

private:
	Board* _board;
	std::list<Action> _actions;
	Playermap _players;
	Game* _initCheck;

	//void parsePlayer(TiXmlElement* elem, std::ostream& out);

	//void parseObstacle(TiXmlElement* elem, std::ostream& out);

};

#endif // _Game
