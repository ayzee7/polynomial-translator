#include <gtest.h>
#include "avl_tree.h"
#include "polinom.h"
#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>

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

	for (auto i = t.begin(); i != t.end(); ++i) {
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

	for (auto i = t.begin(); i != t.end(); ++i) {
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

	for (auto i = t.begin(); i != t.end(); ++i) {
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

	for (auto i = t.begin(); i != t.end(); ++i) {
		std::cout << i.key();
	}
	auto keys = t.print_keys();
	std::string keys_str;
	for (const auto& s : keys) keys_str += s;
	ASSERT_EQ(keys_str, "abde");
}

TEST(AVLTree, StressTestInsertHundredThousand) {
	AVLTree<int, Polynom> t;
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
	ASSERT_NE(t.begin(), t.end());
}

TEST(AVLTree, StressTestInsertMillion) {
	AVLTree<int, Polynom> t;
	Polynom p(Monom(1, 1, 1, 1));
	std::vector<int> keys(1000000);
	std::iota(keys.begin(), keys.end(), 1);
	std::shuffle(keys.begin(), keys.end(), std::mt19937{ std::random_device{}()});

	auto start = std::chrono::high_resolution_clock::now();
	for (int key : keys) {
		t.insert(key, p);
	}
	auto fin = std::chrono::high_resolution_clock::now();
	std::cout << "elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(fin - start).count() << std::endl;
	ASSERT_NE(t.begin(), t.end());
}
/*
TEST(AVLTree, StressTestInsertTenMillion) {
	AVLTree<int, Polynom> t;
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
	ASSERT_NE(t.begin(), t.end());
}
*/