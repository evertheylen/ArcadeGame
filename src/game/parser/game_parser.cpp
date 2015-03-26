/*
 * game_parser.cpp
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn & evert
 */

#include "game_parser.h"
#include "../../../lib/tinyxml/tinyxml.h"
#include "player_parser.h"
#include "obstacle_parser.h"

Game Game_parser::parse_game(TiXmlElement& board_elem, TiXmlElement& move_elem) {
		// ---- Board ----
		TiXmlElement* root = board_elem.FirstChildElement();
		if (root == NULL) throw(ParseError());
		// Warning, for some mysterious reason, root->Value() == "VELD" will always fail, even if it should definitly pass.
		if(root->ValueTStr() != "VELD") throw(ParseError());

		TiXmlElement* current_el = root->FirstChildElement();
		std::string boardname;
		_players = Playermap();

		int x, y;
		try {
			x = std::stoi(readElement(root, "BREEDTE"));
			y = std::stoi(readElement(root, "LENGTE"));
		} catch (std::invalid_argument& e) {
			throw(ParseError());
			//REQUIRE(false, "Invalid BREEDTE or LENGTE in board file.");
		}

		if (x<1 || y<1) {
			out << "Error: Invalid board dimensions.\n";
			throw(ParseError());
		}

		_board = Board(x, y);

		while (current_el != NULL) {
			if (current_el->ValueTStr() == "NAAM") {
				boardname = readElement(current_el);
				_board.set_name(boardname);
			} else if (current_el->ValueTStr() == "SPELER") {
				parsePlayer(current_el, out);
			} else if (current_el->ValueTStr() == "OBSTAKEL") {
				parseObstacle(current_el, out);
			} else if (current_el->ValueTStr() != "BREEDTE" && current_el->ValueTStr() != "LENGTE") {
				out << "Error: Error: tag " << current_el->Value() << " not defined.\n";
			}
			current_el = current_el->NextSiblingElement();
		}


		// ---- Movements ----
		root = move_elem.FirstChildElement();
		REQUIRE(root != NULL, "Failed to load movements file: No root element.");
		REQUIRE(root->ValueTStr() == "BEWEGINGEN", "Failed to load movements file: Wrong root element tag.");
		current_el = root->FirstChildElement();
		TiXmlElement* current_el_2;
		while (current_el != NULL) {
			if (current_el->ValueTStr() == "BEWEGING") {
				current_el_2 = current_el->FirstChildElement();
				while (current_el_2 != NULL) {
					if (current_el_2->ValueTStr() != "SPELERNAAM"
							&& current_el_2->ValueTStr() != "RICHTING") {
						out << "Error: Error: tag " << current_el->Value() << " not defined.\n";
					}
					current_el_2 = current_el_2->NextSiblingElement();
				}
				std::string dir_s = readElement(current_el, "RICHTING");
				std::string player_name = readElement(current_el, "SPELERNAAM");

				Direction dir = toDirection(dir_s);
				if (dir == Direction::no_dir) {
					out << "Error: Invalid direction specified, skipping movement in movement file.\n";
					current_el = current_el->NextSiblingElement();
					continue;
				}

				if (_players.find(player_name) == _players.end()) {
					out << "Error: Invalid player specified, skipping movement in movement file.\n";
					current_el = current_el->NextSiblingElement();
					continue;
				}

				_movements.push_back(Movement(dir, _players[player_name]));
			} else {
				out << "Error: tag " << current_el->Value() << " not defined.\n";
			}
			current_el = current_el->NextSiblingElement();
		}

		_initCheck = this;
		ENSURE(properlyInitialized(), "Constructor of Game did not end properly.");
}


