#pragma once
#include "List.h"
#include <iostream>
#include <vector>

class Monom {

	double coef;
	int powX;
	int powY;
	int powZ;

protected:

	static int spaceship_comparator(int comp1, int comp2);

public:

	Monom();

	Monom(double coef, int powX, int powY, int powZ);

	static int compare(const Monom& first, const Monom& second);

	Monom operator+(const Monom& other);

	Monom operator-(const Monom& other);

	Monom operator*(const Monom& other);

	Monom operator*(double mult);

	Monom operator/(const Monom& other);

	Monom operator/(double mult);

	bool operator==(const Monom& other);

	bool operator!=(const Monom& other);

	friend std::ostream& operator<<(std::ostream& ostr, const Monom& m);

	double get_coeff() const;
	std::vector<int> get_value() const;

};

class Polynom {

	List<Monom> polynom;

public:

	Polynom();

	Polynom(const Monom& monom);

	Polynom(const List<Monom>& poly);

	Polynom operator+(const Polynom& other);

	Polynom operator+(const Monom& other);

	Polynom operator-(const Polynom& other);

	Polynom operator-(Monom& other);

	Polynom operator*(const Polynom& other);

	Polynom operator*(const Monom& other);

	Polynom operator*(int mult);

	Polynom operator/(const Polynom& other);

	Polynom operator/(const Monom& other);

	Polynom operator/(int mult);

	bool operator==(const Polynom& other) const;

	bool operator!=(const Polynom& other) const;

	void printout();

	int size() const;

	bool operator<(const Polynom& other) const;
	bool operator>(const Polynom& other) const;
	bool operator<=(const Polynom& other) const;
	bool operator>=(const Polynom& other) const;

	friend std::ostream& operator<<(std::ostream& ostr, const Polynom& m);
};