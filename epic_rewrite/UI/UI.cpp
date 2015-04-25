/*
 * UI.cpp
 *
 *  Created on: 16 Apr 2015
 *      Author: stijn
 */

#include "../UI/UI.h"
//#include "../../src/game/parser/game_parser.h"	TODO FIX THE PARSERS!
#include <fstream>

void UI::run() {
	std::cout << "\nWelcome to the Wonderful ARCADE GAME of Evert and Stijn!";
	help();

	bool win = false;
	bool board_loaded = false;
	bool moves_loaded = false;
	bool parsed = false;
	Game g;
	//TiXmlDocument doc_board, doc_moves;
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
			//board_loaded = doc_board.LoadFile(board_file);
			std::cout << "Reading board, automatically setting board_loaded = true\n";
			board_loaded = true;
			if (!board_loaded) {
				std::cerr << "Error loading board.\n";
			}
			if (board_loaded && moves_loaded && !parsed) {
				//Game_parser gp(&std::cerr, std::string(board_file));
				//Game g = *gp.parse_game(doc_board.FirstChildElement(), doc_moves.FirstChildElement());
				std::cout << "Parsing and initializing game!\n";
				parsed = true;
			}
			continue;
		}

		compare_str = "read_actions";
		if (!input.compare(0, compare_str.size(), compare_str)) {       // This line of code returns 0 if the two strings are equal. Therefore the NOT.
			if (input.size() <= compare_str.size()+1) {
				std::cout << "Please input an xml-file\n";
				continue;
			}
			const char* file = input.substr(compare_str.size()+1, input.size()).c_str();
			//moves_loaded = doc_moves.LoadFile(file);
			std::cout << "Reading moves, automatically setting moves_loaded = true\n";
			moves_loaded = true;
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
			//Game_parser gp(&std::cerr, std::string(board_file));
			//Game g = *gp.parse_game(doc_board.FirstChildElement(), doc_moves.FirstChildElement());
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
				do_action(amount);
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
				show(std::cout);
				continue;
			}
			std::ofstream stream;
			stream.open(input.substr(compare_str.size()+1, input.size()).c_str());
			show(stream);
			stream.close();
			continue;
		}
	}
}

void UI::show(std::ostream& out) {
	out << "Showing the board!\n";
	//out << g << std::endl;
}

void UI::write_board(std::string file, Game& g) {
	std::ofstream output_file;
	output_file.open(file.c_str());
	output_file << "Hier verschijnt later het huidige speelveld!\n";
	//g.writeBoard(output_file);
	output_file.close();
}

void UI::write_actions(std::string file, Game& g) {
	std::ofstream output_file;
	output_file.open(file.c_str());
	output_file << "Hier verschijnen later de resterende bewegingen!\n";
	//g.writeActions(output_file);
	output_file.close();
}

void UI::do_action(int amount) {
	for (int i = 0; i < amount; i++) {
		std::cout << "Doing an action\n";
		//g.do_action;
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

