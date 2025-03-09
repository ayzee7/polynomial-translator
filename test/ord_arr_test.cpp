#include <gtest.h>
#include "ord_arr.h"
#include "polinom.h"

//	Iterator tests

TEST(OrderedTableIterator, CanCreateBeginAndEndIterator) {
	OrderedTable<std::string, Polynom> table;
	EXPECT_NO_THROW(table.begin());
	EXPECT_NO_THROW(table.end());
}

TEST(OrderedTableIterator, CanIterateThroughTableUsingIterator) {
	OrderedTable<std::string, Polynom> table;
	ASSERT_NO_THROW(for (auto i = table.begin(); i != table.end(); ++i));
}

//	Ordered table tests

TEST(OrderedTable, CanInsert) {
	OrderedTable<std::string, Polynom> table;
	Polynom p(Monom(1, 1, 1, 1));
	table.insert("a", p);
	table.insert("f", p);
	table.insert("g", p);
	table.insert("b", p);

	std::vector<std::string> table_exp;
	table_exp.push_back("a");
	table_exp.push_back("b");
	table_exp.push_back("f");
	table_exp.push_back("g");

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

TEST(OrderedTable, ThrowsWhenInsertingExistingElement) {
	OrderedTable<std::string, Polynom> table;
	Polynom p(Monom(1, 1, 1, 1));
	table.insert("a", p);
	ASSERT_ANY_THROW(table.insert("a", p));
}

TEST(OrderedTable, CanErase) {
	OrderedTable<std::string, Polynom> table;
	Polynom p(Monom(1, 1, 1, 1));
	table.insert("a", p);
	table.insert("f", p);
	table.insert("g", p);
	table.insert("b", p);

	table.erase("a");
	table.erase("f");
	table.erase("g");

	std::vector<std::string> table_exp;
	table_exp.push_back("b");

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

TEST(OrderedTable, ErasingNonExistingElementReturnsEndIterator) {
	OrderedTable<std::string, Polynom> table;
	Polynom p(Monom(1, 1, 1, 1));
	table.insert("a", p);
	table.insert("f", p);
	table.insert("g", p);
	table.insert("b", p);

	auto it = table.erase("p");
	
	ASSERT_EQ(it, table.end());
}

TEST(OrderedTable, CanFind) {
	OrderedTable<std::string, Polynom> table;
	Polynom p(Monom(1, 1, 1, 1));
	table.insert("a", p);
	table.insert("f", p);
	table.insert("g", p);
	table.insert("b", p);

	auto it = table.find("f");
	ASSERT_EQ(it.key(), "f");
}

TEST(OrderedTable, FindingNonExistingElementReturnsEndIterator) {
	OrderedTable<std::string, Polynom> table;
	Polynom p(Monom(1, 1, 1, 1));
	table.insert("a", p);
	table.insert("f", p);
	table.insert("g", p);
	table.insert("b", p);

	auto it = table.find("p");
	ASSERT_EQ(it, table.end());
}

TEST(OrderedTable, CanReturnIfEmpty) {
	OrderedTable<std::string, Polynom> table;
	EXPECT_TRUE(table.empty());


	Polynom p(Monom(1, 1, 1, 1));
	table.insert("a", p);
	EXPECT_FALSE(table.empty());
}

TEST(OrderedTable, CanReturnSize) {
	OrderedTable<std::string, Polynom> table;
	EXPECT_EQ(table.size(), 0);

	Polynom p(Monom(1, 1, 1, 1));
	table.insert("a", p);
	EXPECT_EQ(table.size(), 1);
}

TEST(OrderedTable, ReturnsValueViaKeyIfExists) {
	OrderedTable<std::string, Polynom> table;
	Polynom p1(Monom(1, 1, 1, 1));
	Polynom p2(Monom(3, 0, 0, 0));
	table.insert("a", p1);
	table.insert("b", p2);
	bool eq = table["a"] == p1;
	EXPECT_TRUE(eq);
}

TEST(OrderedTable, ThrowsWhenRequestingNonExistingElement) {
	OrderedTable<std::string, Polynom> table;
	Polynom p1(Monom(1, 1, 1, 1));
	Polynom p2(Monom(3, 0, 0, 0));
	table.insert("a", p1);
	table.insert("b", p2);
	ASSERT_ANY_THROW(table["c"]);
}