#include <string>
#include <iostream>
#include "movement.h"
#include "../board/player.h"

Movement::Movement(Direction dir, Player* player):
	_dir(dir), _player(player) {}

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
		std::cerr << "Did not recognize type '" << dir_s << "' as a direction.\n";
		// TODO proper error handling
	}
}

Direction Movement::get_dir() const {
	return _dir;
}

std::string Movement::get_dir_name() const {
	std::string result;
	if (_dir == 0) {
		result = "OMHOOG";
	}
	if (_dir == 1) {
		result = "LINKS";
	}
	if (_dir == 2) {
		result = "OMLAAG";
	}
	if (_dir == 3) {
		result = "RECHTS";
	}
	return result;
}

void Movement::set_dir(Direction dir) {
	_dir = dir;
}

const Player* Movement::get_player() const {
	return _player;
}

void Movement::set_player(Player* player) {
	_player = player;
}

std::ostream& operator<< (std::ostream &out, Movement& move){
	out << "Speler " << move.get_player()->get_name() << " zal volgende beweging nog uitvoeren:\n"
		<< move.get_dir_name() << std::endl;
	return out;
}
