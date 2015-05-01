/*
 * UI.cpp
 *
 *  Created on: 16 Apr 2015
 *      Author: stijn
 */

#include "../UI/UI.h"
#include "../parsers/game_parser.h"
#include <fstream>
#include <sstream>
#include <string>

void UI::run() {
	std::cout << "\nWelcome to the Wonderful ARCADE GAME of Evert and Stijn!";
	help();

	bool win = false;
	bool board_loaded = false;
	bool moves_loaded = false;
	bool parsed = false;
	Game* g;
	TiXmlDocument doc_board, doc_moves;
	while (true) {
		std::string input;
		std::getline(std::cin, input);
		if (input == "help") {
			help();
			continue;
		}

		std::string compare_str = "read_board";
		const char* board_file;
		if (!input.compare(0, compare_str.size(), compare_str)) {       // This line of code returns 0 if the two strings are equal. Therefore the NOT.
			if (input.size() <= compare_str.size()+1) {
				std::cout << "Please input an xml-file\n";
				continue;
			}
			board_file = input.substr(compare_str.size()+1, input.size()).c_str();
			std::cout << " [Loading] " << board_file << std::endl;
			board_loaded = doc_board.LoadFile(board_file);
			//std::cout << "Reading board, automatically setting board_loaded = true\n";
			if (!board_loaded) {
				std::cerr << "Error loading board.\n";
			}
			if (board_loaded && moves_loaded && !parsed) {
				//Game_parser gp(&std::cerr, std::string(board_file));
				//Game g = *gp.parse_game(doc_board.FirstChildElement(), doc_moves.FirstChildElement());
				std::cout << "Parsing and initializing game!\n";
				parsed = true;
			}
			doc_board.LoadFile("Level3.xml");
			doc_moves.LoadFile("Level3Acties.xml");
			Game_parser gp(&std::cerr, std::string(board_file));
			g = gp.parse_game(doc_board.FirstChildElement(), doc_moves.FirstChildElement());
			parsed = true;
			continue;
		}

		compare_str = "read_actions";
		if (!input.compare(0, compare_str.size(), compare_str)) {       // This line of code returns 0 if the two strings are equal. Therefore the NOT.
			if (input.size() <= compare_str.size()+1) {
				std::cout << "Please input an xml-file\n";
				continue;
			}
			const char* file = input.substr(compare_str.size()+1, input.size()).c_str();
			std::cout << " [Loading] " << file << std::endl;
			//moves_loaded = doc_moves.LoadFile(file);
			//std::cout << "Reading moves, automatically setting moves_loaded = true\n";
			if (!moves_loaded) {
				std::cerr << "Error loading moves.\n";
			}
			if (board_loaded && moves_loaded && !parsed) {
				//Game_parser gp(&std::cerr, std::string(board_file));
				//Game g = *gp.parse_game(doc_board.FirstChildElement(), doc_moves.FirstChildElement());
				std::cout << "Parsing and initializing game!\n";
				parsed = true;
			}
			continue;
		}

		if (board_loaded && moves_loaded && !parsed) {
			Game_parser gp(&std::cerr, std::string(board_file));
			g = gp.parse_game(doc_board.FirstChildElement(), doc_moves.FirstChildElement());
			std::cout << "Parsing and initializing game!\n";
			parsed = true;
		}


		// TODO We must check for each of the functionalities that both XML-docs are already loaded. Evert fixed gij deze error-catching?

		compare_str = "simulate";
		if (!input.compare(0, compare_str.size(), compare_str)) { 		// This line of code returns 0 if the two strings are equal. Therefore the NOT.
			int amount = 1;
			if (input.size() != compare_str.size()) {
				amount = atoi(input.substr(compare_str.size()+1, input.size()).c_str());
				if (amount == 0) amount = 1;
			}
			if (parsed) {
				do_action(g, amount);
				continue;
			} else {
				std::cout << "Game is not initialized or parsed!\n";
				continue;
			}
		}

		compare_str = "write_board";
		if (!input.compare(0, compare_str.size(), compare_str)) {
			if (!parsed) {
				std::cout << "Game is not initialized or parsed!\n";
				continue;
			}
			if (input.size() <= compare_str.size()+1) {
				write_board("HuidigSpeelveld.txt", g);
				continue;
			}
			std::string file = input.substr(compare_str.size()+1, input.size()).c_str();
			write_board(file, g);
			continue;
		}

		compare_str = "write_actions";
		if (!input.compare(0, compare_str.size(), compare_str)) {
			if (!parsed) {
				std::cout << "Game is not initialized or parsed!\n";
				continue;
			}
			if (input.size() <= compare_str.size()+1) {
				write_board("ResterendeBewegingen.txt", g);
				continue;
			}
			std::string file = input.substr(compare_str.size()+1, input.size()).c_str();
			write_actions(file, g);
			continue;
		}

		compare_str = "show";
		if (!input.compare(0, compare_str.size(), compare_str)) {
			if (!parsed) {
				std::cout << "Game is not initialized or parsed!\n";
				continue;
			}
			if (input.size() <= compare_str.size()+1) {
				show(std::cout, g);
				continue;
			}
			std::ofstream stream;
			stream.open(input.substr(compare_str.size()+1, input.size()).c_str());
			show(stream, g);
			stream.close();
			continue;
		}
	}
}

void UI::show(std::ostream& out, Game* g) {
	g->board.simple_graphics(out);
}

void UI::write_board(std::string file, Game* g) {
	std::ofstream output_file;
	output_file.open(file.c_str());
	g->board.write_board(output_file);
	output_file.close();
}

void UI::write_actions(std::string file, Game* g) {
	std::ofstream output_file;
	output_file.open(file.c_str());
	g->write_actions(output_file);
	output_file.close();
}

void UI::do_action(Game* g, int amount) {
	std::stringstream ss;
	std::string str;
	for (int i = 0; i < amount; i++) {
		std::cout << "Doing an action\n";

		ss << i << ".stijn-evert";
		str = ss.str();
		ss.str("");
		std::ofstream file;
		file.open(str);
		show(file, g);
		file.close();
		g->actions.front()->execute(g);
		g->actions.pop_front();
	}
}

void UI::help() {
	std::cout << "\nThis interactive User Interface is able to do a few simple things:\n";
	std::cout << "  * Read an xml-file for the board\t\t[ read_board <board_file> ]\n";
	std::cout << "  * Read an xml-file for the actions\t\t[ read_actions <actions_file> ]\n";
	std::cout << "  * Simulate one or more of the actions\t\t[ simulate <amount of moves> ]\tdefault=1\n";
	std::cout << "  * Write the current board to a file\t\t[ write_board <output_file> ]\tdefault=HuidigSpeelveld.txt\n";
	std::cout << "  * Write the rest of the actions to a file\t[ write_actions <output_file> ]\tdefault=ResterendeBewegingen.txt\n";
	std::cout << "  * Print out the simple graphical impression\t[ show <output_stream> ]\tdefault=std::cout\n";
	std::cout << "\n\tIf you ever want to see this documentation again please type help.\n";
}

