
#ifndef _H_Game
#define _H_Game

#include <iostream>
#include <string>
#include <map>

#include <list>

#include "entities/entity.h"
#include "entities/gate.h"
#include "entities/actor.h"
#include "entities/player.h"
#include "entities/monster.h"

#include "events/managers.h"
#include "events/collisionhandler.h"
#include "events/ia_enterhandler.h"
#include "events/ia_leavehandler.h"
#include "events/killhandler.h"

#include "board.h"
#include "actions.h"

class Game {
public:
	typedef std::map<std::string, Player*> Playermap;
	typedef std::map<std::string, Monster*> Monstermap;

	typedef std::map<std::string, Gate*> Gatemap;

	std::list<Action*> actions;

	Playermap playermap;
	Monstermap monstermap;
	Gatemap gatemap;

	Game();
	
	//Game (Board* board, std::list<Action*>* actions, Playermap players, Monstermap monsters, Gatemap gates);

	KillManager kill;         // kill(a)
	CollisionManager collide; // collide(a, b) == collide(b, a)
	IA_EnterManager enter;    // enter(top, bottom)
	IA_LeaveManager leave;    // leave(top, bottom)
	
	Player* get_player(std::string name);
	Monster* get_monster(std::string name);
	Actor* get_actor(std::string name);
	// Players have priority if a player and monster have the same name
	
	void add_player(Player* p);
	void add_monster(Monster* m);
	
	void write_actions(std::ostream& out);

	int players_alive();
	
	void bury(Entity* e);
	
// 	//void event_log(std::string s);
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

	void do_all_actions(std::ostream& out);
	
	void do_action(std::ostream& out);
	
	int get_num_actions();
	
	bool is_ended();
	
	void clear_actions();
	
	Board* get_board();
	void set_board(Board* b);
	
	~Game();
	
private:

	Board* board;
	
	std::vector<Entity*> graveyard;

	bool ended;
	
	friend class CollisionHandler;
	friend class IA_EnterHandler;
	friend class IA_LeaveHandler;
	friend class KillHandler;
	friend class Board;
};

#endif
