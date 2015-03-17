
#include "../game/board/wall.h"
#include <sstream>

TEST(Wall, NotProperlyInitialized) {
	char a[sizeof(Wall)] {'a'};
	EXPECT_FALSE(((Wall*) &a)->properlyInitialized());
}

TEST(Wall, Init) {
	Wall t = Wall(4,8);
	EXPECT_EQ(t.get_x(), 4);
	EXPECT_EQ(t.get_y(), 8);
	EXPECT_EQ(t.get_weight(), -1);
	EXPECT_TRUE(t.properlyInitialized());
}

TEST(Wall, NotMovable) {
	Wall t = Wall(4,8);
	EXPECT_FALSE(t.is_movable());
}


TEST(Wall, Print) {
	Wall t = Wall(4,8);
	std::stringstream ss;
	ss << t;
	EXPECT_EQ(ss.str(), "Wall\n");
}

TEST(Wall, ToChar) {
	Wall t = Wall(4,8);
	EXPECT_EQ(t.to_char(), 'X');
}

TEST(Wall, CopyConstructor) {
	Wall tt = Wall(4,8);
	Wall t = tt;
	EXPECT_EQ(t.get_x(), 4);
	EXPECT_EQ(t.get_y(), 8);
	EXPECT_TRUE(t.properlyInitialized());
}

TEST(Wall, CopyAssignment) {
	Wall tt = Wall(4,8);
	Wall t = Wall(80,1);
	t = tt;
	EXPECT_EQ(t.get_x(), 4);
	EXPECT_EQ(t.get_y(), 8);
	EXPECT_TRUE(t.properlyInitialized());
}
