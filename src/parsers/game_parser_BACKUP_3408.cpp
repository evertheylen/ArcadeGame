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
<<<<<<< HEAD:src/game/parser/game_parser.cpp
#include "../game.h"
=======
#include "../game/game.h"
>>>>>>> rewrite:epic_rewrite/parsers/game_parser.cpp
#include <string>
#include <iostream>

#include <list>


Game_parser::Game_parser(std::ostream* stream, std::string filename):
		Parser(stream, filename) {}

Game* Game_parser::parse_game(TiXmlElement* board_elem, TiXmlElement* move_elem) {
	log("Game parser started", board_elem);
	Game* gp = new Game;
	Game::Playermap players;
	Game::Monstermap monsters;
	Game::Gatemap gates;
	Board_parser bp(_out, _filename);
<<<<<<< HEAD:src/game/parser/game_parser.cpp
	Action_parser mp(_out, "not unknown");  // TODO second filename!!
	
	Board* board = bp.parse_board(board_elem, players, gates);
	std::list<Action> moves = *mp.parse_actions(move_elem, players);
=======
	Action_parser ap(_out, "not unknown");  // TODO second filename!!
	
	Board* board = bp.parse_board(board_elem, players, gates, monsters, gp);
	std::list<Action*>* actions = ap.parse_action(move_elem, players);
>>>>>>> rewrite:epic_rewrite/parsers/game_parser.cpp

	//std::cout << *board << std::endl;
	/*for (int i = 0; i != moves.size(); i++) {
		std::cout << moves.front().get_dir_name() << std::endl;
		moves.pop_front();
	}*/
	//Game g(bp.parse_board(board_elem, players), mp.parse_movement(move_elem, players), players, output_stream);
	//gp = new Game(board, actions, players, monsters, gates);

	gp->board = *board;
	gp->actions = *actions;
	gp->monstermap = monsters;
	gp->playermap = players;
	gp->gatemap = gates;

	std::cout << "Height::" << gp->board.get_height() << std::endl;

	return gp;
}


