/*
 * UI.h
 *
 *  Created on: 16 Apr 2015
 *      Author: stijn
 */

#include "../../lib/tinyxml/tinyxml.h"
#include <string>
#include <vector>
#include <iostream>
#include "../game/game.h"
#include "../game/board.h"

#ifndef _H_UI
#define _H_UI

class UI {
public:
	UI();
	
	void reset();
	
	void run();
	
	void fancy_command(std::string& command);
	
	bool parse_and_do(std::string& command);


	// help
	void help();
	// read_board
	void read_board(std::string& filename);
	// read_actions
	void read_actions(std::string& filename);
	// simulate
	void simulate();
	// write_board
	void write_board(std::ostream& out);
	// write_actions
	void write_actions(std::ostream& out);
	// show
	void show(std::ostream& out);
	
	// returns whether or not the game is ready
	bool init_game();


private:
	
	bool board_loaded;
	bool actions_loaded;
	bool parsed;
	Game* g;
	TiXmlDocument doc_board;
	TiXmlDocument doc_actions;
	
	bool reparse_board;
	bool reparse_actions;
};

std::vector<std::string> split(std::string& s, char delim);

#endif /* _H_UI */
