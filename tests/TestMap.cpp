#include <gtest/gtest.h>
#include <string>

#include "../Map.h"

TEST(Map, BuildTokenMap)
{
    Map temp;
    std::string fileName = "test";
    std::string line = "this is a test";

    temp.tokenMap(fileName,line);

    EXPECT_EQ(temp.wordBuffer.size(),4);
}

TEST(Map, isFullBuffer)
{
    Map temp;
    std::string fileName = "test";
    std::string line = "this is a fun test. this is a fun test. this is a fun test. this is a fun test.";

    temp.tokenMap(fileName,line);

    EXPECT_EQ(temp.wordBuffer.size(),20);
    ASSERT_TRUE(temp.isFull);
}

TEST(Map, ClearBuffer)
{
    Map temp;
    std::string fileName = "test";
    std::string line = "this is a fun test. this is a fun test. this is a fun test. this is a fun test. this is a fun test.";

    temp.clearBuffer();

    EXPECT_EQ(temp.wordBuffer.size(),0);
    ASSERT_FALSE(temp.isFull);
}

TEST(Map, tokenizeTest)
{
    Map temp;
    std::string fileName = "test";
    std::string line = "Apple, breaD CAT isn't happy.";

    temp.tokenMap(fileName,line);

    EXPECT_EQ(temp.wordBuffer[0].first,"apple");
}

int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}