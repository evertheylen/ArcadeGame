#include <iostream>
#include <functional>
#include <fstream>

#include <csignal>

#include "game/game.h"
#include "parsers/game_parser.h"
#include "UI/UI.h"

#include "server/server.h"

#include "lib/tinyxml/tinyxml.h"


void help() {
	std::cout
			<< "Please specify a command.\n"
			<< "    run <board.xml> <moves.xml>\n"
			<< "    server <board.xml> <moves.xml> <port=8080>\n"
			<< "    ui\n"
			<< "    exec ui_cmd;ui_cmd;...\n";
}

void control_c(int s) {
	std::cout << "Application shutting down.\n";
	exit(1);
}

int main(int argc, const char** argv) {
	if (argc < 2) {
		help();
		return 0;
	}
	
	// Set SIGINT handler
	// http://stackoverflow.com/a/1641223/2678118
	struct sigaction sigIntHandler;
	sigIntHandler.sa_handler = control_c;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	
	sigaction(SIGINT, &sigIntHandler, NULL);
	
	std::string cmd(argv[1]);
	
	if ((cmd == "run" || cmd == "server") && argc >= 4) {
		if (cmd == "run") {
			TiXmlDocument doc_board, doc_moves;

			bool board_loaded = doc_board.LoadFile(argv[2]);
			bool moves_loaded = doc_moves.LoadFile(argv[3]);

			if (!board_loaded) {
				std::cerr << "Error loading board.\n";
			}

			if (!moves_loaded) {
				std::cerr << "Error loading moves.\n";
			}

			if (!(board_loaded && moves_loaded)) {
				return 1;
			}

			Game_parser gp(&std::cerr, std::string(argv[2]));
			Game* g = gp.parse_game(doc_board.FirstChildElement(), doc_moves.FirstChildElement());
			std::ofstream output_file;
			
			output_file.open("ResterendeBewegingen_begin.txt");
			g->write_actions(output_file);
			output_file.close();
			std::ofstream f1;
			f1.open("SaveLevel.xml");
			std::ofstream f2;
			f2.open("SaveActions.xml");
			g->save(f1, f2);
			f1.close();
			f2.close();
			
			g->do_all_actions(std::cout);
			
			output_file.open("HuidigSpeelveld.txt");
			g->get_board()->write_board(output_file);
			output_file.close();
			
			output_file.open("ResterendeBewegingen_einde.txt");
			g->write_actions(output_file);
			output_file.close();
			
			delete g;
		} else { // cmd == "server"
			int port = 8080;
			if (argc > 4) {
				try {
					port = std::stoi(std::string(argv[4]));
				} catch (std::invalid_argument& e) {
					port = 8080;
				}
				port = abs(port);
			}
			GameServer s(argv[2], argv[3], port);
			s.run();
			std::cout << "> Press Enter to stop... \n";
			std::cin.ignore();
		}
		
	} else if (cmd == "exec" && argc == 3) {
		UI user_interface;
		std::string arg(argv[2]);
		for (auto s: split(arg, ';')) {
			std::cout << "\033[1;38;2;255;0;0;48;2;0;0;0m> " << s << "\033\[m\n";
			user_interface.fancy_command(s);
		}
	} else if (cmd == "ui") {
		UI user_interface;
		user_interface.run();
	} else {
		help();
	}
}

