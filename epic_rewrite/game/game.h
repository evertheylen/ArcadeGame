
#ifndef _H_Game
#define _H_Game

#include <iostream>
#include <string>
#include <map>

#include <list>

#include "entities/entity.h"
#include "entities/gate.h"
#include "events/managers.h"


class Game {
private:
	CollisionManager collide;
	IA_EnterManager enter;
	IA_LeaveManager leave;

public:

 	Game();
	
// 	//void event_log(std::string s);
// 	typedef std::map<std::string, Entity*> Playermap;
// 	typedef std::pair<std::string, Entity*> Playerpair;
// 	typedef std::map<std::string, Gate*> Gatemap;
// 
// 	//! copy constructor
// 	Game(const Game& that);
// 	/**< ENSURE(properlyInitialized(), "Copy constructor must end...");*/
// 
// 	//! copy assignment
// 	Game& operator=(const Game& that);
// 	/**< ENSURE(properlyInitialized(), "Copy by assignment must end...");*/
// 
// 	Game(Board* board, std::list<Action>& actions, Playermap& players);
// 	/**< ENSURE(properlyInitialized(), "constructor must end ...");*/

	void main_loop();
};

#endif
