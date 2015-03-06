#include "thing.h"

Thing::Thing() {}

Thing::Thing(unsigned int x, unsigned int y, bool movable):
	_x(x), _y(y), _movable(movable)
	{}

bool Thing::is_movable() const {
	return _movable;
}

void Thing::set_movable(bool movable) {
	_movable = movable;
}

unsigned int Thing::get_x() const {
	return _x;
}

void Thing::set_x(unsigned int x) {
	_x = x;
}

unsigned int Thing::get_y() const {
	return _y;
}

void Thing::set_y(unsigned int y) {
	_y = y;
}

/*void Thing::print(){
	std::cout << "Thing" << std::endl;
}*/

std::ostream& Thing::print(std::ostream& out) {
	out << "Thing" << std::endl;
	return out;
}

std::ostream& operator<< (std::ostream &out, Thing &thing){
	thing.print(out);
	return out;
}

char Thing::to_char() {
	return 'T';
}
