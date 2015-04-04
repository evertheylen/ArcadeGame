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

Board* Board_parser::parse_board(TiXmlElement* board_elem, Game::Playermap& _players, Game::Gatemap& _gates) {
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
	Board* bp;
	bp =  new Board(x, y);

	while (current_el != NULL) {
		// TODO alles pointers, zie ook zever met gates enzo
		//      LivingThing parser
		std::string tagname = current_el->Value();

		if (tagname == "NAAM") {
			boardname = readElement(current_el);
			(*bp).set_name(boardname);
		} else if (tagname == "SPELER" || tagname == "MONSTER") {
			LivingThing* liv_thing;
			if (tagname == "SPELER") {
				liv_thing = lp.parse_player(current_el, _players, (*bp));
			} else if (tagname == "MONSTER") {
				liv_thing = lp.parse_monster(current_el, _players, (*bp));
			}

			unsigned int x = liv_thing->get_x();
			unsigned int y = liv_thing->get_y();

			(*bp)(x,y)->add_upper(liv_thing);

		} else if (tagname == "TON") {
			MovableThing* mov_thing = tp.parse_barrel(current_el, (*bp));

			unsigned int x = mov_thing->get_x();
			unsigned int y = mov_thing->get_y();

			(*bp)(x,y)->add_upper(mov_thing);	// TODO Testcase! Add water after barrel and see the magic happen.

		} else if (tagname == "MUUR" || tagname == "WATER" || tagname == "POORT" || tagname == "DOEL" || tagname == "VALSTRIK") {
			Thing* thing;
			if (tagname == "MUUR") {
				thing = tp.parse_wall(current_el, (*bp));
			}  else if (tagname == "WATER") {
				thing = tp.parse_water(current_el, (*bp));
			} else if (tagname == "POORT") {
				thing = tp.parse_gate(current_el, (*bp), _gates);
			} else if (tagname == "DOEL") {
				thing = tp.parse_goal(current_el, (*bp));
			} else if (tagname == "VALSTRIK") {
				thing = tp.parse_boobytrap(current_el, (*bp));
			}

			unsigned int x = thing->get_x();
			unsigned int y = thing->get_y();

			(*bp)(x,y)->add_stuff(thing);

		} else if (tagname != "BREEDTE" && tagname != "LENGTE" && tagname != "KNOP") {
			std::string s = current_el->Value();
			//print(s + " not defined.");
		}
		current_el = current_el->NextSiblingElement();
	}

	current_el = board_elem->FirstChildElement();

	while (current_el != NULL) {
		if (current_el->ValueTStr() == "KNOP") {					// TODO Fix that buttons work.
			Thing* thing = tp.parse_button(current_el, (*bp), _gates);

			unsigned int x = thing->get_x();
			unsigned int y = thing->get_y();

			(*bp)(x,y)->add_stuff(thing);
		}
		current_el = current_el->NextSiblingElement();
	}

	std::cout << *bp << std::endl;

	return bp;
}
