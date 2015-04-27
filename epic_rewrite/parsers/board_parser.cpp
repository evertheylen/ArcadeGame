/*
 * board_parser.cpp
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn
 */

#include "board_parser.h"
#include "../game/board.h"
#include "../entities/barrel.h"
#include "../entities/wall.h"
#include "../entities/water.h"
#include "../entities/button.h"
#include "../entities/gate.h"
#include "../entities/goal.h"
#include "../entities/entity.h"
#include "../entities/actor.h"
#include "../entities/boobytrap.h"
#include "../game.h"
#include <iostream>
#include <string>

Board_parser::Board_parser(std::ostream* stream, std::string filename):
		Parser(stream, filename) {}

Board* Board_parser::parse_board(TiXmlElement* board_elem, Game::Playermap& _players, Game::Gatemap& _gates) {
	Actor_parser lp(_out, _filename);
	Entity_parser tp(_out, _filename);

	if (board_elem == NULL) fatal("Board was null", board_elem);

	TiXmlElement* current_el = board_elem->FirstChildElement();
	std::string boardname;
	_players = Game::Playermap();
	
	int x, y;
	try {
		x = std::stoi(readElement(board_elem, "BREEDTE"));
		y = std::stoi(readElement(board_elem, "LENGTE"));
	} catch (std::invalid_argument& e) {
		fatal("Invalid BREEDTE or LENGTE in board file.", board_elem);
	}

	if (x<1 || y<1) {
		fatal("Invalid board dimensions", board_elem);
	}
	
	Board* bp;
	bp = new Board(x, y);

	while (current_el != NULL) {
		try {
			// TODO alles pointers, zie ook zever met gates enzo
			//      Actor parser
			std::string tagname = current_el->Value();

			if (tagname == "NAAM") {
				boardname = readElement(current_el);
				(*bp).set_name(boardname);
			} else if (tagname == "SPELER" || tagname == "MONSTER") {
				Actor* actor;
				if (tagname == "SPELER") {
					actor = lp.parse_player(current_el, _players, (*bp));
				} else if (tagname == "MONSTER") {
					actor = lp.parse_monster(current_el, _players, (*bp));
				}

				unsigned int x = actor->get_x();
				unsigned int y = actor->get_y();

				(*bp)(x,y)->add_upper(actor);

			} else if (tagname == "MUUR" || tagname == "WATER" || tagname == "POORT" || tagname == "DOEL" || tagname == "VALSTRIK" || tagname == "TON") {
				Entity* entity;
				if (tagname == "MUUR") {
					entity = tp.parse_wall(current_el, (*bp));
				}  else if (tagname == "WATER") {
					entity = tp.parse_water(current_el, (*bp));
				} else if (tagname == "POORT") {
					entity = tp.parse_gate(current_el, (*bp), _gates);
				} else if (tagname == "DOEL") {
					entity = tp.parse_goal(current_el, (*bp));
				} else if (tagname == "VALSTRIK") {
					entity = tp.parse_boobytrap(current_el, (*bp));
				}
				
				unsigned int x = entity->get_x();
				unsigned int y = entity->get_y();
				
				auto whatever = (*bp)(x,y);
				whatever->add_stuff(entity);
				
			} else if (tagname != "BREEDTE" && tagname != "LENGTE" && tagname != "KNOP") {
				std::string s = current_el->Value();
				// TODO log or fatal?
			}
		} catch (ParseError& e) {
			log(e.what(), board_elem);
		}
		
		if (current_el == nullptr) {
			std::cerr << "WTF";
		}
		current_el = current_el->NextSiblingElement();
	}
	
	current_el = board_elem->FirstChildElement();
	
	while (current_el != NULL) {
		try {
			if (current_el->ValueTStr() == "KNOP") {  // TODO Fix that buttons work.
				Entity* entity = tp.parse_button(current_el, (*bp), _gates);

				unsigned int x = entity->get_x();
				unsigned int y = entity->get_y();

				(*bp)(x,y)->add_stuff(entity);
			}
		} catch (ParseError& e) {
			log(e.what(), board_elem);
		}
		current_el = current_el->NextSiblingElement();
	}
	
	std::cout << *bp << std::endl;

	return bp;
}
