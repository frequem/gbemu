#include <iostream>
#include <gtest/gtest.h>

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(ExampleTest, example1){
	EXPECT_EQ(1, 1);
}

TEST(ExampleTest, example2){
	EXPECT_EQ(2, 2);
}
