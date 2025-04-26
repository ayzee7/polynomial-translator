//#pragma once
#ifndef POLYNOM_H
#define POLYNOM_H

#include "List.h"
#include <iostream>

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

	double get_coef();

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

	int size();
};

#endif