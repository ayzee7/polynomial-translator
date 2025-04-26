#include <gtest.h>
#include "Translator.h"
#include "ord_arr.h"
#include "address_hash.h"
#include "avl_tree.h"

template <class T>
class TranslatorTest : public ::testing::Test {
public:
	using TestType = Translator<T>;
};

using TestTypes = ::testing::Types<OrderedTable<std::string, Polynom>, AVLTree<std::string, Polynom>, AddressHashTable<std::string, Polynom>>;
TYPED_TEST_CASE(TranslatorTest, TestTypes);

//	Object-oriented tests
// 
//TEST(translator_basic, can_create_translator) {
//	ASSERT_NO_THROW(Translator<OrderedTable<std::string, Polynom>> t);
//}

TYPED_TEST(TranslatorTest, can_perform_expression) {
	TestFixture::TestType t;
	ASSERT_NO_THROW(t.test_execute("1"));
}


//	Assignment operation tests
TYPED_TEST(TranslatorTest, can_create_integer_variable) {
	TestFixture::TestType t;
	t.test_execute("a=3");
	bool result = t.test_execute("a") == Polynom(Monom(3, 0, 0, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_create_multi_digit_integer_variable) {
	TestFixture::TestType t;
	t.test_execute("a=35");
	bool result = t.test_execute("a") == Polynom(Monom(35, 0, 0, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, deletes_spaces_and_tabs_correctly) {
	TestFixture::TestType t;
	t.test_execute("a\t= 3 ");
	bool result = t.test_execute("a") == Polynom(Monom(3, 0, 0, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_create_variable_with_multiple_letter_name) {
	TestFixture::TestType t;
	t.test_execute("abc= 3 ");
	bool result = t.test_execute("abc") == Polynom(Monom(3, 0, 0, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_create_float_variable) {
	TestFixture::TestType t;
	t.test_execute("a=3.0");
	bool result = t.test_execute("a") == Polynom(Monom(3.0, 0, 0, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_create_multi_digit_float_variable) {
	TestFixture::TestType t;
	t.test_execute("a=35.0");
	bool result = t.test_execute("a") == Polynom(Monom(35.0, 0, 0, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_create_float_variable_without_specified_fraction) {
	TestFixture::TestType t;
	t.test_execute("a=35.");
	bool result = t.test_execute("a") == Polynom(Monom(35., 0, 0, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, cannot_overwrite_variable_integer_value) {
	TestFixture::TestType t;
	t.test_execute("a=3");
	ASSERT_ANY_THROW(t.test_execute("a=4"));
}

TYPED_TEST(TranslatorTest, cannot_overwrite_variable_float_value) {
	TestFixture::TestType t;
	t.test_execute("a=3.");
	ASSERT_ANY_THROW(t.test_execute("a=4."));
}

TYPED_TEST(TranslatorTest, cannot_overwrite_integer_variable_with_float_value) {
	TestFixture::TestType t;
	t.test_execute("a=3");
	ASSERT_ANY_THROW(t.test_execute("a=4.5"));
}

TYPED_TEST(TranslatorTest, can_assign_variable) {
	TestFixture::TestType t;
	t.test_execute("a=1");
	t.test_execute("b=a");
	bool result = t.test_execute("a") == t.test_execute("b");
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_assign_integer_expression) {
	TestFixture::TestType t;
	t.test_execute("a=1+1");
	bool result = t.test_execute("a") == Polynom(Monom(2, 0, 0, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_assign_float_expression) {
	TestFixture::TestType t;
	t.test_execute("a=1.+1.");
	bool result = t.test_execute("a") == Polynom(Monom(2., 0, 0, 0));
	ASSERT_TRUE(result);;
}

TYPED_TEST(TranslatorTest, can_assign_expression_with_variable) {
	TestFixture::TestType t;
	t.test_execute("a=5");
	t.test_execute("b=1+a");
	bool result = t.test_execute("b") == Polynom(Monom(6, 0, 0, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_assign_expression_with_brackets) {
	TestFixture::TestType t;
	t.test_execute("a=2*(2+2)");
	bool result = t.test_execute("a") == Polynom(Monom(8, 0, 0, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_assign_expression_with_multiple_variables) {
	TestFixture::TestType t;
	t.test_execute("a=1");
	t.test_execute("b=2");
	t.test_execute("c=a+b");
	bool result = t.test_execute("c") == Polynom(Monom(3, 0, 0, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_assign_expression_with_every_operation) {
	TestFixture::TestType t;
	t.test_execute("a=2+2*2-2/2");
	bool result = t.test_execute("a") == Polynom(Monom(5, 0, 0, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_assign_expression_with_multiple_variables_and_brackets) {
	TestFixture::TestType t;
	t.test_execute("a=1");
	t.test_execute("b=2");
	t.test_execute("c=(a+b)*3");
	bool result = t.test_execute("c") == Polynom(Monom(9, 0, 0, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_assign_variable_with_alike_name) {
	TestFixture::TestType t;
	t.test_execute("ab=2");
	t.test_execute("a=ab");
	bool result = t.test_execute("a") == Polynom(Monom(2, 0, 0, 0));
	ASSERT_TRUE(result);
}


//	Calculating expression tests
TYPED_TEST(TranslatorTest, can_calculate_trivial_integer_expression) {
	TestFixture::TestType t;
	auto res = t.test_execute("1+1");
	bool result = res == Polynom(Monom(2, 0, 0, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_calculate_trivial_double_expression) {
	TestFixture::TestType t;
	auto res = t.test_execute("1.3 - 0.4");
	bool result = res == Polynom(Monom(0.9, 0, 0, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_calculate_trivial_variable_expression) {
	TestFixture::TestType t;
	t.test_execute("a=2");
	auto res = t.test_execute("a * 0.5");
	bool result = res == Polynom(Monom(1, 0, 0, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_calculate_expression_with_lower_priority_operation_in_brackets) {
	TestFixture::TestType t;
	auto res = t.test_execute("2*(2+1)");
	bool result = res == Polynom(Monom(6, 0, 0, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_calculate_expression_with_multiple_brackets) {
	TestFixture::TestType t;
	auto res = t.test_execute("2*(2/(1+1))");
	bool result = res == Polynom(Monom(2, 0, 0, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_calculate_expression_with_multiple_variables) {
	TestFixture::TestType t;
	t.test_execute("a=2");
	t.test_execute("b=5");
	auto res = t.test_execute("(a+1)*(b-2)");
	bool result = res == Polynom(Monom(9, 0, 0, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_calculate_expression_with_alike_variable_names) {
	TestFixture::TestType t;
	t.test_execute("a=2");
	t.test_execute("ab=3");
	auto res = t.test_execute("a+ab");
	bool result = res == Polynom(Monom(5, 0, 0, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, throws_when_dividing_by_zero) {
	TestFixture::TestType t;
	ASSERT_ANY_THROW(t.test_execute("0/0"));
}

TYPED_TEST(TranslatorTest, can_calculate_nested_expressions_in_brackets) {
	TestFixture::TestType t;
	auto res = t.test_execute("2*(2/(2+2))");
	bool result = res == Polynom(Monom(1, 0, 0, 0));
	ASSERT_TRUE(result);
}


//	Expression analysis tests
TYPED_TEST(TranslatorTest, assignment_throws_when_assigning_uninitialized_variable) {
	TestFixture::TestType t;
	ASSERT_ANY_THROW(t.test_execute("a=1+b"));
}

TYPED_TEST(TranslatorTest, assignment_throws_when_assigning_invalid_float_number) {
	TestFixture::TestType t;
	ASSERT_ANY_THROW(t.test_execute("a=3.3.3"));
}

TYPED_TEST(TranslatorTest, assignment_throws_when_too_many_opening_brackets) {
	TestFixture::TestType t;
	ASSERT_ANY_THROW(t.test_execute("a = ((1+1)"));
}

TYPED_TEST(TranslatorTest, assignment_throws_when_too_many_closing_brackets) {
	TestFixture::TestType t;
	ASSERT_ANY_THROW(t.test_execute("a = (1+1))"));
}

TYPED_TEST(TranslatorTest, assignment_throws_when_expression_is_empty) {
	TestFixture::TestType t;
	ASSERT_ANY_THROW(t.test_execute("a = "));
}

TYPED_TEST(TranslatorTest, assignment_throws_when_invalid_variable_name) {
	TestFixture::TestType t;
	EXPECT_ANY_THROW(t.test_execute("0a=1"));
	EXPECT_ANY_THROW(t.test_execute("%a=1"));
}

TYPED_TEST(TranslatorTest, throws_when_expression_in_brackets_is_empty) {
	TestFixture::TestType t;
	ASSERT_ANY_THROW(t.test_execute("1+()"));
}

TYPED_TEST(TranslatorTest, throws_when_expression_contains_unsupported_symbol) {
	TestFixture::TestType t;
	ASSERT_ANY_THROW(t.test_execute("1+%"));
}

TYPED_TEST(TranslatorTest, throws_when_expression_ends_with_operation_sign) {
	TestFixture::TestType t;
	EXPECT_ANY_THROW(t.test_execute("1+"));
	EXPECT_ANY_THROW(t.test_execute("1-"));
	EXPECT_ANY_THROW(t.test_execute("1/"));
}

TYPED_TEST(TranslatorTest, throws_when_closing_bracket_comes_after_operation_sign) {
	TestFixture::TestType t;
	ASSERT_ANY_THROW(t.test_execute("1+(1^)"));
}

TYPED_TEST(TranslatorTest, throws_when_meets_two_consecutive_operation_signs) {
	TestFixture::TestType t;
	ASSERT_ANY_THROW(t.test_execute("1+*"));
}
