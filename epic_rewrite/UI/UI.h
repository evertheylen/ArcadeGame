/*
 * UI.h
 *
 *  Created on: 16 Apr 2015
 *      Author: stijn
 */

#include "../../lib/tinyxml/tinyxml.h"
#include <string>
#include <iostream>
#include "../game/game.h"

#ifndef _UI
#define _UI

class UI {
public:

	UI();

	//void input_board(TiXmlDocument& board_doc); Overbodig, wordt enkel gebruikt vanuit constructor.
	//void input_actions(TiXmlDocument& action_doc);

	void do_action(int amount = 1);

	void write_board(std::string file, Game& g);
	void write_actions(std::string file, Game& g);

	void show(std::ostream& out);

	void help();

};



#endif /* _UI */