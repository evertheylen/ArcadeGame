/*
 * game_parser.cpp
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn & evert
 */

#include "game_parser.h"
#include "../../../lib/tinyxml/tinyxml.h"
#include "board_parser.h"
#include "action_parser.h"
#include "../game/game.h"
#include <string>
#include <iostream>

#include <list>


Game_parser::Game_parser(std::ostream* stream, std::string _board_filename, std::string _actions_filename):
		Parser(stream, "internal"), board_filename(_board_filename), actions_filename(_actions_filename) {}

Game* Game_parser::parse_game(TiXmlElement* board_elem, TiXmlElement* move_elem) {
	log("Game parser started", board_elem);
	Game* gp = new Game;

	Board_parser bp(_out, board_filename);
	
	gp->set_board(bp.parse_board(board_elem, gp));
	
	if (move_elem != nullptr) {
		Action_parser ap(_out, actions_filename);
		gp->actions = ap.parse_action(move_elem, gp);
	}

	return gp;
}


