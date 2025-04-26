#include <gtest.h>
#include "unord_arr.h"
#include "polinom.h"
#include <string>
#include <vector>


const Polynom P0(Monom(0, 0, 0, 0));
const Polynom P1(Monom(1, 0, 0, 0));
const Polynom P2(Monom(2, 0, 0, 0));
const Polynom P3(Monom(3, 0, 0, 0));
const Polynom P4(Monom(4, 0, 0, 0));
const Polynom P5(Monom(5, 0, 0, 0));
const Polynom P7(Monom(7, 0, 0, 0));
const Polynom P10(Monom(10, 0, 0, 0));
const Polynom P12(Monom(12, 0, 0, 0));
const Polynom P15(Monom(15, 0, 0, 0));
const Polynom P25(Monom(25, 0, 0, 0));


class UnorderedTableStrPolyTest : public ::testing::Test {
protected:
    UnorderedTable<std::string, Polynom> table;

    bool key_exists(const std::string& key)
    {
        return table.find(key) != table.end();
    }
};


TEST_F(UnorderedTableStrPolyTest, default_constructor_is_empty) {
    ASSERT_EQ(table.size(), 0);
}

TEST_F(UnorderedTableStrPolyTest, default_constructor_size_is_zero) {
    ASSERT_EQ(table.size(), 0);
}

TEST_F(UnorderedTableStrPolyTest, default_constructor_begin_equals_end) {
    ASSERT_EQ(table.begin(), table.end());
}

TEST_F(UnorderedTableStrPolyTest, insert_single_element_increases_count) {
    table.insert("a", P5);
    ASSERT_EQ(table.size(), 1);
}

TEST_F(UnorderedTableStrPolyTest, insert_single_element_makes_not_empty) {
    table.insert("a", P5);
    ASSERT_NE(table.begin(), table.end());
}

TEST_F(UnorderedTableStrPolyTest, insert_single_element_allows_find) {
    table.insert("a", P5);
    auto it = table.find("a");
    ASSERT_NE(it, table.end());
}

TEST_F(UnorderedTableStrPolyTest, insert_single_element_find_has_correct_value) {
    table.insert("a", P5);
    auto it = table.find("a");
    ASSERT_NE(it, table.end());
    ASSERT_EQ(it->second, P5);
}

TEST_F(UnorderedTableStrPolyTest, insert_multiple_elements_increases_count) {
    table.insert("a", P5);
    table.insert("b", P7);
    table.insert("c", P3);
    ASSERT_EQ(table.size(), 3);
}

TEST_F(UnorderedTableStrPolyTest, insert_multiple_elements_allows_find_first_two) {
    table.insert("a", P5);
    table.insert("b", P7);
    table.insert("c", P3);
    ASSERT_TRUE(key_exists("a"));
    ASSERT_TRUE(key_exists("c"));
}

TEST_F(UnorderedTableStrPolyTest, insert_multiple_elements_allows_find_last_and_missing) {
    table.insert("a", P5);
    table.insert("b", P7);
    table.insert("c", P3);
    ASSERT_TRUE(key_exists("a"));
    ASSERT_FALSE(key_exists("x"));
}

TEST_F(UnorderedTableStrPolyTest, cant_insert_alredy_existing_elem) {
    table.insert("a", P3);
    ASSERT_EQ(table.size(), 1);
    ASSERT_ANY_THROW(table.insert("a", P1));
}

TEST_F(UnorderedTableStrPolyTest, find_non_existent_key_returns_end) {
    table.insert("a", P5);
    auto it = table.find("b");
    ASSERT_EQ(it, table.end());
}

TEST_F(UnorderedTableStrPolyTest, find_in_empty_table_returns_end) {
    auto it = table.find("a");
    ASSERT_EQ(it, table.end());
}

TEST_F(UnorderedTableStrPolyTest, operator_bracket_finds_existing) {
    table.insert("a", P3);
    auto it = table.find("a");
    ASSERT_NE(it, table.end());
    ASSERT_EQ(it->second, P3);
}

TEST_F(UnorderedTableStrPolyTest, operator_bracket_modifies_existing) {
    table.insert("a", P3);
    table["a"] = P12;
    auto it = table.find("a");
    ASSERT_NE(it, table.end());
    ASSERT_EQ(it->second, P12);
}

TEST_F(UnorderedTableStrPolyTest, have_no_access_to_not_existing_elem) {
    ASSERT_ANY_THROW(table["a"] = P10);
}


TEST_F(UnorderedTableStrPolyTest, erase_existing_element_decreases_count) {
    table.insert("a", P1);
    table.insert("b", P2);
    table.erase("a");
    ASSERT_EQ(table.size(), 1);
}

TEST_F(UnorderedTableStrPolyTest, erase_existing_element_makes_it_unfindable) {
    table.insert("a", P1);
    table.insert("b", P2);
    table.erase("a");
    ASSERT_FALSE(key_exists("a"));
    ASSERT_TRUE(key_exists("b"));
}

TEST_F(UnorderedTableStrPolyTest, erase_only_element_makes_table_empty) {
    table.insert("a", P1);
    table.erase("a");
    ASSERT_EQ(table.begin(), table.end());
    ASSERT_EQ(table.size(), 0);
}

TEST_F(UnorderedTableStrPolyTest, erase_non_existent_does_not_change_count) {
    table.insert("a", P10);
    table.erase("b");
    ASSERT_EQ(table.size(), 1);
    ASSERT_TRUE(key_exists("a"));
}

TEST_F(UnorderedTableStrPolyTest, erase_from_empty_table_does_nothing) {
    table.erase("a");
    ASSERT_EQ(table.size(), 0);
    ASSERT_EQ(table.begin(), table.end());
}


TEST_F(UnorderedTableStrPolyTest, begin_not_equal_end_for_non_empty) {
    table.insert("a", P5);
    ASSERT_NE(table.begin(), table.end());
}

TEST_F(UnorderedTableStrPolyTest, iterator_dereference) {
    table.insert("a", P5);
    auto it = table.begin();
    ASSERT_NE(it, table.end());
    std::pair<const std::string, Polynom> p = *it;
    ASSERT_EQ(p.first, "a");
    ASSERT_EQ(p.second, P5);
}

TEST_F(UnorderedTableStrPolyTest, iterator_arrow_operator) {
    table.insert("a", P5);
    auto it = table.begin();
    ASSERT_NE(it, table.end());
    ASSERT_EQ(it->first, "a");
    ASSERT_EQ(it->second, P5);
}


TEST_F(UnorderedTableStrPolyTest, iterator_pre_increment_moves_to_next) {
    table.insert("a", P10);
    table.insert("b", P5);
    auto it = table.begin();
    ASSERT_NE(it, table.end());
    ++it;
    if (table.size() > 1) {
        ASSERT_NE(it, table.end());
    }
    else {
        ASSERT_EQ(it, table.end());
    }
}

TEST_F(UnorderedTableStrPolyTest, iterator_pre_increment_reaches_end) {
    table.insert("a", P5);
    table.insert("b", P10);
    auto it = table.begin();
    size_t count = 0;
    while (it != table.end()) {
        ++count;
        ++it;
    }
    ASSERT_EQ(count, table.size());
    ASSERT_EQ(it, table.end());
}

TEST_F(UnorderedTableStrPolyTest, iteration_visits_all_elements) {
    table.insert("a", P10);
    table.insert("b", P5);
    table.insert("c", P25);
    table.insert("d", P15);

    std::vector<std::string> keys_expected;
    keys_expected.push_back("a");
    keys_expected.push_back("b");
    keys_expected.push_back("c");
    keys_expected.push_back("d");

    std::vector<std::string> keys_visited;
    size_t count = 0;
    for (auto it = table.begin(); it != table.end(); ++it) {
        keys_visited.push_back(it->first);
        count++;
    }

    ASSERT_EQ(count, 4);
    ASSERT_EQ(keys_visited, keys_expected);
}