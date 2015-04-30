//#include "./lib/tinyxml/tinyxml.h"
#include "gtest/gtest.h"

#include "game.h"

#include <iostream>
#include <fstream>
#include <sys/stat.h>

TEST(Meta, GTestTest) {
	EXPECT_TRUE(true);
	EXPECT_EQ(45, 45);
	EXPECT_FALSE(false);
}

#include "tests/filetests.tests"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	// Get rid of the irritating threading warning when testing DEATH
	::testing::FLAGS_gtest_death_test_style = "threadsafe";
	return RUN_ALL_TESTS();
}
