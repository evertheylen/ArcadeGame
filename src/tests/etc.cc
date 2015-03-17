
// fileCompare

TEST(fileCompare, Equality) {
	EXPECT_TRUE(fileCompare("tests/filecompare_tests/equal_a", "tests/filecompare_tests/equal_b"));
}

TEST(fileCompare, Inequality) {
	EXPECT_FALSE(fileCompare("tests/filecompare_tests/equal_a", "tests/filecompare_tests/almost_equal_b"));
}

TEST(fileCompare, Emptiness) {
	EXPECT_TRUE(fileCompare("tests/filecompare_tests/empty_a", "tests/filecompare_tests/empty_b"));
}


TEST(fileCompare, EOL) {
	EXPECT_FALSE(fileCompare("tests/filecompare_tests/diff_on_end_a", "tests/filecompare_tests/diff_on_end_b"));
}


TEST(fileCompare, OneChar) {
	EXPECT_FALSE(fileCompare("tests/filecompare_tests/onechar_a", "tests/filecompare_tests/onechar_b"));
}
