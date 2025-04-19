#include <gtest.h>
#include "bs_tree.h"
#include "polinom.h"
#include <numeric>
#include <algorithm>
#include <random>
#include <chrono>

//	Iterator tests

TEST(BSTreeIterator, CanCreateIterators) {
	BSTree<std::string, Polynom> table;
	EXPECT_NO_THROW(table.begin());
	EXPECT_NO_THROW(table.root());
	EXPECT_NO_THROW(table.null());
}

TEST(BSTreeIterator, CanIterateThroughTableUsingIterator) {
	BSTree<std::string, Polynom> table;
	ASSERT_NO_THROW(for (auto i = table.begin(); i != table.null(); ++i));
}

//	Binary search tree tests	

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

TEST(BinarySearchTree, StressTestInsertHundredThousand) {
	BSTree<int, Polynom> t;
	Polynom p(Monom(1, 1, 1, 1));
	std::vector<int> keys(100000);
	std::iota(keys.begin(), keys.end(), 1);
	std::shuffle(keys.begin(), keys.end(), std::mt19937{ std::random_device{}() });

	auto start = std::chrono::high_resolution_clock::now();
	for (int key : keys) {
		t.insert(key, p);
	}
	auto fin = std::chrono::high_resolution_clock::now();
	std::cout << "elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(fin - start).count() << std::endl;
	ASSERT_NE(t.begin(), t.null());
}

TEST(BinarySearchTree, StressTestInsertMillion) {
	BSTree<int, Polynom> t;
	Polynom p(Monom(1, 1, 1, 1));
	std::vector<int> keys(1000000);
	std::iota(keys.begin(), keys.end(), 1);
	std::shuffle(keys.begin(), keys.end(), std::mt19937{ std::random_device{}() });

	auto start = std::chrono::high_resolution_clock::now();
	for (int key : keys) {
		t.insert(key, p);
	}
	auto fin = std::chrono::high_resolution_clock::now();
	std::cout << "elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(fin - start).count() << std::endl;
	ASSERT_NE(t.begin(), t.null());
}

TEST(BinarySearchTree, StressTestInsertTenMillion) {
	BSTree<int, Polynom> t;
	Polynom p(Monom(1, 1, 1, 1));
	std::vector<int> keys(10000000);
	std::iota(keys.begin(), keys.end(), 1);
	std::shuffle(keys.begin(), keys.end(), std::mt19937{ std::random_device{}() });

	auto start = std::chrono::high_resolution_clock::now();
	for (int key : keys) {
		t.insert(key, p);
	}
	auto fin = std::chrono::high_resolution_clock::now();
	std::cout << "elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(fin - start).count() << std::endl;
	ASSERT_NE(t.begin(), t.null());
}