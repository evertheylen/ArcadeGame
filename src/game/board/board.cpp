#include "board.h"
#include <string>
#include <vector>

Board::Board(unsigned int width, unsigned int height):
	_width(width), _height(height),
	_data(std::vector<std::vector<Thing*>>(width, std::vector<Thing*>(height, nullptr)))
	{}

Board::~Board() {
	for (std::vector<std::vector<Thing*>>::iterator i = _data.begin(); i != _data.end(); ++i) {
		for (std::vector<Thing*>::iterator j = i->begin(); j != i->end(); ++j) {
			delete(*j);
		}
	}
}

unsigned int Board::get_height() const {
	return _height;
}

const std::string& Board::get_name() const {
	return _name;
}

void Board::set_name(std::string& name) {
	_name = name;
}

unsigned int Board::get_width() const {
	return _width;
}

Thing*& Board::operator()(unsigned int x, unsigned int y) {
	return _data.at(x).at(y);
}

