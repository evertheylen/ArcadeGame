/*
 * spot.cpp
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn & evert
 */

#include "spot.h"
#include "../../DesignByContract.h"

Spot::Spot(unsigned int x, unsigned int y): _x(x), _y(y) {
	_initCheck = this;
	ENSURE(properlyInitialized(), "Constructor must end...");
}

// copy constructor
Spot::Spot(const Spot& that):
	_x(that._x),
	_y(that._y) {
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy constructor must end...");
}

// copy assignment
Spot& Spot::operator=(const Spot& that) {
	_x = that._x;
	_y = that._y;
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy by assignment must end...");
	return *this;
}

unsigned int Spot::get_x() {
	return _x;
}

unsigned int Spot::get_y() {
	return _y;
}

bool Spot::properlyInitialized() {
	return _initCheck == this;
}

int Spot::get_height() {
	int total = 0;
	for (auto t: _stuff) {
		total += t->get_height();
	}
	return total;
}

MovableThing* Spot::get_upper() {
	return _upper;
}

void Spot::add_stuff(Thing* thing) {
	_stuff.push_back(thing);
}

bool Spot::add_upper(MovableThing* thing) {
	REQUIRE(_upper == nullptr, "_upper is occupied");
	
	for (auto t: _stuff) {
		t->onEnter(thing);
		if (! thing->is_alive()) {
			delete thing;
			return false;
		}
	}
	
	if (get_height() < 0) {
		// fallthrough
		add_stuff(thing);
		return true;
	} else {
		_upper = thing;
		return false;
	}
	return false;
}

void Spot::del_upper() {
	if (_upper != nullptr) {
		for (auto t: _stuff) {
			t->onLeave(_upper);
		}
		
		// thing wordt niet gedeleted, want add_upper of een andere collision (bv kill) zorgt hier voor.
		_upper = nullptr;
	}
}

std::ostream& operator<<(std::ostream& stream, Spot& spot) {
	Thing* most_imp_thing = spot.most_important_thing();
	if (most_imp_thing != nullptr) {
		stream << *most_imp_thing;
	}
	return stream;
}

Thing* Spot::most_important_thing() {
	int max = 0;
	Thing* th = nullptr;
	if (_upper != nullptr && _upper->get_importance() > 0) {
		max = _upper->get_importance();
		th = _upper;
	}

	for (auto t: _stuff) {
		if (t != nullptr && max < t->get_importance()) {
			max = t->get_importance();
			th = t;
		}
	}
	return th;
}

char Spot::to_char() {
	Thing* most_imp_thing = most_important_thing();
	if (most_imp_thing != nullptr) {
		return most_imp_thing->to_char();
	}
	return ' ';
}

