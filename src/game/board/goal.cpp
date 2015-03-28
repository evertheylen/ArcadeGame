#include "goal.h"
#include "../../DesignByContract.h"

Goal::Goal(unsigned int x, unsigned int y):
	Thing(x,y,GOAL_WEIGHT,GOAL_HEIGHT,GOAL_IMPORTANCE)
	{
	REQUIRE(x >= 0 && y >= 0, "Incorrect arguments specified for constructor of goal");
	_initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end...");
}

// copy constructor
Goal::Goal(const Goal& that):
	Thing(that) {
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy constructor must end...");
}

// copy assignment
Goal& Goal::operator=(const Goal& that) {
	Thing::operator=(that);
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy by assignment must end...");
	return *this;
}

std::ostream& Goal::print(std::ostream& out){
	REQUIRE(properlyInitialized(), "Goal wasn't initialized when calling print");
	out << "Goal\n";
	return out;
}

char Goal::to_char() {
	REQUIRE(properlyInitialized(), "Goal wasn't initialized when calling print");
	return '#';
}

void Goal::onEnter(MovableThing* other) {
	other->end_game();  // will usually not do anything, except for players
}
