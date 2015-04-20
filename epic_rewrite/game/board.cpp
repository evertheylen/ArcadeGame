
#include "board.h"
#include "game.h"

Board::Board(unsigned int _width, unsigned int _height, Game* _game):
		width(_width), height(_height), game(_game),
		topdata(std::vector<std::vector<Entity*>>(width, std::vector<Entity*>(height, nullptr))),
		data(std::vector<std::vector<std::vector<Entity*>>>(width, std::vector<std::vector<Entity*>>(height, std::vector<Entity*>(0))))
		{}

Entity* Board::get_top(unsigned int x, unsigned int y) {
	return topdata.at(x).at(y);
}

Entity* Board::get(unsigned int loc, unsigned int x, unsigned int y) {
	std::vector<Entity*>& spot = data.at(x).at(y);
	if (spot.size() > loc)
		return nullptr;
	return spot[loc];
}
