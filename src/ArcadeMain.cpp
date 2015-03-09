#include "lib/tinyxml.h"
#include "game/game.h"
#include <iostream>
#include <fstream>

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
	
	Game g = Game(doc_board, doc_moves);
	g.doAllMoves();
	std::ofstream output_file;
	output_file.open("HuidigSpeelveld.txt");
	g.writeBoard(output_file);
	output_file.close();
	output_file.open("ResterendeBewegingen.txt");
	g.writeMovements(output_file);
	output_file.close();
	
	std::cout << "\n\nblablabla\n\n";
}
