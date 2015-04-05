#include "../lib/tinyxml/tinyxml.h"
#include "game/game.h"
#include "game/parser/game_parser.h"
#include <iostream>
#include <streambuf>
#include <fstream>
#include <cstring>

// http://stackoverflow.com/questions/11826554/standard-no-op-output-stream
class NullBuffer : public std::streambuf {
public: int overflow(int c) { return c; }
};

class NullStream : public std::ostream { 
	public: NullStream(): std::ostream(&m_sb) {}
	private: NullBuffer m_sb;
};

int main(int argc, char const* argv[]) {
	TiXmlDocument doc_board, doc_moves;

	if(argc <= 2) {
		std::cerr << "Not enough arguments given.\n";
		return 1;
	}

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
	Game g = *gp.parse_game(doc_board.FirstChildElement(), doc_moves.FirstChildElement());
	
	//Game g = Game(doc_board, doc_moves, std::cout);
	
	if (argc == 4) {
		// Different modes
		if (strcmp("show", argv[3]) == 0) {
			// print the board and stop.
			NullStream null;
			g.writeBoard(std::cout);
			std::cout << "\n\n---------------------------------\n\n";
			g.doAllMoves(std::cout);
			std::cout << "\n\n---------------------------------\n\n";
			g.writeBoard(std::cout);
		} else {
			std::cout << "Couldn't recognize mode '" << argv[3] << "'.\n";
		}
	} else {
		// default
		
		std::ofstream output_file;
		
		output_file.open("ResterendeBewegingen_begin.txt");
		g.writeMovements(output_file);
		output_file.close();
		
		g.doAllMoves(std::cout);
		
		output_file.open("HuidigSpeelveld.txt");
		g.writeBoard(output_file);
		output_file.close();
		
		output_file.open("ResterendeBewegingen_einde.txt");
		g.writeMovements(output_file);
		output_file.close();
	}
}
