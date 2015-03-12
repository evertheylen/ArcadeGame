#include <string>
#include <iostream>
#include <sstream>
#include "movement.h"
#include "../board/player.h"
#include "../../DesignByContract.h"

Direction toDirection(std::string dir_s) {
	if (dir_s == "OMHOOG") {
		return Direction::up;
	} else if (dir_s == "OMLAAG") {
		return Direction::down;
	} else if (dir_s == "LINKS") {
		return  Direction::left;
	} else if (dir_s == "RECHTS") {
		return Direction::right;
	} else {
		//std::cerr << "Did not recognize type " << dir_s << " as a direction.";
		return Direction::no_dir;
	}
}

// copy constructor
Movement::Movement(const Movement& that):
	_dir(that._dir),
	_player(that._player) {
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy constructor must end...");
}

// copy assignment
Movement& Movement::operator=(const Movement& that) {
	_dir = that._dir;
	_player = that._player;
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy by assignment must end...");
	return *this;
}

Movement::Movement(Direction dir, Player* player):
	_dir(dir), _player(player) {
	_initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end ...");
}


Movement::Movement(std::string dir_s, Player* player):
	_player(player) {
	_dir = toDirection(dir_s);
	_initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end ...");
}

bool Movement::properlyInitialized() const {
	return _initCheck == this;
}

void doDirection(Direction dir, unsigned int& x, unsigned int& y) {
	switch (dir) {
		case up:
			y++;
			return;
		case left:
			x--;
			return;
		case down:
			y--;
			return;
		case right:
			x++;
			return;
	}
}

void doReverseDirection(Direction dir, unsigned int& x, unsigned int& y) {
	switch (dir) {
		case up:
			y--;
			return;
		case left:
			x++;
			return;
		case down:
			y++;
			return;
		case right:
			x--;
			return;
	}
}

Direction Movement::get_dir() const {
	REQUIRE(properlyInitialized(), "Movement wasn't initialized when calling get_dir");
	Direction result = _dir;
	return result;
}

std::string Movement::get_dir_name() const {
	REQUIRE(properlyInitialized(), "Movement wasn't initialized when calling get_dir_name");
	switch (_dir) {
		case up:
			return "OMHOOG";
		case left:
			return "LINKS";
		case down:
			return "OMLAAG";
		case right:
			return "RECHTS";
	}
}

void Movement::set_dir(Direction dir) {
	REQUIRE(properlyInitialized(), "Movement wasn't initialized when calling set_dir");
	_dir = dir;
	ENSURE(get_dir() == dir, "Direction not set correctly");
}

Player* Movement::get_player() const {
	REQUIRE(properlyInitialized(), "Movement wasn't initialized when calling get_player");
	Player* result = _player;
	return result;
}

void Movement::set_player(Player* player) {
	REQUIRE(properlyInitialized(), "Movement wasn't initialized when calling set_player");
	_player = player;
	ENSURE(get_player() == player && player->properlyInitialized(), "Player not set correctly");
}

std::ostream& operator<< (std::ostream &out, Movement& move){
	REQUIRE(move.properlyInitialized(), "Movement wasn't initialized when calling operator <<");
	out << "Speler " << move.get_player()->get_name() << " zal volgende beweging nog uitvoeren:\n"
		<< move.get_dir_name() << std::endl;
	return out;
}
