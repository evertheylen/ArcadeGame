
#include "../game/board/thing.h"
#include <sstream>

TEST(Thing, EmptyInit) {
	Thing t = Thing();
	EXPECT_TRUE(t.properlyInitialized());
}

TEST(Thing, NotProperlyInitialized) {
	char a[sizeof(Thing)] {'a'};
	EXPECT_FALSE(((Thing*) &a)->properlyInitialized());
}

TEST(Thing, Init) {
	Thing t = Thing(4,8,12);
	EXPECT_EQ(t.get_x(), 4);
	EXPECT_EQ(t.get_y(), 8);
	EXPECT_EQ(t.get_weight(), 12);
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
	EXPECT_EQ(ss.str(), "Thing\n");
}

TEST(Thing, ToChar) {
	Thing t = Thing(4,8,1);
	EXPECT_EQ(t.to_char(), 'T');
}

TEST(Thing, Setters) {
	Thing t = Thing(50,50,120);
	t.set_x(4);
	t.set_y(8);
	t.set_weight(12);
	EXPECT_EQ(t.get_x(), 4);
	EXPECT_EQ(t.get_y(), 8);
	EXPECT_EQ(t.get_weight(), 12);
	EXPECT_TRUE(t.properlyInitialized());
}

TEST(Thing, CopyConstructor) {
	Thing tt = Thing(4,8,12);
	Thing t = tt;
	EXPECT_EQ(t.get_x(), 4);
	EXPECT_EQ(t.get_y(), 8);
	EXPECT_EQ(t.get_weight(), 12);
	EXPECT_TRUE(t.properlyInitialized());
}

TEST(Thing, CopyAssignment) {
	Thing tt = Thing(4,8,12);
	Thing t = Thing(80,1,-5);
	t = tt;
	EXPECT_EQ(t.get_x(), 4);
	EXPECT_EQ(t.get_y(), 8);
	EXPECT_EQ(t.get_weight(), 12);
	EXPECT_TRUE(t.properlyInitialized());
}
