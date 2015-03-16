#include "../lib/tinyxml/tinyxml.h"
#include "../lib/gtest/include/gtest/gtest.h"

#include "game/game.h"

#include <iostream>
#include <fstream>
#include <sys/stat.h>

// http://stackoverflow.com/questions/11826554/standard-no-op-output-stream
class NullBuffer : public std::streambuf {
	public: int overflow(int c) { return c; }
};

class NullStream : public std::ostream { 
	public: NullStream(): std::ostream(&m_sb) {}
	private: NullBuffer m_sb;
} null; // used when a ostream is needed



bool DirectoryExists(const char *dirname) {
	struct stat st;
	return stat(dirname, &st) == 0;
}

/**
Auxiliary function for file manipulation in unit tests.
*/
bool fileCompare(std::string leftFileName, std::string rightFileName) {
	std::ifstream leftFile, rightFile;
	char leftRead, rightRead;
	bool result;

	// Open the two files.
	leftFile.open(leftFileName);
	if (!leftFile.is_open()) {
		return false;
	};
	rightFile.open(rightFileName);
	if (!rightFile.is_open()) {
		leftFile.close();
		return false;
	};

	result = true; // files exist and are open; assume equality unless a counterexamples shows up.
	while (result && leftFile.good() && rightFile.good()) {
		leftFile.get(leftRead);
		rightFile.get(rightRead);
		result = (leftRead == rightRead);
	};
	if (result) {
		// last read was still equal; are we at the end of both files ?
		result = (!leftFile.good()) && (!rightFile.good());
	};

	leftFile.close();
	rightFile.close();
	return result;
}

// ----[ Game ]-------------------------------------

// class ArcadeGameTest: public ::testing::Test {
// protected:
// 	friend class Game;
// 	
// 	virtual void SetUp() {}
// 	
// 	virtual void TearDown() {}
// 	
// 	// No default constructor for game, sooo
// 	//Game game;
// };


// Literal copy-paste
#include "tests/filetests.tests"

#include "tests/Thing.cc"
#include "tests/Obstacle.cc"
#include "tests/Wall.cc"
#include "tests/Barrel.cc"
#include "tests/Player.cc"
#include "tests/Game.cc"
#include "tests/Board.cc"
#include "tests/Movement.cc"

TEST(ArcadeGameTest, GTestTest) {
	EXPECT_TRUE(true);
}



int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
