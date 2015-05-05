
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
	 * REQUIRE(board != nullptr, "Board wasn't specified")
	 */
	Player* get_player(std::string& name);

	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling get_monster")
	 * REQUIRE(board != nullptr, "Board wasn't specified")
	 */
	Monster* get_monster(std::string& name);

	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling get_actor")
	 * REQUIRE(board != nullptr, "Board wasn't specified")
	 */
	Actor* get_actor(std::string& name);
	// Players have priority if a player and monster have the same name
	
	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling get_gate")
	 * REQUIRE(board != nullptr, "Board wasn't specified")
	 */
	Gate* get_gate(std::string& name);
	
	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling add_player")
	 * REQUIRE(board != nullptr, "Board wasn't specified")
	 */
	void add_player(Player* p);

	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling add_monster")
	 * REQUIRE(board != nullptr, "Board wasn't specified")
	 */
	void add_monster(Monster* m);

	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling add_gate")
	 * REQUIRE(board != nullptr, "Board wasn't specified")
	 */
	void add_gate(Gate* g);
	
	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling write_actions")
	 * REQUIRE(board != nullptr, "Board wasn't specified")
	 */
	void write_actions(std::ostream& out);

	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling players_alive")
	 * REQUIRE(board != nullptr, "Board wasn't specified")
	 */
	int players_alive();
	
	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling bury")
	 * REQUIRE(board != nullptr, "Board wasn't specified")
	 */
	void bury(Entity* e);
	
// 	//void event_log(std::string s);

	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling do_all_actions")
	 * REQUIRE(board != nullptr, "Board wasn't specified")
	 */
	void do_all_actions(std::ostream& out);
	
	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling do_action")
	 * REQUIRE(board != nullptr, "Board wasn't specified")
	 */
	void do_action(std::ostream& out);
	
	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling get_num_actions")
	 * REQUIRE(board != nullptr, "Board wasn't specified")
	 */
	int get_num_actions();
	
	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling is_ended")
	 * REQUIRE(board != nullptr, "Board wasn't specified")
	 */
	bool is_ended();
	
	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling clear_actions")
	 * REQUIRE(board != nullptr, "Board wasn't specified")
	 */
	void clear_actions();
	
	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling get_board")
	 * REQUIRE(board != nullptr, "Board wasn't specified")
	 */
	Board* get_board();

	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling set_board")
	 * REQUIRE(board != nullptr, "Board wasn't specified")
	 */
	void set_board(Board* b);
	
	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling kill")
	 * REQUIRE(board != nullptr, "Board wasn't specified")
	 */
	void kill(Entity* a);

	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling collide")
	 * REQUIRE(board != nullptr, "Board wasn't specified")
	 */
	void collide(Entity* a, Entity* b);

	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling enter")
	 * REQUIRE(board != nullptr, "Board wasn't specified")
	 */
	void enter(Entity* top, Entity* bottom);

	/**
	 * REQUIRE(properlyInitialized(), "Game wasn't initialized when calling leave")
	 * REQUIRE(board != nullptr, "Board wasn't specified")
	 */
	void leave(Entity* top, Entity* bottom);
	
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
