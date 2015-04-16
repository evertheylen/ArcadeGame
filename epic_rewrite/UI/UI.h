/*
 * UI.h
 *
 *  Created on: 16 Apr 2015
 *      Author: stijn
 */

#include "../../lib/tinyxml/tinyxml.h"
#include <fstream>
#include <iostream>
#include "../game/game.h"

#ifndef _UI
#define _UI

class UI {
public:

	UI();

	void input_board(TiXmlDocument& board_doc);
	void input_actions(TiXmlDocument& action_doc);

	void do_action(int amount = 1);

	void write_board(std::fstream& out);
	void write_actions(std::fstream& out);

	void show(std::ostream& out = std::cout);

	void help();

};



#endif /* _UI */
