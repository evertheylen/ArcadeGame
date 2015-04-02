/*
 * game_parser.cpp
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn & evert
 */

#include "game_parser.h"
#include "../../../lib/tinyxml/tinyxml.h"
#include "board_parser.h"
#include "movement_parser.h"
#include "../game.h"
#include <iostream>

#include <list>

Game Game_parser::parse_game(TiXmlElement* board_elem, TiXmlElement* move_elem, std::ostream& output_stream) {
	Game::Playermap players;
	Game::Gatemap gates;
	Board_parser bp;
	Board board = bp.parse_board(board_elem, players, gates);
	Movement_parser mp;
	std::list<Movement> moves = mp.parse_movement(move_elem, players);

	/*for (int i = 0; i != moves.size(); i++) {
		std::cout << moves.front().get_dir_name() << std::endl;
		moves.pop_front();
	}*/
	//Game g(bp.parse_board(board_elem, players), mp.parse_movement(move_elem, players), players, output_stream);
	Game g(board, moves, players, output_stream);
	return g;
}


