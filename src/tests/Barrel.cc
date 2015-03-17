
#include "../game/board/barrel.h"
#include <sstream>
#include <cstdlib>

TEST(Barrel, NotProperlyInitialized) {
	//char* a = new char;
	char a[sizeof(Barrel)] {'a'};
	EXPECT_FALSE(((Barrel*) &a)->properlyInitialized());
}

TEST(Barrel, Init) {
	Barrel t = Barrel(4,8);
	EXPECT_EQ(t.get_x(), 4);
	EXPECT_EQ(t.get_y(), 8);
	EXPECT_EQ(t.get_weight(), 1000);  // NOTE change this when needed!
	EXPECT_TRUE(t.properlyInitialized());
}

TEST(Barrel, NotMovable) {
	Barrel t = Barrel(4,8);
	EXPECT_TRUE(t.is_movable());
}


TEST(Barrel, Print) {
	Barrel t = Barrel(4,8);
	std::stringstream ss;
	ss << t;
	EXPECT_EQ(ss.str(), "Er bevindt zich een ton op positie (4,8).");
}

TEST(Barrel, ToChar) {
	Barrel t = Barrel(4,8);
	EXPECT_EQ(t.to_char(), 'o');
}

TEST(Barrel, CopyConstructor) {
	Barrel tt = Barrel(4,8);
	Barrel t = tt;
	EXPECT_EQ(t.get_x(), 4);
	EXPECT_EQ(t.get_y(), 8);
	EXPECT_TRUE(t.properlyInitialized());
}

TEST(Barrel, CopyAssignment) {
	Barrel tt = Barrel(4,8);
	Barrel t = Barrel(80,1);
	t = tt;
	EXPECT_EQ(t.get_x(), 4);
	EXPECT_EQ(t.get_y(), 8);
	EXPECT_TRUE(t.properlyInitialized());
}
