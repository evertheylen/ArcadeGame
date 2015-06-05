//#include "./lib/tinyxml/tinyxml.h"
#include "gtest/gtest.h"

#include "game.h"
#include "../parsers/game_parser.h"

#include <iostream>
#include <fstream>
#include <sys/stat.h>

#include "../lib/tinyxml/tinyxml.h"


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
	}
	rightFile.open(rightFileName);
	if (!rightFile.is_open()) {
		leftFile.close();
		return false;
	}
	result = true; // files exist and are open; assume equality unless a counterexamples shows up.
	while (result && leftFile.good() && rightFile.good()) {
		leftFile.get(leftRead);
		rightFile.get(rightRead);
		
		if (leftFile.eof() && rightFile.eof()) {
			break;
		}
		if (leftFile.eof() || rightFile.eof()) {
			result = false;
			break;
		}
		
		result = (leftRead == rightRead);
	}
	
	if (result) {
		// last read was still equal; are we at the end of both files ?
		result = (!leftFile.good()) && (!rightFile.good());
	}
	
	leftFile.close();
	rightFile.close();
	return result;
}


TEST(Meta, GTestTest) {
	EXPECT_TRUE(true);
	EXPECT_EQ(45, 45);
	EXPECT_FALSE(false);
}

#include "tests/filetests.tests"
#include "tests/errors.tests"
#include "tests/etc.cpp"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	// Get rid of the irritating threading warning when testing DEATH
	::testing::FLAGS_gtest_death_test_style = "threadsafe";
	return RUN_ALL_TESTS();
}
