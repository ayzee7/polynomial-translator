#include <gtest.h>
#include "bs_tree.h"
#include "avl_tree.h"
#include "polinom.h"

TEST(BinarySearchTree, CanInsert) {
	BSTree<std::string, Polynom> t;
	Polynom p1(Monom(1, 1, 1, 1));
	Polynom p2(Monom(2, 1, 1, 1));
	Polynom p3(Monom(3, 1, 1, 1));
	Polynom p4(Monom(4, 1, 1, 1));
	Polynom p5(Monom(5, 1, 1, 1));
	t.insert("c", p3);
	t.insert("a", p1);
	t.insert("b", p2);
	t.insert("e", p5);
	t.insert("d", p4);

	for (auto i = t.begin(); i != t.null(); ++i) {
		std::cout << i.key();
	}
	auto keys = t.print_keys();
	std::string keys_str;
	for (const auto& s : keys) keys_str += s;
	EXPECT_EQ(keys_str, "abcde");
	EXPECT_TRUE(t.is_balanced());
}

TEST(BinarySearchTree, ThrowsWhenInsertingExistingElement) {
	BSTree<std::string, Polynom> t;
	Polynom p1(Monom(1, 1, 1, 1));
	t.insert("a", p1);
	ASSERT_ANY_THROW(t.insert("a", p1));
}

TEST(BinarySearchTree, CanEraseLeaf) {
	BSTree<std::string, Polynom> t;
	Polynom p1(Monom(1, 1, 1, 1));
	Polynom p2(Monom(2, 1, 1, 1));
	Polynom p3(Monom(3, 1, 1, 1));
	Polynom p4(Monom(4, 1, 1, 1));
	Polynom p5(Monom(5, 1, 1, 1));
	t.insert("c", p3);
	t.insert("a", p1);
	t.insert("b", p2);
	EXPECT_FALSE(t.is_balanced());
	t.erase("b");
	auto keys = t.print_keys();

	for (auto i = t.begin(); i != t.null(); ++i) {
		std::cout << i.key();
	}
	std::string keys_str;
	for (const auto& s : keys) keys_str += s;
	ASSERT_EQ(keys_str, "ac");
}

TEST(BinarySearchTree, CanEraseSubrootWithOneChild) {
	BSTree<std::string, Polynom> t;
	Polynom p1(Monom(1, 1, 1, 1));
	Polynom p2(Monom(2, 1, 1, 1));
	Polynom p3(Monom(3, 1, 1, 1));
	Polynom p4(Monom(4, 1, 1, 1));
	Polynom p5(Monom(5, 1, 1, 1));
	t.insert("c", p3);
	t.insert("a", p1);
	t.insert("b", p2);
	t.erase("a");

	for (auto i = t.begin(); i != t.null(); ++i) {
		std::cout << i.key();
	}
	auto keys = t.print_keys();
	std::string keys_str;
	for (const auto& s : keys) keys_str += s;
	ASSERT_EQ(keys_str, "bc");
}

TEST(BinarySearchTree, CanEraseRoot) {
	BSTree<std::string, Polynom> t;
	Polynom p1(Monom(1, 1, 1, 1));
	Polynom p2(Monom(2, 1, 1, 1));
	Polynom p3(Monom(3, 1, 1, 1));
	Polynom p4(Monom(4, 1, 1, 1));
	Polynom p5(Monom(5, 1, 1, 1));
	t.insert("c", p3);
	t.insert("a", p1);
	t.insert("b", p2);
	t.erase("c");

	for (auto i = t.begin(); i != t.null(); ++i) {
		std::cout << i.key();
	}
	auto keys = t.print_keys();
	std::string keys_str;
	for (const auto& s : keys) keys_str += s;
	ASSERT_EQ(keys_str, "ab");
}

TEST(BinarySearchTree, ErasingNonExistingNodeReturnsNullIterator) {
	BSTree<std::string, Polynom> t;
	ASSERT_EQ(t.erase("c"), t.null());
}

TEST(BinarySearchTree, CanFind) {
	BSTree<std::string, Polynom> t;
	Polynom p1(Monom(1, 1, 1, 1));
	Polynom p2(Monom(2, 1, 1, 1));
	Polynom p3(Monom(3, 1, 1, 1));
	Polynom p4(Monom(4, 1, 1, 1));
	Polynom p5(Monom(5, 1, 1, 1));
	t.insert("c", p3);
	t.insert("a", p1);
	t.insert("b", p2);
	t.insert("e", p5);
	t.insert("d", p4);
	auto c = t.find("c");
	auto d = t.find("d");
	auto a = t.find("a");
	EXPECT_EQ(c.key(), "c");
	EXPECT_EQ(d.key(), "d");
	EXPECT_EQ(a.key(), "a");
}

TEST(BinarySearchTree, FindingNonExistingNodeReturnsNullIterator) {
	BSTree<std::string, Polynom> t;
	ASSERT_EQ(t.find("c"), t.null());
}

TEST(AVLTree, CanInsert) {
	AVLTree<std::string, Polynom> t;
	Polynom p1(Monom(1, 1, 1, 1));
	Polynom p2(Monom(2, 1, 1, 1));
	Polynom p3(Monom(3, 1, 1, 1));
	Polynom p4(Monom(4, 1, 1, 1));
	Polynom p5(Monom(5, 1, 1, 1));
	t.insert("c", p3);
	t.insert("a", p1);
	t.insert("b", p2);
	t.insert("e", p5);
	t.insert("d", p4);

	for (auto i = t.begin(); i != t.null(); ++i) {
		std::cout << i.key();
	}

	auto keys = t.print_keys();
	std::string keys_str;
	for (const auto& s : keys) keys_str += s;
	EXPECT_EQ(keys_str, "abcde");
	EXPECT_TRUE(t.is_balanced());
}

TEST(AVLTree, CanEraseLeaf) {
	AVLTree<std::string, Polynom> t;
	Polynom p1(Monom(1, 1, 1, 1));
	Polynom p2(Monom(2, 1, 1, 1));
	Polynom p3(Monom(3, 1, 1, 1));
	Polynom p4(Monom(4, 1, 1, 1));
	Polynom p5(Monom(5, 1, 1, 1));
	t.insert("c", p3);
	t.insert("a", p1);
	t.insert("b", p2);
	EXPECT_TRUE(t.is_balanced());

	t.erase("b");

	for (auto i = t.begin(); i != t.null(); ++i) {
		std::cout << i.key();
	}
	auto keys = t.print_keys();
	std::string keys_str;
	for (const auto& s : keys) keys_str += s;
	ASSERT_EQ(keys_str, "ac");
}

TEST(AVLTree, CanEraseSubrootWithOneChild) {
	AVLTree<std::string, Polynom> t;
	Polynom p1(Monom(1, 1, 1, 1));
	Polynom p2(Monom(2, 1, 1, 1));
	Polynom p3(Monom(3, 1, 1, 1));
	Polynom p4(Monom(4, 1, 1, 1));
	Polynom p5(Monom(5, 1, 1, 1));
	t.insert("c", p3);
	t.insert("a", p1);
	t.insert("b", p2);
	t.insert("e", p5);
	t.insert("d", p4);
	t.erase("a");

	EXPECT_TRUE(t.is_balanced());

	for (auto i = t.begin(); i != t.null(); ++i) {
		std::cout << i.key();
	}
	auto keys = t.print_keys();
	std::string keys_str;
	for (const auto& s : keys) keys_str += s;
	ASSERT_EQ(keys_str, "bcde");
}

TEST(AVLTree, CanEraseRoot) {
	AVLTree<std::string, Polynom> t;
	Polynom p1(Monom(1, 1, 1, 1));
	Polynom p2(Monom(2, 1, 1, 1));
	Polynom p3(Monom(3, 1, 1, 1));
	Polynom p4(Monom(4, 1, 1, 1));
	Polynom p5(Monom(5, 1, 1, 1));
	t.insert("c", p3);
	t.insert("a", p1);
	t.insert("b", p2);
	t.insert("e", p5);
	t.insert("d", p4);
	t.erase("c");

	EXPECT_TRUE(t.is_balanced());

	for (auto i = t.begin(); i != t.null(); ++i) {
		std::cout << i.key();
	}
	auto keys = t.print_keys();
	std::string keys_str;
	for (const auto& s : keys) keys_str += s;
	ASSERT_EQ(keys_str, "abde");
}