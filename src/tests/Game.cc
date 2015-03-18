
#include "../game/game.h"
#include <iostream>


// First some tests like filetests, but different.
// Proper loading (and error handling) of an xml file is already tested in the normal filetests,
// but when the xml-file is broken enough so that Game can't initialize, we need to the test
// that apart.

TEST(ArcadeGameTest, BadInit_Board) {
	#define Base std::string("tests/filetests_alt/BadInit_Board/")

	TiXmlDocument doc_board, doc_moves;

	bool board_loaded = doc_board.LoadFile((Base + "Speelveld.xml").c_str());
	bool moves_loaded = doc_moves.LoadFile((Base + "Bewegingen.xml").c_str());

	ASSERT_TRUE(board_loaded && moves_loaded) << "Failed to load xml files.";
	
	std::ofstream new_cout;
	new_cout.open(Base+"output.txt");
	
	Game g = Game(doc_board, doc_moves, new_cout);
	
	EXPECT_FALSE(g.properlyInitialized());
	
	new_cout.close();
	
	EXPECT_TRUE(fileCompare(Base+"output.txt", Base+"_output.txt"));
}


// Other tests

// There are a lot of tests already using writeBoard and writeMovements. (filetests)
// If they ever break, we'll know about it.

// Example has 3 moves, and a basic 10x10 playing field.
class ExampleGame: public ::testing::Test {
protected:
	friend class Game;
	
	virtual void SetUp() {
		#define Base std::string("tests/filetests_alt/ExampleGame/")

		TiXmlDocument doc_board, doc_moves;

		bool board_loaded = doc_board.LoadFile((Base + "Speelveld.xml").c_str());
		bool moves_loaded = doc_moves.LoadFile((Base + "Bewegingen.xml").c_str());

		ASSERT_TRUE(board_loaded && moves_loaded) << "Failed to load xml files.";
		
		game = new Game(doc_board, doc_moves, null);
		
		ASSERT_TRUE(game->properlyInitialized());
	}
	
	virtual void TearDown() {
		delete(game);
	}
	
	// No default constructor for game, sooo
	Game* game;
};


TEST_F(ExampleGame, popMove) {
	int original_size = game->get_movements().size();
	game->popMove(null);
	EXPECT_EQ(game->get_movements().size(), original_size-1);
}


TEST_F(ExampleGame, popMoveEmpty) {
	int original_size = game->get_movements().size();
	game->popMove(null); // 2 moves left
	game->popMove(null); // 1 move left
	game->popMove(null); // 0 moves left
	game->popMove(null); // 0 moves left
	EXPECT_DEATH(game->popMove(null), "");
}


TEST_F(ExampleGame, doMove) {
	auto move = game->get_movements().back();
	int orig_x = move.get_player()->get_x();
	int orig_y = move.get_player()->get_y();
	game->doMove(move, null);
	int x = move.get_player()->get_x();
	int y = move.get_player()->get_y(); 
	EXPECT_TRUE(x != orig_x || y != orig_y);
}


TEST_F(ExampleGame, doAllMoves) {
	game->doAllMoves(null);
	EXPECT_TRUE(game->get_movements().empty());
}


TEST_F(ExampleGame, CopyConstructor) {
	Game game2 = *game;
	ASSERT_TRUE(game2.properlyInitialized());
}


TEST_F(ExampleGame, CopyAssignment) {
	// When assigning by copy, only the width, height and name of the other
	// Game (or underlying board) are copied. The rest is simply emptied.

	#define Base std::string("tests/filetests_alt/ExampleGame2/")

	TiXmlDocument doc_board, doc_moves;

	bool board_loaded = doc_board.LoadFile((Base + "Speelveld.xml").c_str());
	bool moves_loaded = doc_moves.LoadFile((Base + "Bewegingen.xml").c_str());

	ASSERT_TRUE(board_loaded && moves_loaded) << "Failed to load xml files.";
	
	Game game2 = Game(doc_board, doc_moves, null);
	
	ASSERT_TRUE(game2.properlyInitialized());
	
	// Write current files
	
	std::ofstream output_file;
	
	output_file.open(Base+"ResterendeBewegingen_begin.txt");
	game2.writeMovements(output_file);
	output_file.close();
	
	output_file.open(Base+"HuidigSpeelveld.txt");
	game2.writeBoard(output_file);
	output_file.close();
	
	// Compare with selfmade files, should be equal.
	EXPECT_TRUE(fileCompare(Base+"ResterendeBewegingen_begin.txt", Base+"_ResterendeBewegingen_begin.txt"));
	EXPECT_TRUE(fileCompare(Base+"HuidigSpeelveld.txt", Base+"_HuidigSpeelveld.txt"));

	// Now copy
	game2 = *game;
	
	// Write new files
	output_file.open(Base+"ResterendeBewegingen_begin_copied.txt");
	game2.writeMovements(output_file);
	output_file.close();
	
	output_file.open(Base+"HuidigSpeelveld_copied.txt");
	game2.writeBoard(output_file);
	output_file.close();

	// Check again, movements should be empty, and board should be empty too, but have the same dimensions
	EXPECT_TRUE(fileCompare(Base+"ResterendeBewegingen_begin_copied.txt", Base+"_ResterendeBewegingen_begin_copied.txt"));
	EXPECT_TRUE(fileCompare(Base+"HuidigSpeelveld_copied.txt", Base+"_HuidigSpeelveld_copied.txt"));
}

