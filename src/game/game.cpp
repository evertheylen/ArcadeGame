#include "game.h"
#include <vector>
#include <algorithm>

Game::Game(TiXmlDocument& doc) :
		_board(Board(0, 0)) {
	_players = std::vector<Player>( { Player("Stijn"), Player("Evert") });
	_board = Board(20, 20);
	_movements = std::vector<Movement>( { Movement(Direction::up, &_players[0]),
			Movement(Direction::down, &_players[1]), });

	TiXmlElement * root = doc.FirstChildElement();
	if (root == NULL) {
		std::cerr << "Failed to load file: No root element." << std::endl;
		doc.Clear();
		return;
	}

	forceLowerCase(root);

	std::string boardname = readElement(root, "naam");
	int x = atoi(readElement(root, "breedte").c_str());
	int y = atoi(readElement(root, "lengte").c_str());
	_board = Board(x, y);
	_board.set_name(boardname);

	std::cout << "Width: " << _board.get_width() << "   Height: " << _board.get_height() << "   Name: " << _board.get_name() << std::endl;


}

void Game::forceLowerCase(TiXmlElement* elem) {

	//TODO This function loops through all "first" elements of the xml-file. Therefore elements like type or playername or not yet converted.
	// I don't know how to fix this yet though.

	TiXmlNode* child = 0;
	while (child = elem->IterateChildren(child)) {
		std::string data = child->Value();
		std::transform(data.begin(), data.end(), data.begin(), ::tolower);
		const char * data2 = data.c_str();
		child->SetValue(data2);
	}
	return;
}

std::string Game::readElement(TiXmlElement* elem, const char* tag) {
	TiXmlElement* e = elem->FirstChildElement(tag);
	if (e == NULL) {
		std::cerr << "Error: Tag not defined.";
	}
	TiXmlNode* node = e->FirstChild();
	TiXmlText* text = node->ToText();
	return text->Value();
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
	std::cout << "do move with player " << movement.get_player()->get_name()
			<< "\n";
}
