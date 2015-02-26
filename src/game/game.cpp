#include "game.h"
#include <vector>

Game::Game(TiXmlDocument& doc):
	_board(Board(0,0)){
	_players = std::vector<Player>({Player("Stijn"), Player("Evert")});
	_board = Board(20,20);
	_movements = std::vector<Movement>({
		Movement(Direction::up, &_players[0]),
		Movement(Direction::down, &_players[1]),
	});
}

void Game::writeBoard(std::ostream& stream) {
	stream << "board\n";
}

void Game::writeMovements(std::ostream& stream) {
	stream << "movements\n";
}

void Game::popMove() {
	std::cout << "popped\n";
	doMove(_movements.back());
	// TODO POP
}

void Game::doMove(Movement& movement) {
	std::cout << "do move with player " << movement.get_player()->get_name() << "\n";
}
