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

void doDirection(Direction dir, unsigned int& x, unsigned int& y) {
	switch (dir) {
		case up:
			y++;
			break;
		case left:
			x--;
			break;
		case down:
			y--;
			break;
		case right:
			x++;
			break;
	}
	
	return;
}

Direction Movement::get_dir() const {
	return _dir;
}

std::string Movement::get_dir_name() const {
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
	_dir = dir;
}

Player* Movement::get_player() const {
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
