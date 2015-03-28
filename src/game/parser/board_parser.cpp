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

Board Board_parser::parse_board(TiXmlElement* board_elem, Game::Playermap& _players) {
	// ---- Board ----

	Player_parser pp;

	if (board_elem == NULL) throw(ParseError());

	TiXmlElement* current_el = board_elem->FirstChildElement();
	std::string boardname;
	_players = Game::Playermap();

	int x, y;
	try {
		x = std::stoi(readElement(board_elem, "BREEDTE"));
		y = std::stoi(readElement(board_elem, "LENGTE"));
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
			pp.parse_player(current_el, _players, board);
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
