/*
 * board_parser.cpp
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn
 */

#include "board_parser.h"
#include "../board/board.h"
#include <iostream>
#include <string>

Board Board_parser::parse_board(TiXmlElement& board_elem, Game::Playermap& _players) {
	// ---- Board ----
	TiXmlElement* root = board_elem.FirstChildElement();
	if (root == NULL) throw(ParseError());
	// Warning, for some mysterious reason, root->Value() == "VELD" will always fail, even if it should definitly pass.
	if(root->ValueTStr() != "VELD") throw(ParseError());

	TiXmlElement* current_el = root->FirstChildElement();
	std::string boardname;
	_players = Game::Playermap();

	int x, y;
	try {
		x = std::stoi(readElement(root, "BREEDTE"));
		y = std::stoi(readElement(root, "LENGTE"));
	} catch (std::invalid_argument& e) {
		throw(ParseError());
		//REQUIRE(false, "Invalid BREEDTE or LENGTE in board file.");
	}

	if (x<1 || y<1) {
		throw(ParseError());	//TODO Inside function out << "Error: Invalid board dimensions.\n";
	}

	//_board = Board(x, y);

	Board board(x, y);

	while (current_el != NULL) {
		if (current_el->ValueTStr() == "NAAM") {
			boardname = readElement(current_el);
			board.set_name(boardname);
		} else if (current_el->ValueTStr() == "SPELER") {
			//parsePlayer(current_el, out);
		} else if (current_el->ValueTStr() == "OBSTAKEL") {
			//parseObstacle(current_el, out);
		} else if (current_el->ValueTStr() != "BREEDTE" && current_el->ValueTStr() != "LENGTE") {
			std::string s = current_el->Value();
			//print(s + " not defined.");
		}
		current_el = current_el->NextSiblingElement();
	}
	return board;
}
