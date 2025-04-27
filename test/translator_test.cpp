#include <gtest.h>
#include "Translator.h"
#include "ord_arr.h"
#include "unord_arr.h"
#include "address_hash.h"
#include "hash_chain.h"
#include "avl_tree.h"
#include "rb_tree.h"

template <class T>
class TranslatorTest : public ::testing::Test {
public:
	using TestType = Translator<T>;

	Polynom createPolynom(std::initializer_list<Monom> monoms) {
		Polynom p;
		for (const auto& m : monoms) {
			p = p + Polynom(m);
		}
		return p;
	}
};

using TestTypes = ::testing::Types<OrderedTable<std::string, Polynom>, UnorderedTable<std::string, Polynom>, AVLTree<std::string, Polynom>, RBTree<std::string, Polynom>, AddressHashTable<std::string, Polynom>, HashTableChaining<std::string, Polynom>>;
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

//polinom expressions test
TYPED_TEST(TranslatorTest, can_perform_polynom)
{
	TestFixture::TestType t;
	ASSERT_NO_THROW(t.test_execute("xyz"));
}

TYPED_TEST(TranslatorTest, can_parse_single_variable_x) {
	TestFixture::TestType t;
	auto res = t.test_execute("x");
	bool result = res == Polynom(Monom(1, 1, 0, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_parse_single_variable_y_with_power) {
	TestFixture::TestType t;
	auto res = t.test_execute("y^2");
	bool result = res == Polynom(Monom(1, 0, 2, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_parse_single_variable_z_with_power) {
	TestFixture::TestType t;
	auto res = t.test_execute("z^9");
	bool result = res == Polynom(Monom(1, 0, 0, 9));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_parse_variable_with_power_zero) {
	TestFixture::TestType t;
	auto res = t.test_execute("x^0");
	bool result = res == Polynom(Monom(1, 0, 0, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_parse_monom_with_integer_coefficient) {
	TestFixture::TestType t;
	auto res = t.test_execute("3x");
	bool result = res == Polynom(Monom(3, 1, 0, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_parse_monom_with_float_coefficient) {
	TestFixture::TestType t;
	auto res = t.test_execute("2.5y^3");
	bool result = res == Polynom(Monom(2.5, 0, 3, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, cant_parse_monom_with_negative_coefficient) {
	TestFixture::TestType t;
	ASSERT_ANY_THROW(t.test_execute("-4z^2"));
}

TYPED_TEST(TranslatorTest, can_parse_monom_with_multiple_variables) {
	TestFixture::TestType t;
	auto res = t.test_execute("x^2yz^3");
	bool result = res == Polynom(Monom(1, 2, 1, 3));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_parse_monom_with_coefficient_and_multiple_variables) {
	TestFixture::TestType t;
	auto res = t.test_execute("5x^1y^2z^0");
	bool result = res == Polynom(Monom(5, 1, 2, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, cant_parse_monom_with_variables_in_different_order) {
	TestFixture::TestType t;
	ASSERT_ANY_THROW(t.test_execute("zyx"));
}

TYPED_TEST(TranslatorTest, can_parse_monom_with_spaces_around_power) {
	TestFixture::TestType t;
	auto res = t.test_execute("3 x ^ 2");
	bool result = res == Polynom(Monom(3, 2, 0, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_parse_simple_polynom_addition) {
	TestFixture::TestType t;
	auto res = t.test_execute("x+y");
	Polynom expected = createPolynom({ Monom(1, 1, 0, 0), Monom(1, 0, 1, 0) });
	bool result = res == expected;
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_parse_simple_polynom_subtraction) {
	TestFixture::TestType t;
	auto res = t.test_execute("3x^2 - 2y");
	Polynom expected = createPolynom({ Monom(3, 2, 0, 0), Monom(-2, 0, 1, 0) });
	bool result = res == expected;
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_parse_polynom_with_constants) {
	TestFixture::TestType t;
	auto res = t.test_execute("x^2 + 5 - 2y");
	Polynom expected = createPolynom({ Monom(1, 2, 0, 0), Monom(-2, 0, 1, 0), Monom(5, 0, 0, 0) });
	bool result = res == expected;
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, simplifies_like_terms_addition) {
	TestFixture::TestType t;
	auto res = t.test_execute("x+x");
	bool result = res == Polynom(Monom(2, 1, 0, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, simplifies_like_terms_subtraction) {
	TestFixture::TestType t;
	auto res = t.test_execute("3x^2y - x^2y");
	bool result = res == Polynom(Monom(2, 2, 1, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, simplifies_like_terms_to_zero) {
	TestFixture::TestType t;
	auto res = t.test_execute("x-x");
	bool result = res == Polynom(Monom(0,1,0,0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, simplifies_complex_polynom) {
	TestFixture::TestType t;
	auto res = t.test_execute("2x + 3y - x + 2y^2 - y");
	Polynom expected = createPolynom({ Monom(1, 1, 0, 0), Monom(2, 0, 2, 0), Monom(2, 0, 1, 0) });
	bool result = res == expected;
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, cant_use_unary_minus_in_polynom_expressions) {
	TestFixture::TestType t;
	ASSERT_ANY_THROW(t.test_execute("-x+y"));
}


TYPED_TEST(TranslatorTest, can_add_polynoms) {
	TestFixture::TestType t;
	auto res = t.test_execute("(x+y) + x - y");
	bool result = res == createPolynom({ Monom(2, 1, 0, 0), Monom(0, 0, 1, 0) } );
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_sub_2_polynoms) {
	TestFixture::TestType t;
	auto res = t.test_execute("(x-x) + (y - y)");
	bool result = res == createPolynom({ Monom(0, 1, 0, 0), Monom(0, 0, 1, 0) });
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_substract_polynoms) {
	TestFixture::TestType t;
	auto res = t.test_execute("(x^2+2y) - (x^2-y)");
	bool result = res == createPolynom({ Monom(3, 0, 1, 0), Monom(0, 2, 0, 0) });
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_multiply_monom_by_constant) {
	TestFixture::TestType t;
	auto res = t.test_execute("3 * x^2y");
	bool result = res == Polynom(Monom(3, 2, 1, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_multiply_polynom_by_constant) {
	TestFixture::TestType t;
	auto res = t.test_execute("2 * (x+y)");
	Polynom expected = createPolynom({ Monom(2, 1, 0, 0), Monom(2, 0, 1, 0) });
	bool result = res == expected;
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_multiply_monom_by_monom) {
	TestFixture::TestType t;
	auto res = t.test_execute("(2x) * (3y^2)");
	bool result = res == Polynom(Monom(6, 1, 2, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_multiply_polynom_by_monom) {
	TestFixture::TestType t;
	auto res = t.test_execute("(x+y) * 2x");
	Polynom expected = createPolynom({ Monom(2, 2, 0, 0), Monom(2, 1, 1, 0) });
	bool result = res == expected;
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_multiply_polynom_by_polynom) {
	TestFixture::TestType t;
	auto res = t.test_execute("(x+1) * (y-2)");
	Polynom expected = createPolynom({ Monom(1, 1, 1, 0), Monom(-2, 1, 0, 0), Monom(1, 0, 1, 0), Monom(-2, 0, 0, 0) });
	bool result = res == expected;
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_multiply_polynom_by_polynom_with_simplification) {
	TestFixture::TestType t;
	auto res = t.test_execute("(x+y) * (x-y)");
	Polynom expected = createPolynom({ Monom(1, 2, 0, 0), Monom(-1, 0, 2, 0), Monom(0, 1, 1, 0) });
	bool result = res == expected;
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_divide_monom_by_constant) {
	TestFixture::TestType t;
	auto res = t.test_execute("(4x^2y) / 2");
	bool result = res == Polynom(Monom(2, 2, 1, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_divide_polynom_by_constant) {
	TestFixture::TestType t;
	auto res = t.test_execute("(2x+4y^2) / 2");
	Polynom expected = createPolynom({ Monom(1, 1, 0, 0), Monom(2, 0, 2, 0) });
	bool result = res == expected;
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, division_by_zero_polynom_throws) {
	TestFixture::TestType t;
	ASSERT_ANY_THROW(t.test_execute("x / 0"));
}

TYPED_TEST(TranslatorTest, can_assign_monom_to_variable) {
	TestFixture::TestType t;
	t.test_execute("p1 = 3x^2y");
	auto res = t.test_execute("p1");
	bool result = res == Polynom(Monom(3, 2, 1, 0));
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_assign_polynom_to_variable) {
	TestFixture::TestType t;
	t.test_execute("p2 = x - 2y^3 + 5");
	auto res = t.test_execute("p2");
	Polynom expected = createPolynom({ Monom(1, 1, 0, 0), Monom(-2, 0, 3, 0), Monom(5, 0, 0, 0) });
	bool result = res == expected;
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, cannot_overwrite_polynom_variable) {
	TestFixture::TestType t;
	t.test_execute("p = x");
	ASSERT_ANY_THROW(t.test_execute("p = y"));
}

TYPED_TEST(TranslatorTest, can_use_polynom_variable_in_expression_addition) {
	TestFixture::TestType t;
	t.test_execute("p1 = x+y");
	auto res = t.test_execute("p1 + x");
	bool result = res == createPolynom({ Monom(2, 1, 0, 0), Monom(1, 0, 1, 0) });
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_use_polynom_variable_in_expression_multiplication) {
	TestFixture::TestType t;
	t.test_execute("p1 = x+y");
	auto res = t.test_execute("p1 * 3");
	bool result = res == createPolynom({ Monom(3, 1, 0, 0), Monom(3, 0, 1, 0) });
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_use_polynom_variable_in_polynom_multiplication) {
	TestFixture::TestType t;
	t.test_execute("p1 = x+1");
	auto res = t.test_execute("p1 * y");
	bool result = res == createPolynom({ Monom(1, 1, 1, 0), Monom(1, 0, 1, 0) });
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_use_multiple_polynom_variables) {
	TestFixture::TestType t;
	t.test_execute("p1 = x+y");
	t.test_execute("p2 = x-y");
	auto res = t.test_execute("p1+p2");
	bool result = res == createPolynom({ Monom(2, 1, 0, 0), Monom(0, 0, 1, 0) });
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, can_assign_expression_with_polynom_variable) {
	TestFixture::TestType t;
	t.test_execute("p1=x");
	t.test_execute("p2=p1+y");
	auto res = t.test_execute("p2");
	bool result = res == createPolynom({ Monom(1, 1, 0, 0), Monom(1, 0, 1, 0) });
	ASSERT_TRUE(result);
}

TYPED_TEST(TranslatorTest, throws_on_invalid_power_character) {
	TestFixture::TestType t;
	ASSERT_ANY_THROW(t.test_execute("x^a"));
}

TYPED_TEST(TranslatorTest, throws_on_power_out_of_range_too_high) {
	TestFixture::TestType t;
	ASSERT_ANY_THROW(t.test_execute("x^10"));
}

TYPED_TEST(TranslatorTest, throws_on_missing_power_after_caret) {
	TestFixture::TestType t;
	ASSERT_ANY_THROW(t.test_execute("x^"));
	ASSERT_ANY_THROW(t.test_execute("x^+y"));
}

TYPED_TEST(TranslatorTest, throws_on_caret_without_variable) {
	TestFixture::TestType t;
	ASSERT_ANY_THROW(t.test_execute("^2"));
	ASSERT_ANY_THROW(t.test_execute("2+^2"));
}

TYPED_TEST(TranslatorTest, cant_use_variable_in_power_of_monom) {
	TestFixture::TestType t;
	t.test_execute("a=1");
	ASSERT_ANY_THROW(t.test_execute("x^2a"));
}

TYPED_TEST(TranslatorTest, throws_on_assigning_to_math_variable) {
	TestFixture::TestType t;
	ASSERT_ANY_THROW(t.test_execute("x = 5"));
	ASSERT_ANY_THROW(t.test_execute("y = z"));
}

TYPED_TEST(TranslatorTest, throws_on_misplaced_variable_or_number) {
	TestFixture::TestType t;
	ASSERT_ANY_THROW(t.test_execute("x 1"));
	ASSERT_ANY_THROW(t.test_execute("(x+1)y"));
}