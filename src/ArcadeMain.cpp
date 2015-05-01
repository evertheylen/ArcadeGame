#include <iostream>
#include <functional>

#include "game/game.h"
#include "parsers/game_parser.h"
#include "UI/UI.h"

#include "lib/tinyxml/tinyxml.h"

int main(int argc, const char** argv) {
	if (argc >= 3) {
		TiXmlDocument doc_board, doc_moves;
		
		bool board_loaded = doc_board.LoadFile(argv[1]);
		bool moves_loaded = doc_moves.LoadFile(argv[2]);

		if (!board_loaded) {
			std::cerr << "Error loading board.\n";
		}

		if (!moves_loaded) {
			std::cerr << "Error loading moves.\n";
		}

		if (!(board_loaded && moves_loaded)) {
			return 1;
		}
		
		TiXmlElement* board_el = doc_board.RootElement();
		TiXmlElement* moves_el = doc_board.RootElement();
		
		if (board_el == nullptr || moves_el == nullptr) {
			std::cerr << "Error loading root elements.\n";
			return 1;
		}
		
		Game_parser g(&std::cerr, std::string(argv[1]), std::string(argv[2]));
		
	} else {
		UI user_interface;
		user_interface.run();
	}
}


/*
 * TODO
 *  - Events based framework
 *  - Components
 *
 */
