#include <string>
#include "../board/player.h"

#ifndef _Movement
#define _Movement

enum Direction {up, left, down, right, no_dir};

Direction toDirection(std::string dir_s);

void doDirection(Direction dir, unsigned int& x, unsigned int& y);
void doReverseDirection(Direction dir, unsigned int& x, unsigned int& y);

class Movement {
public:
	
	// copy constructor
	Movement(const Movement& that);

	// copy assignment
	Movement& operator=(const Movement& that);
	
	Movement(Direction dir, Player* player);
	// ENSURE(properlyInitialized(), "constructor must end ...");
	
	Movement(std::string dir_s, Player* player);
	// ENSURE(properlyInitialized(), "constructor must end ...");

	Direction get_dir() const;
	// REQUIRE(properlyInitialized(), "Movement wasn't initialized when calling get_dir");

	std::string get_dir_name() const;
	// REQUIRE(properlyInitialized(), "Movement wasn't initialized when calling get_dir_name");

	void set_dir(Direction dir);
	// REQUIRE(properlyInitialized(), "Movement wasn't initialized when calling set_dir");
	// ENSURE(get_dir() == dir, "Direction not set correctly");

	Player* get_player() const;
	// REQUIRE(properlyInitialized(), "Movement wasn't initialized when calling get_player");

	// When setting to other player, take care of memory leaks.
	void set_player(Player* player);
	// REQUIRE(properlyInitialized(), "Movement wasn't initialized when calling set_player");
	// ENSURE(get_player() == player && player->properlyInitialized(), "Player not set correctly");

	friend std::ostream& operator<< (std::ostream &out, Movement& move);
	// REQUIRE(move.properlyInitialized(), "Movement wasn't initialized when calling operator <<");

	bool properlyInitialized() const;

private:
	Direction _dir;
	Player* _player;
	Movement* _initCheck;
};


#endif // _Movement
