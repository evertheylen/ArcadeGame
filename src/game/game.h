
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
#include "DesignByContract.h"

class Game {
public:
	typedef std::map<std::string, Player*> Playermap;
	typedef std::map<std::string, Monster*> Monstermap;

	typedef std::map<std::string, Gate*> Gatemap;

	std::list<Action*> actions;

	/**
	 * ENSURE(properlyInitialized(), "Constructor must end...")
	 */
	Game();
	
	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling get_player")
	 */
	Player* get_player(std::string& name);

	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling get_monster")
	 */
	Monster* get_monster(std::string& name);

	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling get_actor")
	 */
	Actor* get_actor(std::string& name);
	// Players have priority if a player and monster have the same name
	
	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling get_gate")
	 */
	Gate* get_gate(std::string& name);
	
	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling add_player")
	 */
	void add_player(Player* p);

	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling add_monster")
	 */
	void add_monster(Monster* m);

	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling add_gate")
	 */
	void add_gate(Gate* g);
	
	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling write_actions")
	 */
	void write_actions(std::ostream& out);

	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling players_alive")
	 */
	int players_alive();
	
	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling bury")
	 */
	void bury(Entity* e);
	
// 	//void event_log(std::string s);

	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling do_all_actions")
	 */
	void do_all_actions(std::ostream& out);
	
	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling do_action")
	 */
	void do_action(std::ostream& out);
	
	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling get_num_actions")
	 */
	int get_num_actions();
	
	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling is_ended")
	 */
	bool is_ended();
	
	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling clear_actions")
	 */
	void clear_actions();
	
	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling get_board")
	 * REQUIRE(board != nullptr, "Board wasn't specified")
	 */
	Board* get_board();

	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling set_board")
	 */
	void set_board(Board* b);
	
	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling kill")
	 */
	void kill(Entity* a);

	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling collide")
	 */
	void collide(Entity* a, Entity* b);

	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling enter")
	 */
	void enter(Entity* top, Entity* bottom);

	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling leave")
	 */
	void leave(Entity* top, Entity* bottom);
	
	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling save")
	 */
	void save(std::ostream& out);

	~Game();
	
	bool properlyInitialized();

private:
	Playermap playermap;
	Monstermap monstermap;
	Gatemap gatemap;

	Board* board;
	
	std::vector<Entity*> graveyard;

	bool ended;
	
	Game* initCheck;

	KillManager _kill;         // kill(a)
	CollisionManager _collide; // collide(a, b) == collide(b, a)
	IA_EnterManager _enter;    // enter(top, bottom)
	IA_LeaveManager _leave;    // leave(top, bottom)
	
	friend class CollisionHandler;
	friend class IA_EnterHandler;
	friend class IA_LeaveHandler;
	friend class KillHandler;
	friend class Board;
};

#endif
