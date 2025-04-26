#include <gtest.h>
#include "hash_chain.h"
#include "polinom.h"
#include <string>


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


class HashTableChainingPolynomTest : public ::testing::Test {
protected:
    HashTableChaining<std::string, Polynom> table;
};


TEST_F(HashTableChainingPolynomTest, default_constructor_is_empty) {
    ASSERT_TRUE(table.empty());
}

TEST_F(HashTableChainingPolynomTest, default_constructor_size_is_zero) {
    ASSERT_EQ(table.size(), 0);
}

TEST_F(HashTableChainingPolynomTest, default_constructor_begin_equals_end) {
    ASSERT_EQ(table.begin(), table.end());
}

TEST_F(HashTableChainingPolynomTest, constructor_with_initial_buckets_is_empty) {
    HashTableChaining<std::string, Polynom> sized_table(32);
    ASSERT_TRUE(sized_table.empty());
    ASSERT_EQ(sized_table.size(), 0);
}

TEST_F(HashTableChainingPolynomTest, insert_single_element_increases_size) {
    table.insert("a", P5);
    ASSERT_EQ(table.size(), 1);
    ASSERT_FALSE(table.empty());
}

TEST_F(HashTableChainingPolynomTest, insert_single_element_allows_find) {
    table.insert("a", P5);
    auto it = table.find("a");
    ASSERT_NE(it, table.end());
}

TEST_F(HashTableChainingPolynomTest, insert_single_element_find_has_correct_value) {
    table.insert("a", P5);
    auto it = table.find("a");
    ASSERT_EQ(it->second, P5);
    ASSERT_EQ(it.value(), P5);
}

TEST_F(HashTableChainingPolynomTest, insert_multiple_elements_increases_size) {
    table.insert("a", P5);
    table.insert("b", P7);
    ASSERT_EQ(table.size(), 2);
}

TEST_F(HashTableChainingPolynomTest, insert_multiple_elements_allows_find) {
    table.insert("a", P5);
    table.insert("b", P7);
    auto it1 = table.find("a");
    auto it2 = table.find("b");
    ASSERT_NE(it1, table.end());
    ASSERT_NE(it2, table.end());
}

TEST_F(HashTableChainingPolynomTest, insert_duplicate_key_throws) {
    table.insert("a", P3);
    ASSERT_ANY_THROW(table.insert("a", P12));
}

TEST_F(HashTableChainingPolynomTest, insert_duplicate_key_does_not_change_size) {
    table.insert("a", P3);
    try {
        table.insert("a", P12);
    }
    catch (int) {}
    ASSERT_EQ(table.size(), 1);
}

TEST_F(HashTableChainingPolynomTest, insert_duplicate_key_keeps_original_value) {
    table.insert("a", P3);
    try {
        table.insert("a", P12);
    }
    catch (int) {}
    ASSERT_EQ(table.find("a")->second, P3);
}

TEST_F(HashTableChainingPolynomTest, find_non_existent_key_returns_end) {
    table.insert("a", P5);
    auto it = table.find("b");
    ASSERT_EQ(it, table.end());
}

TEST_F(HashTableChainingPolynomTest, find_in_empty_table_returns_end) {
    auto it = table.find("a");
    ASSERT_EQ(it, table.end());
}

TEST_F(HashTableChainingPolynomTest, operator_bracket_finds_existing) {
    table.insert("a", P3);
    ASSERT_EQ(table["a"], P3);
}

TEST_F(HashTableChainingPolynomTest, operator_bracket_modifies_existing) {
    table.insert("a", P3);
    table["a"] = P12;
    ASSERT_EQ(table.find("a")->second, P12);
}

TEST_F(HashTableChainingPolynomTest, operator_bracket_throws_on_non_existent) {
    ASSERT_ANY_THROW(table["a"]);
}

TEST_F(HashTableChainingPolynomTest, erase_existing_element_decreases_size) {
    table.insert("a", P1);
    table.insert("b", P2);
    table.erase("a");
    ASSERT_EQ(table.size(), 1);
}

TEST_F(HashTableChainingPolynomTest, erase_existing_element_makes_it_unfindable) {
    table.insert("a", P1);
    table.insert("b", P2);
    table.erase("a");
    ASSERT_EQ(table.find("a"), table.end());
}

TEST_F(HashTableChainingPolynomTest, erase_only_element_makes_table_empty) {
    table.insert("a", P1);
    table.erase("a");
    ASSERT_TRUE(table.empty());
    ASSERT_EQ(table.size(), 0);
}

TEST_F(HashTableChainingPolynomTest, erase_only_element_returns_end_iterator) {
    table.insert("a", P1);
    auto it = table.erase("a");
    ASSERT_EQ(it, table.end());
}

TEST_F(HashTableChainingPolynomTest, erase_non_existent_returns_end_iterator) {
    table.insert("a", P10);
    auto it = table.erase("b");
    ASSERT_EQ(it, table.end());
}

TEST_F(HashTableChainingPolynomTest, erase_non_existent_does_not_change_size) {
    table.insert("a", P10);
    table.erase("b");
    ASSERT_EQ(table.size(), 1);
}

TEST_F(HashTableChainingPolynomTest, erase_from_empty_table_returns_end) {
    auto it = table.erase("a");
    ASSERT_EQ(it, table.end());
}

TEST_F(HashTableChainingPolynomTest, begin_not_equal_end_for_non_empty) {
    table.insert("a", P5);
    ASSERT_NE(table.begin(), table.end());
}

TEST_F(HashTableChainingPolynomTest, iterator_access_key) {
    table.insert("a", P5);
    auto it = table.begin();
    ASSERT_EQ(it.key(), "a");
}

TEST_F(HashTableChainingPolynomTest, iterator_access_value) {
    table.insert("a", P5);
    auto it = table.begin();
    ASSERT_EQ(it.value(), P5);
}

TEST_F(HashTableChainingPolynomTest, iterator_dereference) {
    table.insert("a", P5);
    auto it = table.begin();
    std::pair<std::string, Polynom> p = *it;
    ASSERT_EQ(p.first, "a");
    ASSERT_EQ(p.second, P5);
}

TEST_F(HashTableChainingPolynomTest, iterator_arrow_operator) {
    table.insert("a", P5);
    auto it = table.begin();
    ASSERT_EQ(it->first, "a");
    ASSERT_EQ(it->second, P5);
}

TEST_F(HashTableChainingPolynomTest, iterator_increment_moves_to_next) {
    table.insert("a", P5);
    table.insert("b", P15);
    auto it = table.begin();
    std::string key1 = it.key();
    ++it;
    ASSERT_NE(it, table.end());
    ASSERT_NE(it.key(), key1);
}

TEST_F(HashTableChainingPolynomTest, iterator_increment_reaches_end) {
    table.insert("a", P5);
    auto it = table.begin();
    ++it;
    ASSERT_EQ(it, table.end());
}

TEST_F(HashTableChainingPolynomTest, iteration_visits_all_elements) {
    table.insert("a", P5);
    table.insert("b", P15);
    table.insert("c", P25);
    size_t count = 0;
    for (auto it = table.begin(); it != table.end(); ++it)
        count++;
    ASSERT_EQ(count, 3);
}

TEST(HashTableChainingCollisionPolynomTest, insert_colliding_keys_increases_size) {
    HashTableChaining<std::string, Polynom> table(4);
    table.insert("a", P0);
    table.insert("b", P4);
    ASSERT_EQ(table.size(), 2);
}

TEST(HashTableChainingCollisionPolynomTest, find_works_for_colliding_keys) {
    HashTableChaining<std::string, Polynom> table(4);
    table.insert("a", P0);
    table.insert("b", P4);
    auto it0 = table.find("a");
    auto it4 = table.find("b");
    ASSERT_NE(it0, table.end());
    ASSERT_NE(it4, table.end());
    ASSERT_EQ(it0->second, P0);
    ASSERT_EQ(it4->second, P4);
}

TEST(HashTableChainingCollisionPolynomTest, erase_one_colliding_key_keeps_other) {
    HashTableChaining<std::string, Polynom> table(4);
    table.insert("a", P0);
    table.insert("b", P4);
    table.erase("a");
    ASSERT_EQ(table.size(), 1);
    ASSERT_EQ(table.find("a"), table.end());
    ASSERT_NE(table.find("b"), table.end());
}

TEST(HashTableChainingCollisionPolynomTest, iteration_visits_colliding_keys) {
    HashTableChaining<std::string, Polynom> table(4);
    table.insert("a", P0);
    table.insert("b", P4);
    table.insert("c", P1);
    size_t count = 0;
    for (auto it = table.begin(); it != table.end(); ++it) {
        count++;
    }
    ASSERT_EQ(count, 3);
}
TEST(HashTableChainingCollisionPolynomTest, insert_colliding_keys_in_small_table_increases_size) {
    HashTableChaining<std::string, Polynom> table(1);
    table.insert("a", P0);
    table.insert("b", P4);
    ASSERT_EQ(table.size(), 2);
}