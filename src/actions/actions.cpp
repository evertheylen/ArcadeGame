
#include "actions.h"
#include "game.h"

// Direction

Direction::Direction(Direction::Dirk d):
		dir(d) {}

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
}


void Direction::move_to(unsigned int& x, unsigned int& y) {
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
	return dir;
}

// Action

Action::Action(Actor* _actor, std::string& dirname):
		actor(_actor), dir(dirname) {}



