
#include "../game/board/obstacle.h"
#include <sstream>

TEST(Obstacle, NotProperlyInitialized) {
	char a[sizeof(Obstacle)] {'a'};
	EXPECT_FALSE(((Obstacle*) &a)->properlyInitialized());
}

TEST(Obstacle, Init) {
	Obstacle t = Obstacle(4,8,12);
	EXPECT_EQ(t.get_x(), 4);
	EXPECT_EQ(t.get_y(), 8);
	EXPECT_EQ(t.get_weight(), 12);
	EXPECT_TRUE(t.properlyInitialized());
}

TEST(Obstacle, NotMovable) {
	Obstacle t = Obstacle(4,8,-1);
	EXPECT_FALSE(t.is_movable());
}

TEST(Obstacle, Movable) {
	Obstacle t = Obstacle(4,8,1);
	EXPECT_TRUE(t.is_movable());
}

TEST(Obstacle, Print) {
	Obstacle t = Obstacle(4,8,1);
	std::stringstream ss;
	ss << t;
	EXPECT_EQ(ss.str(), "Obstacle\n");
}

TEST(Obstacle, ToChar) {
	Obstacle t = Obstacle(4,8,1);
	EXPECT_EQ(t.to_char(), 'O');
}

TEST(Obstacle, CopyConstructor) {
	Obstacle tt = Obstacle(4,8,12);
	Obstacle t = tt;
	EXPECT_EQ(t.get_x(), 4);
	EXPECT_EQ(t.get_y(), 8);
	EXPECT_EQ(t.get_weight(), 12);
	EXPECT_TRUE(t.properlyInitialized());
}

TEST(Obstacle, CopyAssignment) {
	Obstacle tt = Obstacle(4,8,12);
	Obstacle t = Obstacle(80,1,0);
	t = tt;
	EXPECT_EQ(t.get_x(), 4);
	EXPECT_EQ(t.get_y(), 8);
	EXPECT_EQ(t.get_weight(), 12);
	EXPECT_TRUE(t.properlyInitialized());
}
