#pragma once
#include "List.h"
#include <iostream>

class Monom {

	int coef;
	int powX;
	int powY;
	int powZ;

protected:

	static int spaceship_comparator(int comp1, int comp2);

public:

	Monom();

	Monom(int coef, int powX, int powY, int powZ);

	static int compare(const Monom& first, const Monom& second);

	Monom operator+(const Monom& other);

	Monom operator-(const Monom& other);

	Monom operator*(const Monom& other);

	Monom operator*(int mult);

	bool operator==(const Monom& other);

	bool operator!=(const Monom& other);

	friend std::ostream& operator<<(std::ostream& ostr, const Monom& m);

};

class Polynom {

	List<Monom> polynom;

public:

	Polynom();

	Polynom(const Monom& monom);

	Polynom(const List<Monom>& poly);

	Polynom operator+(Polynom& other);

	Polynom operator+(const Monom& other);

	Polynom operator-(Polynom& other);

	Polynom operator-(Monom& other);

	Polynom operator*(Polynom& other);

	Polynom operator*(const Monom& other);

	Polynom operator*(int mult);

	bool operator==(Polynom& other);

	bool operator!=(Polynom& other);

	void printout();

	int size();
};