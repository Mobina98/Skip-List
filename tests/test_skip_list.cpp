#include <gtest/gtest.h>
#include "../include/skip_list.hpp"

TEST(SkipListTest, InsertAndContains) {
    stl::SkipList<int> list;
    list.insert(10);
    list.insert(5);
    list.insert(15);

    EXPECT_TRUE(list.contains(10));
    EXPECT_TRUE(list.contains(5));
    EXPECT_TRUE(list.contains(15));
    EXPECT_FALSE(list.contains(20));
}

TEST(SkipListTest, Erase) {
    stl::SkipList<int> list;
    list.insert(8);
    list.insert(12);
    list.insert(3);

    EXPECT_TRUE(list.contains(12));
    list.erase(12);
    EXPECT_FALSE(list.contains(12));
}

TEST(SkipListTest, IteratorTraversal) {
    stl::SkipList<int> list;
    std::vector<int> values = {1, 3, 5, 7};
    for (int v : values) list.insert(v);

    std::vector<int> collected;
    for (int x : list) collected.push_back(x);

    EXPECT_EQ(collected, values);
}