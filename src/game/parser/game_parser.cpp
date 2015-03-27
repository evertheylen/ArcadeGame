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

#include <list>

Game Game_parser::parse_game(TiXmlElement* board_elem, TiXmlElement* move_elem, std::ostream& output_stream) {
	Game::Playermap players;
	Board_parser bp;
	//Board board = bp.parse_board(board_elem, players);

	Movement_parser mp;
	//std::list<Movement> moves = mp.parse_movement(move_elem, players);

	Game g(bp.parse_board(board_elem, players), mp.parse_movement(move_elem, players), players, output_stream);
}


