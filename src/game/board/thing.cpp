#include "thing.h"

Thing::Thing() {}

Thing::Thing(unsigned int x, unsigned int y, int weight):
	_x(x), _y(y), _weight(weight)
	{}

bool Thing::is_movable() const {
	return _weight>=0;
}

int Thing::get_weight() const {
	return _weight;
}

void Thing::set_weight(int weight) {
	_weight = weight;
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
