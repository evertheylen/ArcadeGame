#include "../lib/tinyxml/tinyxml.h"
#include "../lib/gtest/include/gtest/gtest.h"

#include "game/game.h"

#include <iostream>
#include <fstream>
#include <sys/stat.h>

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

class ArcadeGameTest: public ::testing::Test {
protected:
	friend class Game;
	
	virtual void SetUp() {}
	
	virtual void TearDown() {}
	
	// No default constructor for game, sooo
	//Game game;
};


// Literal copy-paste
//#include "tests/filetests.tests"


TEST_F(ArcadeGameTest, GTestTest) {
	EXPECT_TRUE(true);
}

//TEST_F(ArcadeGameTest, ) {
	// Set up tests
//}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
