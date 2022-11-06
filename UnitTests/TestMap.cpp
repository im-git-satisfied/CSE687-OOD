#include <gtest/gtest.h>
#include <string>

#include "../Map.h"

TEST(Map, BuildTokenMap)
{
    Map temp;
    std::string fileName = "test";
    std::string line = "this is a test";

    temp.tokenMap(fileName,line);

    EXPECT_EQ(temp.getWordBuffer().size(),4);
}

TEST(Map, isFullBuffer)
{
    Map temp;
    std::string fileName = "test";
    std::string line = "this is a fun test. this is a fun test. this is a fun test. this is a fun test.";

    temp.tokenMap(fileName,line);

    EXPECT_EQ(temp.getWordBuffer().size(),20);
    ASSERT_TRUE(temp.checkIsFull());
}

TEST(Map, ClearBuffer)
{
    Map temp;
    std::string fileName = "test";
    std::string line = "this is a fun test. this is a fun test. this is a fun test. this is a fun test. this is a fun test.";

    temp.clearBuffer();

    EXPECT_EQ(temp.getWordBuffer().size(),0);
    ASSERT_FALSE(temp.checkIsFull());
}

TEST(Map, tokenizeTest)
{
    Map temp;
    std::string fileName = "test";
    std::string line = "Apple, breaD CAT isn't happy. [Abstract . ";

    temp.tokenMap(fileName,line);

    EXPECT_EQ(temp.wordBuffer[0].first,"apple");
    EXPECT_EQ(temp.wordBuffer[1].first,"bread");
    EXPECT_EQ(temp.wordBuffer[2].first,"cat");
    EXPECT_EQ(temp.wordBuffer[3].first,"isnt");
    EXPECT_EQ(temp.wordBuffer[4].first,"happy");
    EXPECT_EQ(temp.wordBuffer[5].first,"abstract");
    EXPECT_EQ(temp.wordBuffer[6].first.size(),0);
}

int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}