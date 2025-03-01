#include <gtest.h>
#include "polinom.h"

//	Monom class tests

TEST(monom, CanCreateEmptyMonom) {
	ASSERT_NO_THROW(Monom m);
}

TEST(monom, CanCreateGivenMonom) {
	ASSERT_NO_THROW(Monom m(1, 1, 1, 1));
}

TEST(monom, ThrowsWhenGivenInvalidValues) {
	EXPECT_ANY_THROW(Monom m(0, 0, -1, 0));
	EXPECT_ANY_THROW(Monom m(0, 11, 0, 0));
}

TEST(monom, CanCopyFromGiven) {
	Monom m(1, 1, 1, 1);
	Monom m1(m);
	ASSERT_TRUE(m == m1);
}

TEST(monom, CanAssignGiven) {
	Monom m(1, 1, 1, 1);
	Monom m1 = m;
	ASSERT_TRUE(m == m1);
}

TEST(monom, CanSum) {
	Monom m1(1, 1, 1, 1);
	Monom m2(3, 1, 1, 1);
	Monom m_exp(4, 1, 1, 1);

	Monom m = m1 + m2;

	ASSERT_TRUE(m == m_exp);
}

TEST(monom, CannotSumWithoutEqualPowers) {
	Monom m1(1, 1, 1, 1);
	Monom m2(3, 2, 1, 1);
	ASSERT_ANY_THROW(m1 + m2);
}

TEST(monom, CanSubtract) {
	Monom m1(1, 1, 1, 1);
	Monom m2(3, 1, 1, 1);
	Monom m_exp(-2, 1, 1, 1);

	Monom m = m1 - m2;

	ASSERT_TRUE(m == m_exp);
}

TEST(monom, CannotSubtractWithoutEqualPowers) {
	Monom m1(1, 1, 1, 1);
	Monom m2(3, 2, 1, 1);
	ASSERT_ANY_THROW(m1 - m2);
}

TEST(monom, CanMultiplyByMonom) {
	Monom m1(1, 2, 1, 2);
	Monom m2(3, 3, 2, 1);
	Monom m_exp(3, 5, 3, 3);

	Monom m = m1 * m2;

	ASSERT_TRUE(m == m_exp);
}

TEST(monom, CanMultiplyByInteger) {
	Monom m1(1, 2, 1, 2);
	int mult = 10;
	Monom m_exp(10, 2, 1, 2);

	Monom m = m1 * mult;

	ASSERT_TRUE(m == m_exp);
}

//	Polynom class tests

TEST(polynom, CanCreateEmptyPolynom) {
	ASSERT_NO_THROW(Polynom p);
}

TEST(polynom, CanCreatePolynomFromMonom) {
	Monom m(1, 1, 1, 1);
	ASSERT_NO_THROW(Polynom p(m));
}

TEST(polynom, CanCopyFromGiven) {
	Monom m(1, 1, 1, 1);
	Polynom p1(m);
	Polynom p2(p1);
	ASSERT_TRUE(p1 == p2);
}

TEST(polynom, CanAssignGiven) {
	Monom m(1, 1, 1, 1);
	Polynom p1(m);
	Polynom p2 = p1;
	ASSERT_TRUE(p1 == p2);
}

TEST(polynom, CanSumMonomWithEqualPowers) {
	List<Monom> ms;
	ms.insert_front(Monom(1, 1, 1, 1));
	ms.insert_front(Monom(3, 2, 1, 1));
	Polynom p(ms);
	Polynom p_sum = p + Monom(4, 1, 1, 1);

	ms.clear();
	ms.insert_front(Monom(5, 1, 1, 1));
	ms.insert_front(Monom(3, 2, 1, 1));
	Polynom p_exp(ms);
	ASSERT_TRUE(p_sum == p_exp);
}

TEST(polynom, CanSumMonomWithoutEqualPowers) {
	List<Monom> ms;
	ms.insert_front(Monom(1, 1, 1, 1));
	ms.insert_front(Monom(3, 2, 1, 1));
	Polynom p(ms);
	Polynom p_sum = p + Monom(4, 1, 2, 1);

	ms.clear();
	ms.insert_front(Monom(1, 1, 1, 1));
	ms.insert_front(Monom(4, 1, 2, 1));
	ms.insert_front(Monom(3, 2, 1, 1));
	Polynom p_exp(ms);
	ASSERT_TRUE(p_sum == p_exp);
}

TEST(polynom, CanSubtractMonomWithEqualPowers) {
	List<Monom> ms;
	ms.insert_front(Monom(1, 1, 1, 1));
	ms.insert_front(Monom(3, 2, 1, 1));
	Polynom p(ms);
	Polynom p_sum = p - Monom(4, 1, 1, 1);

	ms.clear();
	ms.insert_front(Monom(-3, 1, 1, 1));
	ms.insert_front(Monom(3, 2, 1, 1));
	Polynom p_exp(ms);
	ASSERT_TRUE(p_sum == p_exp);
}

TEST(polynom, CanSubtractMonomWithoutEqualPowers) {
	List<Monom> ms;
	ms.insert_front(Monom(1, 1, 1, 1));
	ms.insert_front(Monom(3, 2, 1, 1));
	Polynom p(ms);
	Polynom p_sum = p - Monom(4, 1, 2, 1);

	ms.clear();
	ms.insert_front(Monom(1, 1, 1, 1));
	ms.insert_front(Monom(-4, 1, 2, 1));
	ms.insert_front(Monom(3, 2, 1, 1));
	Polynom p_exp(ms);
	ASSERT_TRUE(p_sum == p_exp);
}

TEST(polynom, CanMultiplyByMonom) {
	List<Monom> ms;
	ms.insert_front(Monom(1, 1, 1, 1));
	ms.insert_front(Monom(3, 2, 1, 1));
	Polynom p(ms);
	Polynom p_sum = p * Monom(4, 1, 2, 1);

	ms.clear();
	ms.insert_front(Monom(4, 2, 3, 2));
	ms.insert_front(Monom(12, 3, 3, 2));
	Polynom p_exp(ms);
	ASSERT_TRUE(p_sum == p_exp);
}

TEST(polynom, CanSumPolynom) {
	List<Monom> ms1;
	ms1.insert_front(Monom(1, 1, 1, 1));
	ms1.insert_front(Monom(2, 2, 1, 1));
	Polynom p1(ms1);

	List<Monom> ms2;
	ms2.insert_front(Monom(2, 1, 1, 1));
	ms2.insert_front(Monom(1, 1, 2, 1));
	Polynom p2(ms2);

	List<Monom> ms_exp;
	ms_exp.insert_front(Monom(3, 1, 1, 1));
	ms_exp.insert_front(Monom(1, 1, 2, 1));
	ms_exp.insert_front(Monom(2, 2, 1, 1));
	Polynom p_exp(ms_exp);

	Polynom p_act = p1 + p2;
	ASSERT_TRUE(p_act == p_exp);
}

TEST(polynom, CanSubtractPolynom) {
	List<Monom> ms1;
	ms1.insert_front(Monom(1, 1, 1, 1));
	ms1.insert_front(Monom(2, 2, 1, 1));
	Polynom p1(ms1);

	List<Monom> ms2;
	ms2.insert_front(Monom(2, 1, 1, 1));
	ms2.insert_front(Monom(1, 1, 2, 1));
	Polynom p2(ms2);

	List<Monom> ms_exp;
	ms_exp.insert_front(Monom(-1, 1, 1, 1));
	ms_exp.insert_front(Monom(-1, 1, 2, 1));
	ms_exp.insert_front(Monom(2, 2, 1, 1));
	Polynom p_exp(ms_exp);

	Polynom p_act = p1 - p2;
	ASSERT_TRUE(p_act == p_exp);
}

TEST(polynom, CanMultiplyByPolynom) {
	List<Monom> ms1;
	ms1.insert_front(Monom(1, 1, 1, 1));
	ms1.insert_front(Monom(2, 2, 1, 1));
	Polynom p1(ms1);

	List<Monom> ms2;
	ms2.insert_front(Monom(2, 1, 1, 1));
	ms2.insert_front(Monom(1, 1, 2, 1));
	Polynom p2(ms2);

	List<Monom> ms_exp;
	ms_exp.insert_front(Monom(2, 2, 2, 2));
	ms_exp.insert_front(Monom(1, 2, 3, 2));
	ms_exp.insert_front(Monom(4, 3, 2, 2));
	ms_exp.insert_front(Monom(2, 3, 3, 2));
	Polynom p_exp(ms_exp);

	Polynom p_act = p1 * p2;
	ASSERT_TRUE(p_act == p_exp);
}

TEST(polynom, CanMultiplyByInteger) {
	List<Monom> ms1;
	ms1.insert_front(Monom(1, 1, 1, 1));
	ms1.insert_front(Monom(2, 2, 1, 1));
	Polynom p1(ms1);

	List<Monom> ms_exp;
	ms_exp.insert_front(Monom(10, 1, 1, 1));
	ms_exp.insert_front(Monom(20, 2, 1, 1));
	Polynom p_exp(ms_exp);

	Polynom p_act = p1 * 10;
	ASSERT_TRUE(p_act == p_exp);
}