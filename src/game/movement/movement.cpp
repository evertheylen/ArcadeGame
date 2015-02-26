#include "movement.h"
#include "../board/player.h"

Movement::Movement(Direction dir, Player* player):
	_dir(dir), _player(player) {}

Direction Movement::get_dir() const {
	return _dir;
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
