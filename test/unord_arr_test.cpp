#include "unord_arr.h"
#include <gtest.h>

TEST(UnorderedTableTest, InsertAndFind) {
    UnorderedTable<int, std::string> table;
    auto it = table.insert(1, "one");
    EXPECT_EQ(it.key(), 1);
    EXPECT_EQ(it.value(), "one");

    it = table.find(1);
    EXPECT_NE(it, table.end());
    EXPECT_EQ(it.key(), 1);
    EXPECT_EQ(it.value(), "one");
}

TEST(UnorderedTableTest, InsertDuplicateKey) {
    UnorderedTable<int, std::string> table;
    table.insert(1, "one");
    EXPECT_THROW(table.insert(1, "duplicate"), std::runtime_error);
}

TEST(UnorderedTableTest, EraseExisting) {
    UnorderedTable<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    auto it = table.erase(1);
    EXPECT_EQ(it, table.end()) << "Erase should return end() when last element is removed";

    it = table.find(1);
    EXPECT_EQ(it, table.end());
}

TEST(UnorderedTableTest, EraseNonExisting) {
    UnorderedTable<int, std::string> table;
    table.insert(1, "one");
    auto it = table.erase(2);
    EXPECT_EQ(it, table.end());
}

TEST(UnorderedTableTest, OperatorAccess) {
    UnorderedTable<int, std::string> table;
    table.insert(1, "one");
    EXPECT_EQ(table[1], "one");
    EXPECT_THROW(table[2], std::runtime_error);
}

TEST(UnorderedTableTest, SizeAndEmpty) {
    UnorderedTable<int, std::string> table;
    EXPECT_TRUE(table.empty());
    EXPECT_EQ(table.size(), 0);

    table.insert(1, "one");
    EXPECT_FALSE(table.empty());
    EXPECT_EQ(table.size(), 1);
}