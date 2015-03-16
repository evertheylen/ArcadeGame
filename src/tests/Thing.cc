
#include "../game/board/thing.h"
#include <sstream>

TEST(Thing, EmptyInit) {
	Thing t = Thing();
	EXPECT_TRUE(t.properlyInitialized());
}

TEST(Thing, NotProperlyInitialized) {
	char* a = new char;
	EXPECT_FALSE(((Thing*) a)->properlyInitialized());
}

TEST(Thing, Init) {
	Thing t = Thing(4,8,12);
	EXPECT_TRUE(t.get_x() == 4);
	EXPECT_TRUE(t.get_y() == 8);
	EXPECT_TRUE(t.get_weight() == 12);
	EXPECT_TRUE(t.properlyInitialized());
}

TEST(Thing, NotMovable) {
	Thing t = Thing(4,8,-1);
	EXPECT_FALSE(t.is_movable());
}

TEST(Thing, Movable) {
	Thing t = Thing(4,8,1);
	EXPECT_TRUE(t.is_movable());
}

TEST(Thing, Print) {
	Thing t = Thing(4,8,1);
	std::stringstream ss;
	ss << t;
	EXPECT_TRUE(ss.str() == "Thing\n");
}

TEST(Thing, ToChar) {
	Thing t = Thing(4,8,1);
	EXPECT_TRUE(t.to_char() == 'T');
}
