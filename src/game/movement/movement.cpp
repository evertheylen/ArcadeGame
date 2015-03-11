#include <string>
#include <iostream>
#include <sstream>
#include "movement.h"
#include "../board/player.h"
#include "../../DesignByContract.h"

Movement::Movement(Direction dir, Player* player):
	_dir(dir), _player(player) {
	_initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end ...");

	// TODO Something is going wrong during initialization, cuz everything crashes.
}

Movement::Movement(std::string dir_s, Player* player):
	_player(player) {
	if (dir_s == "OMHOOG") {
		_dir = Direction::up;
	} else if (dir_s == "OMLAAG") {
		_dir = Direction::down;
	} else if (dir_s == "LINKS") {
		_dir = Direction::left;
	} else if (dir_s == "RECHTS") {
		_dir = Direction::right;
	} else {
		std::cerr << "Did not recognize type " << dir_s << " as a direction.";	// TODO We should fix this so that the incorrect movement does NOT get pushed on the movements vector!
	}
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
	//REQUIRE(properlyInitialized(), "Movement wasn't initialized when calling get_dir");
	Direction result = _dir;
	ENSURE(result == _dir, "Wrong result when executing get_dir");
	return result;
}

std::string Movement::get_dir_name() const {
	//REQUIRE(properlyInitialized(), "Movement wasn't initialized when calling get_dir_name");
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
	//REQUIRE(properlyInitialized(), "Movement wasn't initialized when calling set_dir");
	_dir = dir;
	ENSURE(_dir == dir, "Direction not set correctly");
}

Player* Movement::get_player() const {

	//TODO Fix this? When we require this, we get an error that movement wasnt initialized when we do a move in doMove.
	//REQUIRE(properlyInitialized(), "Movement wasn't initialized when calling get_player");
	Player* result = _player;
	ENSURE(result == _player, "Wrong result when executing get_player");
	return result;
}

void Movement::set_player(Player* player) {
	//REQUIRE(properlyInitialized(), "Movement wasn't initialized when calling set_player");
	_player = player;
	ENSURE(_player == player && player->properlyInitialized(), "Player not set correctly");
}

std::ostream& operator<< (std::ostream &out, Movement& move){
	//REQUIRE(move.properlyInitialized(), "Movement wasn't initialized when calling operator <<");
	out << "Speler " << move.get_player()->get_name() << " zal volgende beweging nog uitvoeren:\n"
		<< move.get_dir_name() << std::endl;
	return out;
}
