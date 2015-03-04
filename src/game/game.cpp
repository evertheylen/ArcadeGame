#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>

#include "game.h"
#include "board/barrel.h"
#include "board/wall.h"
#include "movement/movement.h"

Game::Game(TiXmlDocument& board_doc, TiXmlDocument& moves_doc) {
	TiXmlElement* root = board_doc.FirstChildElement();
	if (root == NULL) {
		std::cerr << "Failed to load board file: No root element." << std::endl;
		board_doc.Clear();
		return;
		// TODO proper error handling, also below
	}

	// Load Board properties
	std::string boardname = readElement(root, "NAAM");
	int x = atoi(readElement(root, "BREEDTE").c_str());
	int y = atoi(readElement(root, "LENGTE").c_str());

	// TODO Check on error atoi. If it returns 0 -> error.

	_board = Board(x, y);
	_board.set_name(boardname);

	std::cout << "Width: " << _board.get_width() << "   Height: "
			<< _board.get_height() << "   Name: " << _board.get_name()
			<< std::endl;

	// Load players
	_players = Playermap();

	for (TiXmlElement* player_el = root->FirstChildElement("SPELER");
			player_el != NULL;
			player_el = player_el->NextSiblingElement("SPELER")) {
		std::string name = readElement(player_el, "NAAM");
		unsigned int x = atoi(readAttribute(player_el, "x").c_str());
		unsigned int y = atoi(readAttribute(player_el, "y").c_str());
		Player* player = new Player(name, x, y);
		_players[name] = *player;

		// Put on board
		_board(x,y) = player;

		std::cout << _players[name].get_name() << std::endl;
	}

	// Obstacles
	for (TiXmlElement* obstacle_el = root->FirstChildElement("OBSTAKEL");
			obstacle_el != NULL;
			obstacle_el = obstacle_el->NextSiblingElement("OBSTAKEL")) {
		std::string type = readElement(obstacle_el, "TYPE");
		unsigned int x = atoi(readAttribute(obstacle_el, "x").c_str());
		unsigned int y = atoi(readAttribute(obstacle_el, "y").c_str());

		Thing* obst;
		if (type == "ton") {
			// TODO check beweegbaar
			obst = new Barrel(x,y);
		} else if (type == "muur") {
			// TODO check beweegbaar
			obst = new Wall(x,y);
		}

		// Put on board
		_board(x,y) = obst;

		std::cout << _board(x,y)->is_movable() << "\n";
	}

	// Movements
	root = moves_doc.FirstChildElement();
	if (root == NULL) {
		std::cerr << "Failed to load movements file: No root element." << std::endl;
		moves_doc.Clear();
		return;
	}
	std::cout << "Starting..\n";
	for (TiXmlElement* move_el = root->FirstChildElement("BEWEGING");
				move_el != NULL;
				move_el = move_el->NextSiblingElement("BEWEGING")) {
			std::string dir_s = readElement(move_el, "RICHTING");
			std::string player_name = readElement(move_el, "SPELERNAAM");

			Movement move(dir_s, &_players[player_name]);
			_movements.push_back(move);

			std::cout << _movements.back().get_dir() << "\n";
	}
}

void Game::forceLowerCase(TiXmlElement* elem) {

	// TODO This function loops through all "first" elements of the xml-file. Therefore elements like type or playername or not yet converted.
	// I don't know how to fix this yet though.

	TiXmlNode* child = 0;
	while (child = elem->IterateChildren(child)) {
		std::string data = child->Value();
		std::transform(data.begin(), data.end(), data.begin(), ::tolower);
		const char * data2 = data.c_str();
		child->SetValue(data2);
		//std::cout << child->Value() << std::endl;
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

std::string Game::readAttribute(TiXmlElement* elem, const char* tag) {
	return std::string(elem->Attribute(tag));
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
