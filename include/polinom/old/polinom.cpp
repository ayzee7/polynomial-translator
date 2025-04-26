#include "polinom.h"


int Monom::spaceship_comparator(int comp1, int comp2) {
	if (comp1 < comp2) {
		return -1;
	}
	else if (comp1 > comp2) {
		return 1;
	}
	else {
		return 0;
	}
}

int Monom::compare(const Monom& first, const Monom& second) {
	int pows[] = { first.powX, first.powY, first.powZ };
	int other_pows[] = { second.powX, second.powY, second.powZ };
	for (int i = 0; i < 3; i++) {
		int comp_res = spaceship_comparator(pows[i], other_pows[i]);
		if (comp_res) {
			return comp_res;
		}
	}
	return 0;
}

Monom::Monom() {}

Monom::Monom(double coef, int powX, int powY, int powZ) {
	if (powX < 0 || powX > 9) {
		throw "invalid x power value";
	}
	if (powY < 0 || powY > 9) {
		throw "invalid y power value";
	}
	if (powZ < 0 || powZ > 9) {
		throw "invalid z power value";
	}
	this->coef = coef;
	this->powX = powX;
	this->powY = powY;
	this->powZ = powZ;
}

Monom Monom::operator+(const Monom& other) {
	Monom res = *this;
	if (compare(*this, other)) {
		throw "invalid operation";
	}
	else res.coef += other.coef;
	return res;
}

Monom Monom::operator-(const Monom& other) {
	Monom res = *this;
	if (compare(*this, other)) {
		throw "invalid operation";
	}
	else res.coef -= other.coef;
	return res;
}

Monom Monom::operator*(const Monom& other) {
	Monom res = *this;
	res.coef *= other.coef;
	res.powX += other.powX;
	if (res.powX < 0 || res.powX > 9) {
		throw "x power overflow";
	}
	res.powY += other.powY;
	if (res.powY < 0 || res.powY > 9) {
		throw "y power overflow";
	}
	res.powZ += other.powZ;
	if (res.powZ < 0 || res.powZ > 9) {
		throw "z power overflow";
	}
	return res;
}

Monom Monom::operator*(double mult) {
	Monom res = *this;
	res.coef *= mult;
	return res;
}

Monom Monom::operator/(const Monom& other) {
	Monom res = *this;
	res.coef /= other.coef;
	res.powX -= other.powX;
	if (res.powX < 0 || res.powX > 9) {
		throw "x power overflow";
	}
	res.powY -= other.powY;
	if (res.powY < 0 || res.powY > 9) {
		throw "y power overflow";
	}
	res.powZ -= other.powZ;
	if (res.powZ < 0 || res.powZ > 9) {
		throw "z power overflow";
	}
	return res;
}

Monom Monom::operator/(double mult) {
	Monom res = *this;
	res.coef /= mult;
	return res;
}

bool Monom::operator==(const Monom& other) {
	if (!compare(*this, other) && coef == other.coef) {
		return true;
	}
	else return false;
}

bool Monom::operator!=(const Monom& other) {
	return !(*this == other);
}

std::ostream& operator<<(std::ostream& ostr, const Monom& m) {
	ostr << m.coef << "x^" << m.powX << "y^" << m.powY << "z^" << m.powZ;
	return ostr;
}


Polynom::Polynom() {}

Polynom::Polynom(const Monom& monom) {
	polynom.insert_front(monom);
}

Polynom::Polynom(const List<Monom>& poly) {
	polynom = poly;
}

Polynom Polynom::operator+(const Polynom& other) {
	Polynom *res = new Polynom();
	res->polynom.insert_front(Monom());
	auto res_ptr = res->polynom.begin();
	auto ptr1 = polynom.begin(), ptr2 = other.polynom.begin();
	for (; ptr1 != polynom.end() && ptr2 != other.polynom.end(); ++res_ptr) {
		int comp_res = Monom::compare(ptr1.value(), ptr2.value());
		switch (comp_res) {
		case 1:
			res->polynom.insert_after(ptr1.value(), res_ptr);
			++ptr1;
			break;
		case 0:
			res->polynom.insert_after(ptr1.value() + ptr2.value(), res_ptr);
			++ptr1;
			++ptr2;
			break;
		case -1:
			res->polynom.insert_after(ptr2.value(), res_ptr);
			++ptr2;
			break;
		}
	}
	for (; ptr1 != polynom.end(); ++ptr1, ++res_ptr) {
		res->polynom.insert_after(ptr1.value(), res_ptr);
	}
	for (; ptr2 != polynom.end(); ++ptr2, ++res_ptr) {
		res->polynom.insert_after(ptr2.value(), res_ptr);
	}

	res->polynom.erase_front();
	return *res;
}

Polynom Polynom::operator+(const Monom& other) {
	Polynom *res = new Polynom();
	res->polynom.insert_front(Monom());
	auto res_ptr = res->polynom.begin();
	auto ptr = polynom.begin();
	bool isDone = false;
	for (; ptr != polynom.end();++res_ptr) {
		if (isDone) break;
		int comp_res = Monom::compare(ptr.value(), other);
		switch (comp_res) {
		case 1:
			res->polynom.insert_after(ptr.value(), res_ptr);
			++ptr;
			break;
		case 0:
			res->polynom.insert_after(ptr.value() + other, res_ptr);
			++ptr;
			isDone = true;
			break;
		case -1:
			res->polynom.insert_after(other, res_ptr);
			isDone = true;
			break;
		}
	}
	if (!isDone) {
		res->polynom.insert_after(other, res_ptr);
	}
	for (; ptr != polynom.end(); ++ptr, ++res_ptr) {
		res->polynom.insert_after(ptr.value(), res_ptr);
	}
	
	res->polynom.erase_front();
	return *res;
}

Polynom Polynom::operator-(const Polynom& other) {
	Polynom* res = new Polynom();
	res->polynom.insert_front(Monom());
	auto res_ptr = res->polynom.begin();
	auto ptr1 = polynom.begin(), ptr2 = other.polynom.begin();
	for (; ptr1 != polynom.end() && ptr2 != other.polynom.end(); ++res_ptr) {
		int comp_res = Monom::compare(ptr1.value(), ptr2.value());
		switch (comp_res) {
		case 1:
			res->polynom.insert_after(ptr1.value(), res_ptr);
			++ptr1;
			break;
		case 0:
			res->polynom.insert_after(ptr1.value() - ptr2.value(), res_ptr);
			++ptr1;
			++ptr2;
			break;
		case -1:
			res->polynom.insert_after(ptr2.value() * -1, res_ptr);
			++ptr2;
			break;
		}
	}
	for (; ptr1 != polynom.end(); ++ptr1, ++res_ptr) {
		res->polynom.insert_after(ptr1.value(), res_ptr);
	}
	for (; ptr2 != polynom.end(); ++ptr2, ++res_ptr) {
		res->polynom.insert_after(ptr2.value() * -1, res_ptr);
	}

	res->polynom.erase_front();
	return *res;
}

Polynom Polynom::operator-(Monom& other) {
	Polynom* res = new Polynom();
	res->polynom.insert_front(Monom());
	auto res_ptr = res->polynom.begin();
	auto ptr = polynom.begin();
	bool isDone = false;
	for (; ptr != polynom.end(); ++res_ptr) {
		if (isDone) break;
		int comp_res = Monom::compare(ptr.value(), other);
		switch (comp_res) {
		case 1:
			res->polynom.insert_after(ptr.value(), res_ptr);
			++ptr;
			break;
		case 0:
			res->polynom.insert_after(ptr.value() - other, res_ptr);
			++ptr;
			isDone = true;
			break;
		case -1:
			res->polynom.insert_after(other * -1, res_ptr);
			isDone = true;
			break;
		}
	}
	if (!isDone) {
		res->polynom.insert_after(other * -1, res_ptr);
	}
	for (; ptr != polynom.end(); ++ptr, ++res_ptr) {
		res->polynom.insert_after(ptr.value(), res_ptr);
	}

	res->polynom.erase_front();
	return *res;
}

Polynom Polynom::operator*(const Polynom& other) {
	Polynom* res_sum = new Polynom();
	for (auto ptr1 = polynom.begin(); ptr1 != polynom.end(); ++ptr1) {
		Polynom res;
		res.polynom.insert_front(Monom());
		auto res_ptr = res.polynom.begin();
		for (auto ptr2 = other.polynom.begin(); ptr2 != other.polynom.end(); ++ptr2, ++res_ptr) {
			res.polynom.insert_after(ptr1.value() * ptr2.value(), res_ptr);
		}
		res.polynom.erase_front();
		*res_sum = *res_sum + res;
	}
	return *res_sum;
}

Polynom Polynom::operator*(const Monom& other) {
	Polynom *res = new Polynom();
	res->polynom.insert_front(Monom());
	auto res_ptr = res->polynom.begin();
	for (auto ptr = polynom.begin(); ptr != polynom.end(); ++ptr, ++res_ptr) {
		res->polynom.insert_after(ptr.value() * other, res_ptr);
	}
	res->polynom.erase_front();
	return *res;
}
	
Polynom Polynom::operator*(int mult) {
	Polynom *res = new Polynom();
	res->polynom.insert_front(Monom());
	auto res_ptr = res->polynom.begin();
	for (auto ptr = polynom.begin(); ptr != polynom.end(); ++ptr, ++res_ptr) {
		res->polynom.insert_after(ptr.value() * mult, res_ptr);
	}
	res->polynom.erase_front();
	return *res;
}

Polynom Polynom::operator/(const Polynom& other) {
	Polynom* res_sum = new Polynom();
	for (auto ptr1 = polynom.begin(); ptr1 != polynom.end(); ++ptr1) {
		Polynom res;
		res.polynom.insert_front(Monom());
		auto res_ptr = res.polynom.begin();
		for (auto ptr2 = other.polynom.begin(); ptr2 != other.polynom.end(); ++ptr2, ++res_ptr) {
			res.polynom.insert_after(ptr1.value() / ptr2.value(), res_ptr);
		}
		res.polynom.erase_front();
		*res_sum = *res_sum + res;
	}
	return *res_sum;
}

Polynom Polynom::operator/(const Monom& other) {
	Polynom* res = new Polynom();
	res->polynom.insert_front(Monom());
	auto res_ptr = res->polynom.begin();
	for (auto ptr = polynom.begin(); ptr != polynom.end(); ++ptr, ++res_ptr) {
		res->polynom.insert_after(ptr.value() / other, res_ptr);
	}
	res->polynom.erase_front();
	return *res;
}

Polynom Polynom::operator/(int mult) {
	Polynom* res = new Polynom();
	res->polynom.insert_front(Monom());
	auto res_ptr = res->polynom.begin();
	for (auto ptr = polynom.begin(); ptr != polynom.end(); ++ptr, ++res_ptr) {
		res->polynom.insert_after(ptr.value() / mult, res_ptr);
	}
	res->polynom.erase_front();
	return *res;
}

bool Polynom::operator==(const Polynom& other) {
	if (polynom.size() != other.polynom.size()) {
		return false;
	}
	auto ptr1 = polynom.begin();
	auto ptr2 = other.polynom.begin();
	for (; ptr1 != polynom.end(), ptr2 != other.polynom.end(); ++ptr1, ++ptr2) {
		if (ptr1.value() != ptr2.value()) {
			return false;
		}
	}
	return true;
}

bool Polynom::operator!=(const Polynom& other) {
	return !(*this == other);
}

void Polynom::printout() {
	polynom.print();
}

int Polynom::size() {
	return polynom.size();
}