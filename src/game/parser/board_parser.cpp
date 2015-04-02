/*
 * board_parser.cpp
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn
 */

#include "board_parser.h"
#include "../board/board.h"
#include "../board/barrel.h"
#include "../board/wall.h"
#include "../board/water.h"
#include "../board/button.h"
#include "../board/gate.h"
#include "../board/goal.h"
#include "../board/thing.h"
#include "../board/movable_thing.h"
#include "../board/living_thing.h"
#include "../board/boobytrap.h"
#include <iostream>
#include <string>

Board Board_parser::parse_board(TiXmlElement* board_elem, Game::Playermap& _players, Game::Gatemap& _gates) {
	// ---- Board ----

	Living_thing_parser lp;
	Thing_parser tp;

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
		// TODO alles pointers, zie ook zever met gates enzo
		//      LivingThing parser
		std::string tagname = current_el->Value();
		if (tagname == "NAAM") {
			boardname = readElement(current_el);
			board.set_name(boardname);
		} else if (tagname == "SPELER") {
			LivingThing* player = lp.parse_player(current_el, _players, board);
		} else if (tagname == "MONSTER") {
			LivingThing* monster = lp.parse_monster(current_el, _players, board);
		} else if (tagname == "MUUR") {
			Thing* wall = tp.parse_wall(current_el, board);
		} else if (tagname == "TON") {
			MovableThing* barrel = tp.parse_barrel(current_el, board);
		} else if (tagname == "WATER") {
			Thing* water = tp.parse_water(current_el, board);
		} else if (tagname == "POORT") {
			Thing* gate = tp.parse_gate(current_el, board, _gates);
		} else if (tagname == "DOEL") {
			Thing* goal = tp.parse_goal(current_el, board);
		} else if (tagname == "VALSTRIK") {
			Thing* boobytrap = tp.parse_boobytrap(current_el, board);
		} else if (tagname != "BREEDTE" && tagname != "LENGTE" && tagname != "KNOP") {
			std::string s = current_el->Value();
			//print(s + " not defined.");
		}
		current_el = current_el->NextSiblingElement();
	}

	current_el = board_elem->FirstChildElement();

	while (current_el != NULL) {
		if (current_el->ValueTStr() == "KNOP") {
			Thing* button = tp.parse_button(current_el, board, _gates);
		}
		current_el = current_el->NextSiblingElement();
	}

	return board;
}
