/*
 * UI.cpp
 *
 *  Created on: 16 Apr 2015
 *      Author: stijn
 */

#include "../UI/UI.h"
//#include "../../src/game/parser/game_parser.h"	TODO FIX THE PARSERS!
#include <string>

UI::UI() {
	std::cout << "\n\nWelcome to the Wonderful ARCADE GAME of Evert and Stijn!\n\n\nThis interactive User Interface is able to do a few simple things:\n\n";
	std::cout << "  *  Read an xml-file for the board\t\t[ type read_board <board_file> ]\n\n";
	std::cout << "  *  Read an xml-file for the actions\t\t[ type read_actions <actions_file> ]\n\n";
	std::cout << "  *  Simulate one or more of the actions\t[ type simulate <amount of moves> ]\tdefault=1\n\n";
	std::cout << "  *  Write the current board to a file\t\t[ type write_board <output_file> ]\n\n";
	std::cout << "  *  Write the rest of the actions to a file\t[ type write_actions <output_file> ]\n\n";
	std::cout << "  *  Print out the simple graphical impression\t[ type show <output_stream> ]\t\tdefault=std::cout\n\n";
	std::cout << "\n\tIf you ever want to see this documentation again please type --help.\n\n";

	bool win = false;
	bool board_loaded = false;
	bool moves_loaded = false;
	bool no_game = true;
	//TiXmlDocument doc_board, doc_moves;
	while (win == false) {
		std::string input;
		std::getline(std::cin, input);
		if (input == "--help") {
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

			if (!board_loaded) {
				std::cerr << "Error loading board.\n";
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

			if (!moves_loaded) {
				std::cerr << "Error loading moves.\n";
			}
			continue;
		}

		if (board_loaded && moves_loaded && no_game) {
			//Game_parser gp(&std::cerr, std::string(board_file));
			//Game g = *gp.parse_game(doc_board.FirstChildElement(), doc_moves.FirstChildElement());
			std::cout << "Parsing and initializing game!\n";
			no_game = false;
		}


		// TODO We must check for each of the functionalities that both XML-docs are already loaded. Evert fixed gij deze error-catching?

		compare_str = "simulate";
		if (!input.compare(0, compare_str.size(), compare_str)) { 		// This line of code returns 0 if the two strings are equal. Therefore the NOT.
			int amount = 1;
			if (input.size() != compare_str.size()) {
				amount = atoi(input.substr(compare_str.size()+1, input.size()).c_str());
				if (amount == 0) amount = 1;
			}
			for (int i = 0; i < amount; i++) {
				//g.do_action;
			}
			continue;
		}


	}
}

void UI::help() {
	std::cout << "\n\nThis is the documentation for this User Interface.\n";
	std::cout << "  *  Read an xml-file for the board\t\t[ type read_board <board_file> ]\n\n";
	std::cout << "  *  Read an xml-file for the actions\t\t[ type read_actions <actions_file> ]\n\n";
	std::cout << "  *  Simulate one or more of the actions\t[ type simulate <amount of moves> ]\tdefault=1\n\n";
	std::cout << "  *  Write the current board to a file\t\t[ type write_board <output_file> ]\n\n";
	std::cout << "  *  Write the rest of the actions to a file\t[ type write_actions <output_file> ]\n\n";
	std::cout << "  *  Print out the simple graphical impression\t[ type show <output_stream> ]\t\tdefault=std::cout\n\n";
	std::cout << "\n\tIf you ever want to see this documentation again please type --help.\n\n";
}

