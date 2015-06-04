#include "actions.h"
#include "game.h"

// Direction

bool Direction::properlyInitialized() {
	return (initCheck == this);
}


Direction::Direction(Direction::Dirk d):
		dir(d) {
	initCheck = this;
	ENSURE(properlyInitialized(), "Copy constructor must end...");
}

Direction::Direction(std::string& s) {
	if (s == "OMHOOG") {
		dir = Dirk::up;
	} else if (s == "OMLAAG") {
		dir = Dirk::down;
	} else if (s == "LINKS") {
		dir = Dirk::left;
	} else if (s == "RECHTS") {
		dir = Dirk::right;
	} else {
		//std::cerr << "Did not recognize type " << dir_s << " as a direction.";
		dir = Dirk::no_dir;
	}
	initCheck = this;
	ENSURE(properlyInitialized(), "Constructor must end...");
}

Direction::Direction(const Direction& that):
		dir(that.dir) {
	initCheck = this;
	ENSURE(properlyInitialized(), "Copy constructor must end...");
}

Direction& Direction::operator=(const Direction& that) {
	dir = that.dir;
	initCheck = this;
	ENSURE(properlyInitialized(), "Copy by assingment must end...");
	return *this;
}

void Direction::move_to(unsigned int& x, unsigned int& y) {
	REQUIRE(properlyInitialized(), "Direction wasn't initialized when calling move_to.");
	switch (dir) {
		case Dirk::up:
			y++;
			return;
		case Dirk::left:
			x--;
			return;
		case Dirk::down:
			y--;
			return;
		case Dirk::right:
			x++;
			return;
	}
}


void Direction::move_from(unsigned int& x, unsigned int& y) {
	REQUIRE(properlyInitialized(), "Direction wasn't initialized when calling move_from.");
	switch (dir) {
		case Dirk::up:
			y--;
			return;
		case Dirk::left:
			x++;
			return;
		case Dirk::down:
			y++;
			return;
		case Dirk::right:
			x--;
			return;
	}
}


std::ostream& operator<<(std::ostream& out, Direction& d) {
	REQUIRE(d.properlyInitialized(), "Direction wasn't initialized when calling operator <<.");
	switch (d.dir) {
		case Direction::Dirk::up:
			out << "OMHOOG";
			return out;
		case Direction::Dirk::left:
			out << "LINKS";
			return out;
		case Direction::Dirk::down:
			out << "OMLAAG";
			return out;
		case Direction::Dirk::right:
			out << "RECHTS";
			return out;
	}
	out << "error";
	return out;
}

Direction::Dirk Direction::get_dir() {
	REQUIRE(properlyInitialized(), "Direction wasn't initialized when calling get_dir.");
	return dir;
}

// Action

Action::Action(Actor* _actor, std::string& dirname):
		actor(_actor), dir(dirname) {
	initCheck = this;
}

bool Action::properlyInitialized() {
	return (initCheck == this);
}

Action::Action(const Action& that):
		dir(that.dir) {
	actor = that.actor;
	initCheck = this;
	ENSURE(properlyInitialized(), "Copy constructor must end...");
}

Action& Action::operator=(const Action& that) {
	//dir();
	actor = that.actor;
	initCheck = this;
	ENSURE(properlyInitialized(), "Copy by assingment must end...");
	return *this;
}

Actor* Action::get_actor() {
	REQUIRE(properlyInitialized(), "Action wasn't initialized when calling get_actor.");
	return actor;
}

Direction Action::get_dir() {
	REQUIRE(properlyInitialized(), "Action wasn't initialized when calling get_dir.");
	return dir;
}


