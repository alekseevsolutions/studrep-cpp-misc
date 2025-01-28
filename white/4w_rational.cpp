#include <iostream>
#include <numeric>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <stdexcept>
using namespace std;


int get_nod(int a, int b){
	a = abs(a);
	b = abs(b);
	while (a > 0 && b > 0) {
		if (a > b) {
			a %= b;
		} else {
			b %= a;
		}
	}
	return a + b;
}


class Rational {
public:
	Rational() {
		numerator = 0;
		denominator = 1;
	}

	Rational(int new_numerator, int new_denominator) {
		if (new_denominator ==  0) {
			throw invalid_argument("denominator == 0");
		}
		int nod = get_nod(new_numerator, new_denominator);
		numerator = new_numerator / nod;
		denominator = new_denominator / nod;

		if (denominator < 0) {
			denominator = -denominator;
			numerator = -numerator;
		}
	}

	int Numerator() const {
		return numerator;
	}

	int Denominator() const {
		return denominator;
	}

private:
	int numerator;
	int denominator;
};

Rational operator+(const Rational& r1, const Rational& r2) {
	if (r1.Denominator() == r2.Denominator()) {
		return {r1.Numerator() + r2.Numerator(), r2.Denominator()};
	} else {
		return {r1.Numerator() * r2.Denominator() + r2.Numerator() * r1.Denominator(),
				r1.Denominator() * r2.Denominator()};
	}
}

Rational operator-(const Rational& r1, const Rational& r2) {
	if (r1.Denominator() == r2.Denominator()) {
		return {r1.Numerator() - r2.Numerator(), r2.Denominator()};
	} else {
		return {r1.Numerator() * r2.Denominator() - r2.Numerator() * r1.Denominator(),
				r1.Denominator() * r2.Denominator()};
	}
}

bool operator==(const Rational& r1, const Rational& r2) {
	return r1.Denominator() == r2.Denominator() && r1.Numerator() == r2.Numerator();
}

Rational operator*(const Rational& r1, const Rational& r2) {
	return {r1.Numerator() * r2.Numerator(), r1.Denominator() * r2.Denominator()};
}

Rational operator/(const Rational& r1, const Rational& r2) {
	if (r2.Numerator() == 0) {
		throw domain_error("Division by zero");
	}
	return {r1.Numerator() * r2.Denominator(), r2.Numerator() * r1.Denominator()};
}

bool operator<(const Rational& r1, const Rational& r2) {
	return r1.Numerator() * r2.Denominator() < r2.Numerator() * r1.Denominator();
}

bool operator>(const Rational& r1, const Rational& r2) {
	return r1.Numerator() * r2.Denominator() > r2.Numerator() * r1.Denominator();
}

istream& operator>>(istream& stream, Rational& r){
	int numerator, denominator;
	char dlm;
	if (stream) {
		stream >> numerator >> dlm >> denominator;
		if (stream) {
			if (dlm == '/') {
				r = Rational(numerator, denominator);
			}
			else {
				stream.setstate(ios_base::failbit);
			}
		}
	}
	return stream;
}

ostream& operator<<(ostream& stream, const Rational& r){
	return stream << r.Numerator() << "/" << r.Denominator();
}

int main() {
	Rational r1, r2;
	char sign;

	try {
		cin >> r1 >> sign >> r2;
	} catch (invalid_argument&){
		cout << "Invalid argument" << endl;
		return 1;
	}

	if (sign == '+') {
		cout << r1 + r2 << endl;
	} else if (sign == '-') {
		cout << r1 - r2 << endl;
	} else if (sign == '*') {
		cout << r1 * r2 << endl;
	} else {
		try {
			cout << r1 / r2 << endl;
		} catch (domain_error&) {
			cout << "Division by zero" << endl;
			return 2;
		}
	}

	return 0;
}
