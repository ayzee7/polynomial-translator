#include <gtest.h>
#include "rb_tree.h"
#include <vector>
#include <string>
#include "polinom.h"

const Polynom P3(Monom(3, 0, 0, 0));
const Polynom P5(Monom(5, 0, 0, 0));
const Polynom P7(Monom(7, 0, 0, 0));
const Polynom P10(Monom(10, 0, 0, 0));
const Polynom P12(Monom(12, 0, 0, 0));
const Polynom P15(Monom(15, 0, 0, 0));
const Polynom P17(Monom(17, 0, 0, 0));
const Polynom P20(Monom(20, 0, 0, 0));
const Polynom P25(Monom(25, 0, 0, 0));


class RBTreeStringPolynomTest : public ::testing::Test {
protected:
    RBTree<std::string, Polynom> tree;

    size_t count_elements() const {
        size_t count = 0;
        auto it = tree.begin();
        auto end_it = tree.end();
        while (it != end_it) {
            ++count;
            ++it;
        }
        return count;
    }

    std::vector<std::string> get_keys_inorder() const {
        std::vector<std::string> keys;
        auto it = tree.begin();
        auto end_it = tree.end();
        while (it != end_it) {
            keys.push_back(it->key);
            ++it;
        }
        return keys;
    }

    bool key_exists(const std::string& key) const
    {
        return tree.find(key) != tree.end();
    }
};


TEST_F(RBTreeStringPolynomTest, empty_tree_iterators_are_equal) {
    EXPECT_EQ(tree.begin(), tree.end());
}

TEST_F(RBTreeStringPolynomTest, empty_tree_element_count_is_zero) {
    EXPECT_EQ(count_elements(), 0);
}

TEST_F(RBTreeStringPolynomTest, empty_tree_properties_valid) {
    EXPECT_TRUE(tree.verify_properties());
}

TEST_F(RBTreeStringPolynomTest, empty_tree_find_returns_end) {
    EXPECT_EQ(tree.find("a"), tree.end());
}

TEST_F(RBTreeStringPolynomTest, empty_tree_erase_returns_end) {
    EXPECT_EQ(tree.erase("a"), tree.end());
    EXPECT_EQ(tree.begin(), tree.end());
}


TEST_F(RBTreeStringPolynomTest, insert_single_returns_valid_iterator) {
    auto it = tree.insert("a", P10);
    EXPECT_NE(it, tree.end());
    EXPECT_EQ(it->key, "a");
}

TEST_F(RBTreeStringPolynomTest, insert_single_sets_correct_value) {
    auto it = tree.insert("a", P5);
    EXPECT_NE(it, tree.end());
    EXPECT_EQ(it->value, P5);
}

TEST_F(RBTreeStringPolynomTest, insert_single_makes_tree_non_empty) {
    tree.insert("a", P10);
    EXPECT_NE(tree.begin(), tree.end());
}

TEST_F(RBTreeStringPolynomTest, insert_single_updates_element_count) {
    tree.insert("a", P10);
    EXPECT_EQ(count_elements(), 1);
}

TEST_F(RBTreeStringPolynomTest, insert_single_maintains_properties) {
    tree.insert("a", P10);
    EXPECT_TRUE(tree.verify_properties());
}

TEST_F(RBTreeStringPolynomTest, find_single_element_check_iterator) {
    tree.insert("a", P10);
    auto found_it = tree.find("a");
    EXPECT_NE(found_it, tree.end());
}

TEST_F(RBTreeStringPolynomTest, find_single_element_check_key) {
    tree.insert("a", P10);
    auto found_it = tree.find("a");
    EXPECT_EQ(found_it->key, "a");
}

TEST_F(RBTreeStringPolynomTest, find_missing_element_in_single_node_tree) {
    tree.insert("a", P10);
    EXPECT_EQ(tree.find("b"), tree.end());
}

TEST_F(RBTreeStringPolynomTest, erase_single_element_makes_tree_empty) {
    tree.insert("a", P10);
    tree.erase("a");
    EXPECT_EQ(tree.begin(), tree.end());
}

TEST_F(RBTreeStringPolynomTest, erase_single_element_updates_element_count) {
    tree.insert("a", P10);
    tree.erase("a");
    EXPECT_EQ(count_elements(), 0);
}

TEST_F(RBTreeStringPolynomTest, erase_single_element_removes_node) {
    tree.insert("a", P10);
    tree.erase("a");
    EXPECT_EQ(tree.find("a"), tree.end());
}

TEST_F(RBTreeStringPolynomTest, erase_single_element_maintains_properties) {
    tree.insert("a", P10);
    tree.erase("a");
    EXPECT_TRUE(tree.verify_properties());
}


TEST_F(RBTreeStringPolynomTest, insert_multiple_updates_element_count_first) {
    tree.insert("a", P10);
    EXPECT_EQ(count_elements(), 1);
}
TEST_F(RBTreeStringPolynomTest, insert_multiple_updates_element_count_second) {
    tree.insert("a", P10);
    tree.insert("b", P20);
    EXPECT_EQ(count_elements(), 2);
}

TEST_F(RBTreeStringPolynomTest, insert_multiple_updates_element_count_third) {
    tree.insert("a", P10);
    tree.insert("b", P20);
    ASSERT_EQ(count_elements(), 2);
    tree.insert("c", P5);
    EXPECT_EQ(count_elements(), 3);
}

TEST_F(RBTreeStringPolynomTest, insert_multiple_maintains_properties_first) {
    tree.insert("b", P10);
    EXPECT_TRUE(tree.verify_properties());
}

TEST_F(RBTreeStringPolynomTest, insert_multiple_maintains_properties_second) {
    tree.insert("b", P10);
    ASSERT_TRUE(tree.verify_properties());
    tree.insert("a", P20);
    EXPECT_TRUE(tree.verify_properties());
}
TEST_F(RBTreeStringPolynomTest, insert_multiple_maintains_properties_third) {
    tree.insert("b", P10);
    tree.insert("a", P20);
    ASSERT_TRUE(tree.verify_properties());
    tree.insert("c", P5);
    EXPECT_TRUE(tree.verify_properties());
}

TEST_F(RBTreeStringPolynomTest, insert_multiple_check_order_size) {
    tree.insert("b", P10);
    tree.insert("c", P20);
    tree.insert("a", P5);
    std::vector<std::string> actual_keys = get_keys_inorder();
    ASSERT_EQ(actual_keys.size(), 3);
}
TEST_F(RBTreeStringPolynomTest, insert_multiple_check_order_first) {
    tree.insert("b", P10);
    tree.insert("c", P20);
    tree.insert("a", P5);
    std::vector<std::string> expected_keys = { "a", "b", "c" };
    std::vector<std::string> actual_keys = get_keys_inorder();
    ASSERT_EQ(actual_keys.size(), 3);
    EXPECT_EQ(actual_keys[0], expected_keys[0]);
}
TEST_F(RBTreeStringPolynomTest, insert_multiple_check_order_second) {
    tree.insert("b", P10);
    tree.insert("c", P20);
    tree.insert("a", P5);
    std::vector<std::string> expected_keys = { "a", "b", "c" };
    std::vector<std::string> actual_keys = get_keys_inorder();
    ASSERT_EQ(actual_keys.size(), 3);
    EXPECT_EQ(actual_keys[1], expected_keys[1]);
}
TEST_F(RBTreeStringPolynomTest, insert_multiple_check_order_third) {
    tree.insert("b", P10);
    tree.insert("c", P20);
    tree.insert("a", P5);
    std::vector<std::string> expected_keys = { "a", "b", "c" };
    std::vector<std::string> actual_keys = get_keys_inorder();
    ASSERT_EQ(actual_keys.size(), 3);
    EXPECT_EQ(actual_keys[2], expected_keys[2]);
}


TEST_F(RBTreeStringPolynomTest, find_multiple_elements_exist_first_two) {
    tree.insert("b", P10);
    tree.insert("c", P20);
    tree.insert("a", P5);
    EXPECT_TRUE(key_exists("a"));
    EXPECT_TRUE(key_exists("b"));
}

TEST_F(RBTreeStringPolynomTest, find_multiple_elements_exist_last_and_missing) {
    tree.insert("b", P10);
    tree.insert("c", P20);
    tree.insert("a", P5);
    EXPECT_TRUE(key_exists("c"));
    EXPECT_FALSE(key_exists("d"));
}


TEST_F(RBTreeStringPolynomTest, insert_recolor_case_properties) {
    tree.insert("m", P10);
    tree.insert("f", P5);
    tree.insert("s", P15);
    ASSERT_TRUE(tree.verify_properties());
    tree.insert("c", P3);
    EXPECT_TRUE(tree.verify_properties());
}
TEST_F(RBTreeStringPolynomTest, insert_recolor_case_element_count) {
    tree.insert("m", P10);
    tree.insert("f", P5);
    tree.insert("s", P15);
    ASSERT_EQ(count_elements(), 3);
    tree.insert("c", P3);
    EXPECT_EQ(count_elements(), 4);
}

TEST_F(RBTreeStringPolynomTest, insert_ll_rotation_properties_first) {
    tree.insert("m", P10);
    tree.insert("f", P5);
    EXPECT_TRUE(tree.verify_properties());
}
TEST_F(RBTreeStringPolynomTest, insert_ll_rotation_properties_second) {
    tree.insert("m", P10);
    tree.insert("f", P5);
    ASSERT_TRUE(tree.verify_properties());
    tree.insert("c", P3);
    EXPECT_TRUE(tree.verify_properties());
}


TEST_F(RBTreeStringPolynomTest, insert_rr_rotation_properties_first) {
    tree.insert("f", P10);
    tree.insert("m", P15);
    EXPECT_TRUE(tree.verify_properties());
}

TEST_F(RBTreeStringPolynomTest, insert_rr_rotation_properties_second) {
    tree.insert("f", P10);
    tree.insert("m", P15);
    ASSERT_TRUE(tree.verify_properties());
    tree.insert("s", P20);
    EXPECT_TRUE(tree.verify_properties());
}

TEST_F(RBTreeStringPolynomTest, insert_lr_rotation_properties_first) {
    tree.insert("m", P10);
    tree.insert("c", P5);
    EXPECT_TRUE(tree.verify_properties());
}

TEST_F(RBTreeStringPolynomTest, insert_lr_rotation_properties_second) {
    tree.insert("m", P10);
    tree.insert("c", P5);
    ASSERT_TRUE(tree.verify_properties());
    tree.insert("f", P7);
    EXPECT_TRUE(tree.verify_properties());
}

TEST_F(RBTreeStringPolynomTest, insert_rl_rotation_properties_first) {
    tree.insert("f", P10);
    tree.insert("s", P15);
    EXPECT_TRUE(tree.verify_properties());
}

TEST_F(RBTreeStringPolynomTest, insert_rl_rotation_properties_second) {
    tree.insert("f", P10);
    tree.insert("s", P15);
    ASSERT_TRUE(tree.verify_properties());
    tree.insert("m", P12);
    EXPECT_TRUE(tree.verify_properties());
}

TEST_F(RBTreeStringPolynomTest, insert_duplicate_key_updates_value_iterator) {
    tree.insert("a", P10);
    tree.insert("b", P20);
    auto it = tree.insert("a", P5);
    EXPECT_NE(it, tree.end());
    EXPECT_EQ(it->value, P5);
}
TEST_F(RBTreeStringPolynomTest, insert_duplicate_key_updates_value_find) {
    tree.insert("a", P10);
    tree.insert("b", P20);
    tree.insert("a", P5);
    auto found_it = tree.find("a");
    EXPECT_NE(found_it, tree.end());
    EXPECT_EQ(found_it->value, P5);
}

TEST_F(RBTreeStringPolynomTest, insert_duplicate_key_does_not_change_element_count) {
    tree.insert("a", P10);
    tree.insert("b", P20);
    ASSERT_EQ(count_elements(), 2);
    tree.insert("a", P5);
    EXPECT_EQ(count_elements(), 2);
}

TEST_F(RBTreeStringPolynomTest, insert_duplicate_key_maintains_properties) {
    tree.insert("a", P10);
    tree.insert("b", P20);
    tree.insert("a", P5);
    EXPECT_TRUE(tree.verify_properties());
}


TEST_F(RBTreeStringPolynomTest, erase_non_existent_key_returns_end) {
    tree.insert("a", P10);
    tree.insert("b", P20);
    EXPECT_EQ(tree.erase("c"), tree.end());
}

TEST_F(RBTreeStringPolynomTest, erase_non_existent_key_doesnt_change_count) {
    tree.insert("a", P10);
    tree.insert("b", P20);
    ASSERT_EQ(count_elements(), 2);
    tree.erase("c");
    EXPECT_EQ(count_elements(), 2);
}

TEST_F(RBTreeStringPolynomTest, erase_non_existent_key_properties) {
    tree.insert("a", P10);
    tree.insert("b", P20);
    tree.erase("c");
    EXPECT_TRUE(tree.verify_properties());
}

TEST_F(RBTreeStringPolynomTest, erase_leaf_updates_element_count) {
    tree.insert("b", P10);
    tree.insert("a", P5);
    tree.insert("c", P15);
    ASSERT_EQ(count_elements(), 3);
    ASSERT_TRUE(tree.verify_properties());
    tree.erase("a");
    EXPECT_EQ(count_elements(), 2);
}

TEST_F(RBTreeStringPolynomTest, erase_leaf_makes_unfindable) {
    tree.insert("b", P10);
    tree.insert("a", P5);
    tree.insert("c", P15);
    ASSERT_TRUE(key_exists("a"));
    tree.erase("a");
    EXPECT_FALSE(key_exists("a"));
}


TEST_F(RBTreeStringPolynomTest, erase_leaf_maintains_properties) {
    tree.insert("b", P10);
    tree.insert("a", P5);
    tree.insert("c", P15);
    tree.erase("a");
    EXPECT_TRUE(tree.verify_properties());
}

TEST_F(RBTreeStringPolynomTest, erase_leaf_keeps_other_keys) {
    tree.insert("b", P10);
    tree.insert("a", P5);
    tree.insert("c", P15);
    tree.erase("a");
    EXPECT_TRUE(key_exists("b"));
    EXPECT_TRUE(key_exists("c"));
}


TEST_F(RBTreeStringPolynomTest, erase_node_with_one_child_updates_count) {
    tree.insert("b", P10);
    tree.insert("a", P5);
    tree.insert("c", P15);
    tree.insert("d", P20);
    ASSERT_EQ(count_elements(), 4);
    tree.erase("c");
    EXPECT_EQ(count_elements(), 3);
}
TEST_F(RBTreeStringPolynomTest, erase_node_with_one_child_makes_unfindable) {
    tree.insert("b", P10);
    tree.insert("a", P5);
    tree.insert("c", P15);
    tree.insert("d", P20);
    ASSERT_TRUE(key_exists("c"));
    tree.erase("c");
    EXPECT_FALSE(key_exists("c"));
}

TEST_F(RBTreeStringPolynomTest, erase_node_with_one_child_keeps_others) {
    tree.insert("b", P10);
    tree.insert("a", P5);
    tree.insert("c", P15);
    tree.insert("d", P20);
    tree.erase("c");
    EXPECT_TRUE(key_exists("a"));
    EXPECT_TRUE(key_exists("b"));
}
TEST_F(RBTreeStringPolynomTest, erase_node_with_one_child_keeps_child) {
    tree.insert("b", P10);
    tree.insert("a", P5);
    tree.insert("c", P15);
    tree.insert("d", P20);
    tree.erase("c");
    EXPECT_TRUE(key_exists("d"));
}
TEST_F(RBTreeStringPolynomTest, erase_node_with_one_child_maintains_properties) {
    tree.insert("b", P10);
    tree.insert("a", P5);
    tree.insert("c", P15);
    tree.insert("d", P20);
    tree.erase("c");
    EXPECT_TRUE(tree.verify_properties());
}



TEST_F(RBTreeStringPolynomTest, erase_node_with_two_children_updates_count) {
    tree.insert("b", P10);
    tree.insert("a", P5);
    tree.insert("c", P15);
    ASSERT_EQ(count_elements(), 3);
    tree.erase("b");
    EXPECT_EQ(count_elements(), 2);
}

TEST_F(RBTreeStringPolynomTest, erase_node_with_two_children_makes_unfindable) {
    tree.insert("b", P10);
    tree.insert("a", P5);
    tree.insert("c", P15);
    ASSERT_TRUE(key_exists("b"));
    tree.erase("b");
    EXPECT_FALSE(key_exists("b"));
}
TEST_F(RBTreeStringPolynomTest, erase_node_with_two_children_keeps_others) {
    tree.insert("b", P10);
    tree.insert("a", P5);
    tree.insert("c", P15);
    tree.erase("b");
    EXPECT_TRUE(key_exists("a"));
    EXPECT_TRUE(key_exists("c"));
}
TEST_F(RBTreeStringPolynomTest, erase_node_with_two_children_maintains_properties) {
    tree.insert("b", P10);
    tree.insert("a", P5);
    tree.insert("c", P15);
    tree.erase("b");
    EXPECT_TRUE(tree.verify_properties());
}
TEST_F(RBTreeStringPolynomTest, erase_node_with_two_children_maintains_order) {
    tree.insert("b", P10);
    tree.insert("a", P5);
    tree.insert("c", P15);
    tree.erase("b");
    std::vector<std::string> expected = { "a", "c" };
    std::vector<std::string> actual = get_keys_inorder();
    ASSERT_EQ(actual, expected);
}

TEST_F(RBTreeStringPolynomTest, erase_root_only_node_makes_tree_empty) {
    tree.insert("a", P10);
    tree.erase("a");
    EXPECT_EQ(count_elements(), 0);
    EXPECT_EQ(tree.begin(), tree.end());
}

TEST_F(RBTreeStringPolynomTest, erase_root_only_node_maintains_properties) {
    tree.insert("a", P10);
    tree.erase("a");
    EXPECT_TRUE(tree.verify_properties());
}


TEST_F(RBTreeStringPolynomTest, begin_on_empty_tree_equals_end) {
    EXPECT_EQ(tree.begin(), tree.end());
}

TEST_F(RBTreeStringPolynomTest, begin_on_non_empty_tree_iterator_check) {
    tree.insert("b", P10);
    tree.insert("a", P5);
    tree.insert("c", P15);
    auto it = tree.begin();
    EXPECT_NE(it, tree.end());
}
TEST_F(RBTreeStringPolynomTest, begin_on_non_empty_tree_key_check) {
    tree.insert("b", P10);
    tree.insert("a", P5);
    tree.insert("c", P15);
    auto it = tree.begin();
    ASSERT_NE(it, tree.end());
    EXPECT_EQ(it->key, "a");
}

TEST_F(RBTreeStringPolynomTest, iterator_pre_increment_iterator_check) {
    tree.insert("b", P10);
    tree.insert("a", P5);
    tree.insert("c", P15);
    auto it = tree.begin();
    ++it;
    EXPECT_NE(it, tree.end());
}
TEST_F(RBTreeStringPolynomTest, iterator_pre_increment_key_check) {
    tree.insert("b", P10);
    tree.insert("a", P5);
    tree.insert("c", P15);
    auto it = tree.begin();
    ++it;
    ASSERT_NE(it, tree.end());
    EXPECT_EQ(it->key, "b");
}

TEST_F(RBTreeStringPolynomTest, iterator_pre_increment_to_next_iterator_check) {
    tree.insert("b", P10);
    tree.insert("a", P5);
    tree.insert("c", P15);
    auto it = tree.begin();
    ++it;
    ++it;
    EXPECT_NE(it, tree.end());
}
TEST_F(RBTreeStringPolynomTest, iterator_pre_increment_to_next_key_check) {
    tree.insert("b", P10);
    tree.insert("a", P5);
    tree.insert("c", P15);
    auto it = tree.begin();
    ++it;
    ++it;
    ASSERT_NE(it, tree.end());
    EXPECT_EQ(it->key, "c");
}

TEST_F(RBTreeStringPolynomTest, iterator_pre_increment_to_end) {
    tree.insert("b", P10);
    tree.insert("a", P5);
    tree.insert("c", P15);
    auto it = tree.begin();
    ++it;
    ++it;
    ++it;
    EXPECT_EQ(it, tree.end());
}

TEST_F(RBTreeStringPolynomTest, iterator_post_increment_prev_check) {
    tree.insert("b", P10);
    tree.insert("a", P5);
    tree.insert("c", P15);
    auto it = tree.begin();
    auto prev_it = it++;
    EXPECT_NE(prev_it, tree.end());
    EXPECT_EQ(prev_it->key, "a");
}
TEST_F(RBTreeStringPolynomTest, iterator_post_increment_current_check) {
    tree.insert("b", P10);
    tree.insert("a", P5);
    tree.insert("c", P15);
    auto it = tree.begin();
    it++;
    EXPECT_NE(it, tree.end());
    EXPECT_EQ(it->key, "b");
}

TEST_F(RBTreeStringPolynomTest, iterator_dereference_value_initial) {
    tree.insert("b", P10);
    tree.insert("a", P5);
    auto it = tree.find("a");
    ASSERT_NE(it, tree.end());
    EXPECT_EQ(it->value, P5);
}

TEST_F(RBTreeStringPolynomTest, iterator_dereference_value_modify_and_check) {
    tree.insert("b", P10);
    tree.insert("a", P5);
    auto it = tree.find("a");
    ASSERT_NE(it, tree.end());
    it->value = P3;
    EXPECT_EQ(tree.find("a")->value, P3);
}

TEST_F(RBTreeStringPolynomTest, iterator_explicit_key_method) {
    tree.insert("a", P10);
    auto it = tree.find("a");
    EXPECT_NE(it, tree.end());
    EXPECT_EQ(it->key, "a");
}

TEST_F(RBTreeStringPolynomTest, iterator_explicit_value_method) {
    tree.insert("a", P10);
    auto it = tree.find("a");
    EXPECT_NE(it, tree.end());
    EXPECT_EQ(it->value, P10);
}


TEST_F(RBTreeStringPolynomTest, range_based_for_loop_finds_key) {
    tree.insert("b", P10);
    tree.insert("a", P5);
    bool found_a = false;
    for (const auto& node_ref : tree) {
        if (node_ref.key == "a") {
            found_a = true;
        }
    }
    EXPECT_TRUE(found_a);
}

TEST_F(RBTreeStringPolynomTest, range_based_for_loop_finds_value) {
    tree.insert("b", P10);
    tree.insert("a", P5);
    bool value_correct = false;
    for (const auto& node_ref : tree) {
        if (node_ref.key == "a") {
            if (node_ref.value == P5) {
                value_correct = true;
            }
        }
    }
    EXPECT_TRUE(value_correct);
}
TEST_F(RBTreeStringPolynomTest, stress_test_insert_erase_verify) {
    const size_t num_elements = 1000;
    const size_t delete_step = 3;
    std::vector<std::string> all_keys(num_elements);
    std::vector<std::string> expected_remaining_keys;

    for (size_t i = 0; i < num_elements; ++i) {
        all_keys[i] = "key_" + std::to_string(i);
    }

    for (size_t i = 0; i < num_elements; ++i) {
        tree.insert(all_keys[i], P5);
        if (i % 100 == 99) {
            ASSERT_TRUE(tree.verify_properties());
        }
    }
    ASSERT_EQ(count_elements(), num_elements);
    ASSERT_TRUE(tree.verify_properties());


    std::vector<std::string> keys_to_delete;
    for (size_t i = 0; i < num_elements; ++i) {
        if (i % delete_step == 0) {
            keys_to_delete.push_back(all_keys[i]);
        }
        else {
            expected_remaining_keys.push_back(all_keys[i]);
        }
    }

    for (const auto& key_to_delete : keys_to_delete) {
        tree.erase(key_to_delete);
    }
    ASSERT_TRUE(tree.verify_properties());


    ASSERT_EQ(count_elements(), expected_remaining_keys.size());

    std::vector<std::string> actual_remaining_keys = get_keys_inorder();
    std::sort(expected_remaining_keys.begin(), expected_remaining_keys.end());
    ASSERT_EQ(actual_remaining_keys, expected_remaining_keys);


    for (const auto& remaining_key : expected_remaining_keys) {
        EXPECT_TRUE(key_exists(remaining_key));
    }

    for (const auto& deleted_key : keys_to_delete) {
        EXPECT_FALSE(key_exists(deleted_key));
    }
}
