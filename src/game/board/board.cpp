#include "board.h"
#include <string>

Board::Board(unsigned int width, unsigned int height):
	_width(width), _height(height),
	_data(std::vector<std::vector<Thing*>>(width, std::vector<Thing*>(height, nullptr)))
	{}

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

Thing* Board::operator()(unsigned int x, unsigned int y) {
	return _data.at(x).at(y);
}

