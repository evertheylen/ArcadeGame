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
#include "../game/board.h"

#ifndef _H_UI
#define _H_UI

class UI {
public:

	void run();

	//void input_board(TiXmlDocument& board_doc); Overbodig, wordt enkel gebruikt vanuit constructor.
	//void input_actions(TiXmlDocument& action_doc);

	void do_action(Game* g, int amount = 1);

	void write_board(std::string file, Game* g);
	void write_actions(std::string file, Game* g);

	void show(std::ostream& out);

	void help();

};



#endif /* _UI */
