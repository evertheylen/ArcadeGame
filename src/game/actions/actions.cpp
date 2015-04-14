#include <string>
#include <iostream>
#include <sstream>
#include "actions.h"
#include "../board/living_thing.h"
#include "../board/player.h"
#include "../../DesignByContract.h"

// Direction stuff
////////////////////////////////

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

// Action stuff
/////////////////////////////////////

Action::Action(Direction dir):
	_dir(dir) {}

std::ostream& operator<<(std::ostream& out, Action& a) {
	a.print(out);
	return out;
}

Direction Action::get_dir() const {
	return _dir;
}

std::string Action::get_dir_name() const {
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
	return "error";
}

void Action::set_dir(Direction dir) {
	_dir = dir;
}


// Movement stuff
///////////////////////////////////////


// copy constructor
Movement::Movement(const Movement& that):
	Action(that),
	_mover(that._mover) {
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy constructor must end...");
}

// copy assignment
Movement& Movement::operator=(const Movement& that) {
	Action::operator=(that);
	_mover = that._mover;
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy by assignment must end...");
	return *this;
}

Movement::Movement(Direction dir, LivingThing* mover):
	Action(dir), _mover(mover) {
	_initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end ...");
}


Movement::Movement(std::string dir_s, LivingThing* mover):
	Action(toDirection(dir_s)), _mover(mover) {
	_initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end ...");
}

bool Movement::properlyInitialized() const {
	return _initCheck == this;
}


LivingThing* Movement::get_mover() const {
	REQUIRE(properlyInitialized(), "Movement wasn't initialized when calling get_player");
	LivingThing* result = _mover;
	return result;
}

/*
void Movement::set_player(LivingThing* mover) {
	REQUIRE(properlyInitialized(), "Movement wasn't initialized when calling set_player");
	_mover = mover;
	ENSURE(get_player() == player && player->properlyInitialized(), "Player not set correctly");
}
*/


void Movement::print(std::ostream &out) {
	REQUIRE(this->properlyInitialized(), "Movement wasn't initialized when calling operator <<");
	// Speler spelernaam zal volgende beweging nog uitvoeren
	// Monster monsternaam zal volgende beweging nog uitvoeren
	out << get_mover()->get_typename() << " " << get_mover()->get_name() << " zal volgende beweging nog uitvoeren:\n"
		<< get_dir_name() << std::endl;
}


// Attack stuff
///////////////////////////////////

Attack::Attack(Direction dir, LivingThing* player):
		Action(dir), _player(player) {}


Attack::Attack(std::string dir_s, LivingThing* player):
		Action(toDirection(dir_s)), _player(player) {}

