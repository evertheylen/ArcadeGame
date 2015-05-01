/*
 * UI.cpp
 *
 *  Created on: 16 Apr 2015
 *      Author: stijn
 */

#include "../UI/UI.h"
#include "../parsers/game_parser.h"
#include "../parsers/action_parser.h"
#include <fstream>
#include <sstream>
#include <string>

#include <readline/readline.h>
#include <readline/history.h>

UI::UI():
		g(nullptr) {
	reset();
}

void UI::reset() {
	board_loaded = false;
	actions_loaded = false;
	parsed = false;
	if (g != nullptr) {
		delete g;
		g = nullptr;
	}
	doc_board.Clear();
	reparse_board = true;
	doc_actions.Clear();
	reparse_actions = true;
}

void UI::run() {	
	std::cout << "\nWelcome to the Wonderful ARCADE GAME of Evert and Stijn!";
	help();
	
	while (true) {
		std::string raw_input(readline("\033[1;38;2;255;0;0;48;2;0;0;0m> "));
		std::cout << "\033[m";
		
		if (raw_input == "quit" || raw_input == "q") {
			return;
		} else {
			fancy_command(raw_input);
		}
	}
}

void UI::fancy_command(std::string& command) {
	std::vector<std::string> fancies = split(command, ':');
	int times = 0;
	if (fancies.size() == 2) {
		try {
			times = std::stoi(fancies[0]);
		} catch (std::invalid_argument& e) {
			// too bad
			times = -1;
		}
	} else if (fancies.size() == 1) {
		if (!parse_and_do(fancies[0])) {
			std::cout << "I didn't understand that command. Try help.\n";
		}
		return;
	}
	
	if (times > 0) {
		for (int i=0; i<times; i++) {
			for (std::string subcommand: split(fancies[1], ',')) {
				std::cout << "\033[1;38;2;255;0;0;48;2;0;0;0m>> " << i << ": " << subcommand << "\033\[m\n";
				if (!parse_and_do(subcommand)) {
					std::cout << "I didn't understand that command. Try help.\n";
				}
			}
		}
	} else {
		std::cout << "I didn't understand that command. Try help.\n";
	}
}

bool UI::parse_and_do(std::string& command) {
	std::vector<std::string> input = split(command, ' ');
	
	if (input.size() < 1) {
		//continue;
	} else if (input[0] == "help") {
		help();
		
	} else if (input[0] == "read_board") {
		std::string filename = input.size() >= 2 ? input[1] : "Level3.xml";
		read_board(filename);
		init_game();
		
	} else if (input[0] == "read_actions") {
		std::string filename = input.size() >= 2 ? input[1] : "Level3Acties.xml";
		read_actions(filename);
		init_game();
		
	} else if (input[0] == "simulate") {
		if (init_game()) {
			int times = input.size() >= 2 ? std::stoi(input[1]) : 1;
			simulate(times);
		} else {
			std::cout << "Game not initialized yet\n";
		}
		
	} else if (input[0] == "write_board") {
		std::string filename = input.size() >= 2 ? input[1] : "HuidigSpeelveld.txt";
		if (filename == "cout") {
			write_board(std::cout);
		} else {
			std::ofstream output_file;
			output_file.open(filename);
			write_board(output_file);
		}
		
	} else if (input[0] == "write_actions") {
		std::string filename = input.size() >= 2 ? input[1] : "HuidigSpeelveld.txt";
		if (filename == "cout") {
			write_actions(std::cout);
		} else {
			std::ofstream output_file;
			output_file.open(filename);
			write_actions(output_file);
		}
		
	} else if (input[0] == "show") {
		show(std::cout);
	
	} else if (input[0] == "") {
		// silently ignore empty commands
	} else {
		// Don't know that command
		return false;
	}
	return true;
}

void UI::help() {
	std::cout << "\nThis interactive User Interface is able to do a few simple things:\n";
	std::cout << "  * Read an xml-file for the board\t\t[ read_board <board_file> ]\n";
	std::cout << "  * Read an xml-file for the actions\t\t[ read_actions <actions_file> ]\n";
	std::cout << "  * Simulate one or more of the actions\t\t[ simulate <amount of moves> ]\tdefault=1\n";
	std::cout << "  * Write the current board to a file\t\t[ write_board <output_file> ]\tdefault=HuidigSpeelveld.txt\n";
	std::cout << "  * Write the rest of the actions to a file\t[ write_actions <output_file> ]\tdefault=ResterendeBewegingen.txt\n";
	std::cout << "  * Print out the simple graphical impression\t[ show ]\n";
	std::cout << "\n\tIf you ever want to see this documentation again please type help.\n";
}

void UI::read_board(std::string& filename) {
	if (board_loaded) {
		std::cout << "Overriding old board.\n";
		doc_board.Clear();
	}
	
	board_loaded = doc_board.LoadFile(filename);
	if (!board_loaded) {
		std::cout << "Something went wrong when loading board.\n";
	} else {
		reparse_board = true;
	}
}

void UI::read_actions(std::string& filename) {
	if (actions_loaded) {
		std::cout << "Overriding old actions.\n";
		doc_actions.Clear();
	}
	
	actions_loaded = doc_actions.LoadFile(filename);
	if (!actions_loaded) {
		std::cout << "Something went wrong when loading actions.\n";
	} else {
		reparse_actions = true;
	}
}

void UI::write_board(std::ostream& out) {
	if (init_game()) {
		g->board.write_board(out);
	} else {
		std::cout << "Game isn't initialized yet.\n";
	}
}

void UI::write_actions(std::ostream& out) {
	if (init_game() && actions_loaded) {
		g->write_actions(out);
	} else {
		std::cout << "Game and actions aren't initialized yet.\n";
	}
}

void UI::show(std::ostream& out) {
	if (init_game()) {
		g->board.simple_graphics(out);
	} else {
		std::cout << "Can't show, Game isn't initialized yet.\n";
	}
}

void UI::simulate(int amount) {
	if (init_game()) {
		for (int i = 0; i < amount; i++) {
			if (g->actions.size() >= 1) {
				g->actions.front()->execute(g);
				g->actions.pop_front();
			}
		}
	} else {
		std::cout << "Can't simulate, Game isn't initialized yet.\n";
	}
}

bool UI::init_game() {
	bool validGame = true;
	
	if (g == nullptr) {
		reparse_actions = true;
		reparse_board = true;
		validGame = false;
	}
	
	try {
		if (board_loaded && reparse_board) {
			// Parse the board, init game
			Game_parser gp(&std::cout);
			TiXmlElement* root = doc_board.RootElement();
			g = gp.parse_game(root);
			validGame = true;
			std::cout << "Parsed game.\n";
			reparse_board = false;
		}
		
		if (actions_loaded && reparse_actions && g!=nullptr) {
			Action_parser ap(&std::cout, "unspecified");
			TiXmlElement* root = doc_actions.RootElement();
			std::list<Action*>* actions = ap.parse_action(root, g);
			g->actions = *actions;
			reparse_actions = false;
		}
	} catch (ParseError& e) {
		std::cout << "Error while parsing in init_game: " << e.what() << "\n";
		return false;
	}
	
	return validGame;
}

// Extra

std::vector<std::string> split(std::string& s, char delim) {
	std::vector<std::string> v;
	int start = 0;
	int end = 0;
	for (; end<s.size(); end++) {
		if (s.at(end) == delim) {
			v.push_back(s.substr(start, end-start));
			start = end+1;
		}
	}
	
	if (start != end) {
		v.push_back(s.substr(start, end-start));
	}
	
	return v;
}
