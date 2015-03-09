#include "board.h"
#include <string>
#include <vector>
#include <iostream>

Board::Board(unsigned int width, unsigned int height):
	_width(width), _height(height),
	_data(std::vector<std::vector<Thing*>>(width, std::vector<Thing*>(height, nullptr)))
	{}

Board::~Board() {
	for (std::vector<std::vector<Thing*>>::iterator i = _data.begin(); i != _data.end(); ++i) {
		for (std::vector<Thing*>::iterator j = i->begin(); j != i->end(); ++j) {
			std::cout << " ? deleting " << *j << std::endl;
			if (*j != nullptr) {
				std::cout << "   deleted " << **j << std::endl;
				delete(*j);
			}
		}
	}
}

unsigned int Board::get_height() const {
	return _height;
}

/*void Board::set_height(unsigned int y) {
	_height = y;
	_data = std::vector<std::vector<Thing*>>(_width, std::vector<Thing*>(_height, nullptr));
}

void Board::set_width(unsigned int x) {
	_width = x;
	_data = std::vector<std::vector<Thing*>>(_width, std::vector<Thing*>(_height, nullptr));
}*/

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

std::ostream& operator<< (std::ostream &out, Board& board) {
	for (int j=board.get_height()-1; j>=0; --j) {
		// print row
		for (int i=0; i<board.get_width(); ++i) {
			if (board(i,j) != nullptr) {
				out << board(i,j)->to_char();
			} else {
				out << " ";
			}
		}
		out << "\n";
	}
	return out;
}
