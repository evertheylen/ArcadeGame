#include <string>
#include "../board/living_thing.h"
#include "../board/board.h"
#include "../board/player.h"

#ifndef _Action
#define _Action

enum Direction {up, left, down, right, no_dir};

Direction toDirection(std::string dir_s);

void doDirection(Direction dir, unsigned int& x, unsigned int& y);
void doReverseDirection(Direction dir, unsigned int& x, unsigned int& y);

class Action {
public:
	Action(Direction dir);

	virtual bool doAction(Board* b); //= 0;
	
	friend std::ostream& operator<<(std::ostream& out, Action& a);
	
	virtual void print(std::ostream& out); // = 0;
	
	Direction get_dir() const;
	/**< REQUIRE(properlyInitialized(), "Movement wasn't initialized when calling get_dir");*/

	std::string get_dir_name() const;
	/**< REQUIRE(properlyInitialized(), "Movement wasn't initialized when calling get_dir_name");*/

	void set_dir(Direction dir);
	/**< REQUIRE(properlyInitialized(), "Movement wasn't initialized when calling set_dir");
		ENSURE(get_dir() == dir, "Direction not set correctly");*/

private:
	Direction _dir;
};

class Movement: public Action {
public:
	
	//! copy constructor
	Movement(const Movement& that);
	/**< ENSURE(properlyInitialized(), "Copy constructor must end...");*/

	//! copy assignment
	Movement& operator=(const Movement& that);
	/**< ENSURE(properlyInitialized(), "Copy by assignment must end...");*/
	
	Movement(Direction dir, LivingThing* mover);
	/**< ENSURE(properlyInitialized(), "constructor must end ...");*/
	
	Movement(std::string dir_s, LivingThing* mover);
	/**< ENSURE(properlyInitialized(), "constructor must end ...");*/

	LivingThing* get_mover() const;
	/**< REQUIRE(properlyInitialized(), "Movement wasn't initialized when calling get_player");*/
	
/*
	//! When setting to other player, take care of memory leaks.
	void set_player(LivingThing* player);
	/**< REQUIRE(properlyInitialized(), "Movement wasn't initialized when calling set_player");
		ENSURE(get_player() == player && player->properlyInitialized(), "Player not set correctly");*/
//*/

	bool doAction(Board* board);

	void print(std::ostream &out);
	/**< REQUIRE(move.properlyInitialized(), "Movement wasn't initialized when calling operator <<");*/

	bool properlyInitialized() const;

private:
	Direction _dir;
	LivingThing* _mover;
	Movement* _initCheck;
};


class Attack: public Action {
public:
	
	Attack(Direction dir, LivingThing* player);
	
	Attack(std::string dir_s, LivingThing* player);
	
	LivingThing* get_player();
	
	void print(std::ostream& out);
	
	bool doAction(Board* board);

	//TODO properlyInitialized vinden we leuk!

private:
	LivingThing* _player;
};

#endif // _Actions
