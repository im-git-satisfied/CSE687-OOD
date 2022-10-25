#include <gtest/gtest.h>

#include "../Reduce.h"

TEST(Reduce, basicReduce)
{
    Reduce temp;
    std::string word = "test";
    std::vector<int> counts;
    counts.push_back(1);
    counts.push_back(1);
    counts.push_back(1);
    counts.push_back(1);
    counts.push_back(1);
    counts.push_back(1);
    counts.push_back(1);
    counts.push_back(1);
    std::vector<std::pair<std::string,std::vector<int>>> tVec;

    tVec = temp.reduce(word,counts);

    EXPECT_EQ(tVec.size(),1);
    EXPECT_EQ(tVec[0].first,"test");
    EXPECT_EQ(tVec[0].second[0],8);
}


int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}