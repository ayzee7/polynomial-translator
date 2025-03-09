#include <gtest.h>
#include <algorithm>
#include "ord_tab.h"
#include "polinom.h"

//	Iterator tests

TEST(OrderedHashTableIterator, CanCreateBeginAndEndIterator) {
	OrderedHashTable<std::string, Polynom> table;
	EXPECT_NO_THROW(table.begin());
	EXPECT_NO_THROW(table.end());
}

TEST(OrderedHashTableIterator, CanIterateThroughTableUsingIterator) {
	OrderedHashTable<std::string, Polynom> table;
	ASSERT_NO_THROW(for (auto i = table.begin(); i != table.end(); ++i));
}

//	Ordered table tests

TEST(OrderedHashTable, CanInsert) {
	OrderedHashTable<std::string, Polynom> table;
	Polynom p(Monom(1, 1, 1, 1));
	table.insert("a", p);
	table.insert("f", p);
	table.insert("g", p);
	table.insert("b", p);

	std::vector<size_t> table_exp;
	table_exp.push_back(std::hash<std::string>{}("a"));
	table_exp.push_back(std::hash<std::string>{}("b"));
	table_exp.push_back(std::hash<std::string>{}("f"));
	table_exp.push_back(std::hash<std::string>{}("g"));
	std::sort(table_exp.begin(), table_exp.end());

	auto it = table.begin();
	auto it_exp = table_exp.begin();
	bool isSame = true;
	for (; it != table.end() || it_exp != table_exp.end(); ++it, ++it_exp) {
		if (it.key() != *it_exp) {
			isSame = false;
			break;
		}
	}
	ASSERT_TRUE(isSame);
}

TEST(OrderedHashTable, ThrowsWhenInsertingExistingElement) {
	OrderedHashTable<std::string, Polynom> table;
	Polynom p(Monom(1, 1, 1, 1));
	table.insert("a", p);
	ASSERT_ANY_THROW(table.insert("a", p));
}

TEST(OrderedHashTable, CanErase) {
	OrderedHashTable<std::string, Polynom> table;
	Polynom p(Monom(1, 1, 1, 1));
	table.insert("a", p);
	table.insert("f", p);
	table.insert("g", p);
	table.insert("b", p);

	table.erase("a");
	table.erase("f");
	table.erase("g");

	std::vector<size_t> table_exp;
	table_exp.push_back(std::hash<std::string>{}("b"));

	auto it = table.begin();
	auto it_exp = table_exp.begin();
	bool isSame = true;
	for (; it != table.end() || it_exp != table_exp.end(); ++it, ++it_exp) {
		if (it.key() != *it_exp) {
			isSame = false;
			break;
		}
	}
	ASSERT_TRUE(isSame);
}

TEST(OrderedHashTable, ErasingNonExistingElementReturnsEndIterator) {
	OrderedHashTable<std::string, Polynom> table;
	Polynom p(Monom(1, 1, 1, 1));
	table.insert("a", p);
	table.insert("f", p);
	table.insert("g", p);
	table.insert("b", p);

	auto it = table.erase("p");

	ASSERT_EQ(it, table.end());
}

TEST(OrderedHashTable, CanFind) {
	OrderedHashTable<std::string, Polynom> table;
	Polynom p(Monom(1, 1, 1, 1));
	table.insert("a", p);
	table.insert("f", p);
	table.insert("g", p);
	table.insert("b", p);

	auto it = table.find("f");
	ASSERT_EQ(it.key(), std::hash<std::string>{}("f"));
}

TEST(OrderedHashTable, FindingNonExistingElementReturnsEndIterator) {
	OrderedHashTable<std::string, Polynom> table;
	Polynom p(Monom(1, 1, 1, 1));
	table.insert("a", p);
	table.insert("f", p);
	table.insert("g", p);
	table.insert("b", p);

	auto it = table.find("p");
	ASSERT_EQ(it, table.end());
}

TEST(OrderedHashTable, CanReturnIfEmpty) {
	OrderedHashTable<std::string, Polynom> table;
	EXPECT_TRUE(table.empty());


	Polynom p(Monom(1, 1, 1, 1));
	table.insert("a", p);
	EXPECT_FALSE(table.empty());
}

TEST(OrderedHashTable, CanReturnSize) {
	OrderedHashTable<std::string, Polynom> table;
	EXPECT_EQ(table.size(), 0);

	Polynom p(Monom(1, 1, 1, 1));
	table.insert("a", p);
	EXPECT_EQ(table.size(), 1);
}

TEST(OrderedHashTable, ReturnsValueViaKeyIfExists) {
	OrderedHashTable<std::string, Polynom> table;
	Polynom p1(Monom(1, 1, 1, 1));
	Polynom p2(Monom(3, 0, 0, 0));
	table.insert("a", p1);
	table.insert("b", p2);
	bool eq = table["a"] == p1;
	EXPECT_TRUE(eq);
}

TEST(OrderedHashTable, ThrowsWhenRequestingNonExistingElement) {
	OrderedHashTable<std::string, Polynom> table;
	Polynom p1(Monom(1, 1, 1, 1));
	Polynom p2(Monom(3, 0, 0, 0));
	table.insert("a", p1);
	table.insert("b", p2);
	ASSERT_ANY_THROW(table["c"]);
}