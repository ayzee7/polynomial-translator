#include <gtest.h>
#include <algorithm>
#include "address_hash.h"
#include "polinom.h"

//	Iterator tests

TEST(AddressHashTableIterator, CanCreateBeginAndEndIterator) {
	AddressHashTable<std::string, Polynom> table;
	EXPECT_NO_THROW(table.begin());
	EXPECT_NO_THROW(table.end());
}

TEST(AddressHashTableIterator, CanIterateThroughTableUsingIterator) {
	AddressHashTable<std::string, Polynom> table;
	ASSERT_NO_THROW(for (auto i = table.begin(); i != table.end(); ++i));
}

//	Address hash table tests

TEST(AddressHashTable, CanInsert) {
	AddressHashTable<std::string, Polynom> table;
	Polynom p(Monom(1, 1, 1, 1));
	table.insert("a", p);

	//	djb2 is used for hash function. 
	//  The corresponding hash for input "a": 177670 % 128 (default hash table size)
	//  final index value equals 6
	auto it = table[6];
	ASSERT_EQ(it.key(), "a");
}

TEST(AddressHashTable, CanInsertOnCollision) {
	AddressHashTable<std::string, Polynom> table;
	Polynom p(Monom(1, 1, 1, 1));
	table.insert("ac", p);
	table.insert("bB", p);

	// Inputs "ac" and "bB" return same hash value 41. 
	// Checking element by index 41 and then checking if second element exists in table 
	auto it = table[41];
	EXPECT_EQ(it.key(), "ac");
	auto it2 = table.find("bB");
	EXPECT_EQ(it2.key(), "bB");
}

TEST(AddressHashTable, ThrowsWhenInsertingExistingElement) {
	AddressHashTable<std::string, Polynom> table;
	Polynom p(Monom(1, 1, 1, 1));
	table.insert("a", p);
	ASSERT_ANY_THROW(table.insert("a", p));
}

TEST(AddressHashTable, RepacksWhenAlmostFull) {
	AddressHashTable<std::string, Polynom> table(4);
	Polynom p(Monom(1, 1, 1, 1));
	table.insert("a", p);
	table.insert("b", p);
	table.insert("c", p);
	table.insert("d", p);
	ASSERT_NE(table.insert("e", p), table.end());
}

TEST(AddressHashTable, CanErase) {
	AddressHashTable<std::string, Polynom> table;
	Polynom p(Monom(1, 1, 1, 1));
	table.insert("a", p);

	table.erase("a");
	ASSERT_EQ(table.find("a"), table.end());
}

TEST(AddressHashTable, ErasingNonExistingElementReturnsEndIterator) {
	AddressHashTable<std::string, Polynom> table;
	Polynom p(Monom(1, 1, 1, 1));

	auto it = table.erase("p");

	ASSERT_EQ(it, table.end());
}

TEST(AddressHashTable, CanFind) {
	AddressHashTable<std::string, Polynom> table;
	Polynom p(Monom(1, 1, 1, 1));
	table.insert("a", p);
	table.insert("f", p);
	table.insert("g", p);
	table.insert("b", p);

	auto it = table.find("f");
	ASSERT_EQ(it.key(), "f");
}

TEST(AddressHashTable, FindingNonExistingElementReturnsEndIterator) {
	AddressHashTable<std::string, Polynom> table;
	Polynom p(Monom(1, 1, 1, 1));
	table.insert("a", p);
	table.insert("f", p);
	table.insert("g", p);
	table.insert("b", p);

	auto it = table.find("p");
	ASSERT_EQ(it, table.end());
}

TEST(AddressHashTable, CanFindCollidingElementAfterErasingFirstOne) {
	AddressHashTable<std::string, Polynom> table;
	Polynom p(Monom(1, 1, 1, 1));
	table.insert("ac", p);
	table.insert("bB", p);
	table.erase("ac");

	auto it = table.find("bB");
	ASSERT_EQ(it.key(), "bB");
}

TEST(AddressHashTable, CanReturnIfEmpty) {
	AddressHashTable<std::string, Polynom> table;
	EXPECT_TRUE(table.empty());


	Polynom p(Monom(1, 1, 1, 1));
	table.insert("a", p);
	EXPECT_FALSE(table.empty());
}

TEST(AddressHashTable, CanReturnSize) {
	AddressHashTable<std::string, Polynom> table;
	EXPECT_EQ(table.size(), 0);

	Polynom p(Monom(1, 1, 1, 1));
	table.insert("a", p);
	EXPECT_EQ(table.size(), 1);
}

TEST(AddressHashTable, ReturnsValueViaKeyIfExists) {
	AddressHashTable<std::string, Polynom> table;
	Polynom p1(Monom(1, 1, 1, 1));
	Polynom p2(Monom(3, 0, 0, 0));
	table.insert("a", p1);
	table.insert("b", p2);
	bool eq = table["a"] == p1;
	EXPECT_TRUE(eq);
}

TEST(AddressHashTable, ThrowsWhenRequestingNonExistingElement) {
	AddressHashTable<std::string, Polynom> table;
	Polynom p1(Monom(1, 1, 1, 1));
	Polynom p2(Monom(3, 0, 0, 0));
	table.insert("a", p1);
	table.insert("b", p2);
	ASSERT_ANY_THROW(table["c"]);
}