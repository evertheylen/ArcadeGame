#include <iostream>
#include <functional>
#include <fstream>

#include "game/game.h"
#include "parsers/game_parser.h"
#include "UI/UI.h"

#include "lib/tinyxml/tinyxml.h"

int main(int argc, const char** argv) {
	if (argc == 2) {
		UI user_interface;
		std::string arg(argv[1]);
		for (auto s: split(arg, ';')) {
			std::cout << "\033[1;38;2;255;0;0;48;2;0;0;0m> " << s << "\033\[m\n";
			user_interface.fancy_command(s);
		}
	} else if (argc == 3) {
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

		Game_parser gp(&std::cerr, std::string(argv[1]));
		Game* g = gp.parse_game(doc_board.FirstChildElement(), doc_moves.FirstChildElement());
		
		std::ofstream output_file;
		
		output_file.open("ResterendeBewegingen_begin.txt");
		g->write_actions(output_file);
		output_file.close();
		
		g->do_all_actions(std::cout);
		
		output_file.open("HuidigSpeelveld.txt");
		g->get_board()->write_board(output_file);
		output_file.close();
		
		output_file.open("ResterendeBewegingen_einde.txt");
		g->write_actions(output_file);
		output_file.close();
		
		delete g;
	} else {
		UI user_interface;
		user_interface.run();
	}
}
