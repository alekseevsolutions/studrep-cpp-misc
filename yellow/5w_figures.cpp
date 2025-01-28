#include <iostream>
#include <utility>
#include <cmath>
#include <memory>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

const double PI = 3.14;

class Figure {
public:
	explicit Figure(const string &type)
			: type_(type) {}

	virtual string Name() const = 0;

	virtual double Perimeter() const = 0;

	virtual double Area() const = 0;

	const string type_;
};

class Triangle : public Figure {
public:
	explicit Triangle(const int &a,  const int &b,  const int &c)
			: Figure("TRIANGLE"),
			  a_(a),
			  b_(b),
			  c_(c) {}

	string Name() const override {
		return type_;
	}

	double Perimeter() const override {
		return a_ + b_ + c_;
	}

	double Area() const override {
		const double pp = Perimeter()/2;
		return sqrt(pp * (pp - a_)* (pp - b_) * (pp - c_));
	}
private:
	const int a_, b_, c_;
};

class Rect : public Figure {
public:
	explicit Rect(const int &width,  const int &height)
			: Figure("RECT"),
			  width_(width),
			  height_(height) {}

	string Name() const override {
		return type_;
	}

	double Perimeter() const override {
		return (width_ + height_) * 2;
	}

	double Area() const override {
		return width_ * height_;
	}
private:
	const int width_, height_;
};

class Circle : public Figure {
public:
	explicit Circle(const int &r)
			: Figure("CIRCLE"),
			  r_(r) {}

	string Name() const override {
		return type_;
	}

	double Perimeter() const override {
		return 2 * PI * r_;
	}

	double Area() const override {
		return PI * r_ * r_;
	}
private:
	const int r_;
};

shared_ptr<Figure> CreateFigure(istream& is) {
	string type;
	getline(is, type, ' ');

	if (type == "RECT") {
		int width, height;
		is >> width >> height;
		return make_shared<Rect>(width, height);
	} else if (type == "TRIANGLE") {
		int a, b, c;
		is >> a >> b >> c;
		return make_shared<Triangle>(a, b, c);
	} else if (type == "CIRCLE") {
		int r;
		is >> r;
		return make_shared<Circle>(r);
	}

	return 0;
}


int main() {
	vector<shared_ptr<Figure>> figures;
	for (string line; getline(cin, line); ) {
		istringstream is(line);

		string command;
		is >> command;
		if (command == "ADD") {
			// Пропускаем "лишние" ведущие пробелы.
			// Подробнее об std::ws можно узнать здесь:
			// https://en.cppreference.com/w/cpp/io/manip/ws
			is >> ws;
			figures.push_back(CreateFigure(is));
		} else if (command == "PRINT") {
			for (const auto& current_figure : figures) {
				cout << fixed << setprecision(3)
					 << current_figure->Name() << " "
					 << current_figure->Perimeter() << " "
					 << current_figure->Area() << endl;
			}
		}
	}
	return 0;
}