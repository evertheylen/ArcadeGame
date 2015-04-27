
#ifndef _H_Action
#define _H_Action

#include <iostream>

#include "../entities/actor.h"
#include "../entities/player.h"
#include <../entities/monster.h>

#include "string"

class Game;

class Direction {
public:
	enum class Dirk {up, left, down, right, no_dir};
	
	Direction(std::string& s);
	Direction(Dirk d);
	
	friend std::ostream& operator<<(std::ostream& out, Direction& d);
	
	Direction::Dirk get_dir();

	void move_to(unsigned int& x, unsigned int& y);
	void move_from(unsigned int& x, unsigned int& y);
	
private:
	Dirk dir;
};


class Action {
protected:
	Actor* actor;
	Direction dir;
	
public:
	Action(Actor* _actor, std::string& dirname);
	
	virtual void execute(Game* g) = 0;
};



#endif
