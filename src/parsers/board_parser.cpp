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
#include "../game/game.h"
#include <iostream>
#include <string>

Board_parser::Board_parser(std::ostream* stream, std::string filename):
		Parser(stream, filename) {}

Board* Board_parser::parse_board(TiXmlElement* board_elem, Game* game) {
	Actor_parser lp(_out, _filename);
	Entity_parser tp(_out, _filename);

	if (board_elem == NULL) fatal("Board was null", board_elem);

	TiXmlElement* current_el = board_elem->FirstChildElement();
	std::string boardname;
	
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
	
	Board* bp = new Board(x, y, game);
	while (current_el != NULL) {
		try {
			// TODO alles pointers, zie ook zever met gates enzo
			//      Actor parser
			std::string tagname = current_el->Value();

			if (tagname == "NAAM") {
				boardname = readElement(current_el);
				bp->set_name(boardname);
			} else if (tagname == "SPELER" || tagname == "MONSTER" || tagname == "TON") {
				Entity* entity;
				if (tagname == "SPELER") {
					Player* p = lp.parse_player(current_el, *bp);
					if (game->get_monster(p->get_name()) != nullptr) {
						fatal("Player with that name already exists.", current_el);
					}
					game->add_player(p);
					entity = p;
				} else if (tagname == "MONSTER") {
					Monster* m = lp.parse_monster(current_el, (*bp));
					if (game->get_monster(m->get_name()) != nullptr) {
						fatal("Monster with that name already exists.", current_el);
					}
					game->add_monster(m);
					entity = m; // downcast
				} else if (tagname == "TON") {
					entity = tp.parse_barrel(current_el, (*bp));
				}

				unsigned int x = entity->x;
				unsigned int y = entity->y;

				bp->enter_top_location(entity, x, y);

			} else if (tagname == "MUUR" || tagname == "WATER" || tagname == "POORT" || tagname == "DOEL" || tagname == "VALSTRIK") {
				Entity* entity;
				if (tagname == "MUUR") {
					entity = tp.parse_wall(current_el, (*bp));
				}  else if (tagname == "WATER") {
					entity = tp.parse_water(current_el, (*bp), game);
				} else if (tagname == "POORT") {
					Gate* g = tp.parse_gate(current_el, (*bp));
					if (game->get_gate(g->get_name()) != nullptr) {
						log("Replacing dummy gate.");
						//fatal("Gate with that name already exists.\n;", current_el);
						*game->get_gate(g->get_name()) = *g;
						Parser::dummyset --;
					} else {
						game->add_gate(g);
					}
					entity = g; // downcast
				} else if (tagname == "DOEL") {
					entity = tp.parse_goal(current_el, (*bp));
				} else if (tagname == "VALSTRIK") {
					entity = tp.parse_boobytrap(current_el, (*bp));
				}
				
				unsigned int x = entity->x;
				unsigned int y = entity->y;
				
				bp->enter_location(entity, x, y);
				
			} else if (tagname != "BREEDTE" && tagname != "LENGTE" && tagname != "KNOP") {
				std::string s = current_el->Value();
				log(std::string("Didnt understand tag ") + s, current_el);
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
	// Parse buttons latest, because they need all the gates to be parsed already
	while (current_el != NULL) {
		try {
			if (current_el->ValueTStr() == "KNOP") {  // TODO Fix that buttons work.
				Entity* entity = tp.parse_button(current_el, (*bp), game);

				unsigned int x = entity->x;
				unsigned int y = entity->y;

				bp->enter_location(entity, x, y);
			}
		} catch (ParseError& e) {
			log(e.what(), board_elem);
		}
		current_el = current_el->NextSiblingElement();
	}
	
//	std::cout << *bp << std::endl;
	if (Parser::dummyset != 0) {
		fatal("Not all dummy gates are replaced!");
	}
	return bp;
}
