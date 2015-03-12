#include "board.h"
#include <string>
#include <vector>
#include <iostream>
#include "../../DesignByContract.h"

Board::Board(unsigned int width, unsigned int height):
	_width(width), _height(height),
	_data(std::vector<std::vector<Thing*>>(width, std::vector<Thing*>(height, nullptr)))
	{
	REQUIRE(width >= 0 && height >= 0, "incorrect height or width");
	_initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end ...");
}

bool Board::properlyInitialized() const {
	return _initCheck == this;
}

Board::~Board() {
	for (std::vector<std::vector<Thing*>>::iterator i = _data.begin(); i != _data.end(); ++i) {
		for (std::vector<Thing*>::iterator j = i->begin(); j != i->end(); ++j) {
			//std::cout << " ? deleting " << *j << std::endl;
			if (*j != nullptr) {
				//std::cout << "   deleted " << **j << std::endl;
				delete(*j);
			}
		}
	}
}

unsigned int Board::get_height() const {
	//REQUIRE(properlyInitialized(), "Board wasn't initialized when calling get_height");+
	unsigned int result = _height;
	ENSURE(result > 0, "Board has incorrect height or height is not returned correctly");
	return result;
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
	//REQUIRE(properlyInitialized(), "Board wasn't initialized when calling get_name");
	const std::string& result = _name;
	return result;
}

void Board::set_name(std::string& name) {
	//REQUIRE(properlyInitialized(), "Board wasn't initialized when calling set_name");
	_name = name;
	ENSURE(get_name() == name, "name not set correctly when calling set_name");
}

unsigned int Board::get_width() const {
	//REQUIRE(properlyInitialized(), "Board wasn't initialized when calling get_width");
	unsigned int result = _width;
	ENSURE(result > 0, "Board has incorrect width or width is not returned correctly");
	return result;
}

Thing*& Board::operator()(unsigned int x, unsigned int y) {
	//REQUIRE(properlyInitialized(), "Board wasn't initialized when calling operator()");
	return _data.at(x).at(y);
}

bool Board::valid_location(unsigned int x, unsigned int y) {
	//REQUIRE(properlyInitialized(), "Board wasn't initialized when calling valid_location");
	return 0<x && x<_width && 0<y && y<_height;
}

std::ostream& operator<< (std::ostream &out, Board& board) {
	//REQUIRE(board.properlyInitialized(), "Board wasn't initialized when calling oeprator <<");
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
