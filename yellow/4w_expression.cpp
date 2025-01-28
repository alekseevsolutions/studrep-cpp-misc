#include <iostream>
#include <string>
#include <algorithm>
#include <deque>
#include <set>
#include <map>

#include "test_runner.h"

using namespace std;

class Expression{
public:
	explicit Expression(int x) {
		expression.emplace_back(to_string(x));
	}

	void addNewOperation(char operation, int num) {
		if ((operation == '/' or operation == '*') && is_prev_low_priority) {
			expression.push_front("(");
			expression.emplace_back(")");
			is_prev_low_priority = false;
		}

		if (operation == '-' or operation == '+') {
			is_prev_low_priority = true;
		}

		deque<string> new_operation = {" ", string(1, operation), " ", to_string(num)};
		expression.insert(expression.end(), new_operation.begin(), new_operation.end());
	}

	void printExpression() const {
		for (const auto& element : expression) {
			cout << element;
		}
		cout << endl;
	}

	string getExpression() const {
		stringstream ss;
		for (const auto& element : expression) {
			ss << element;
		}
		return ss.str();
	}

private:
	deque<string> expression;
	bool is_prev_low_priority = false;
};


void Test1() {
	Expression e(2);
	vector<pair<char, int>> v{{'-', 5}, {'/', 10}, {'+', 1}, {'*', 6}};
	for (const auto& op : v) {
		e.addNewOperation(op.first, op.second);
	}
	AssertEqual("((2 - 5) / 10 + 1) * 6", e.getExpression());
}

void Test2() {
	Expression e(3);
	vector<pair<char, int>> v{{'*', 5},
							  {'/', 10},
							  {'+', 1},
							  {'-', -6}};
	for (const auto& op : v) {
		e.addNewOperation(op.first, op.second);
	}
	AssertEqual("3 * 5 / 10 + 1 - -6", e.getExpression());
}

void Test3() {
	Expression e(8);
	vector<pair<char, int>> v{{'*', 3},
							  {'-', 6},
							  {'/', 1}};
	for (const auto& op : v) {
		e.addNewOperation(op.first, op.second);
	}
	AssertEqual("(8 * 3 - 6) / 1", e.getExpression());
}

void Test4() {
	Expression e(-1);
	vector<pair<char, int>> v{{'*', 5},
							  {'-', 3},
							  {'+', 6},
							  {'*', 7},
							  {'-', 10},
							  {'/', 4}};
	for (const auto& op : v) {
		e.addNewOperation(op.first, op.second);
	}
	AssertEqual("((-1 * 5 - 3 + 6) * 7 - 10) / 4", e.getExpression());
}

void Test5() {
	Expression e(1);
	vector<pair<char, int>> v{{'+', 2},
							  {'-', 3},
							  {'+', 4},
							  {'-', 5},
							  {'+', 6},
							  {'*', -4}};
	for (const auto& op : v) {
		e.addNewOperation(op.first, op.second);
	}
	AssertEqual("(1 + 2 - 3 + 4 - 5 + 6) * -4", e.getExpression());
}

void Test6() {
	Expression e(8);
	vector<pair<char, int>> v{{'*', -1},
							  {'-', -1},
							  {'*', -1}};
	for (const auto& op : v) {
		e.addNewOperation(op.first, op.second);
	}
	AssertEqual("(8 * -1 - -1) * -1", e.getExpression());
}

int main() {
//	TestRunner tr;
//	tr.RunTest(Test1, "1");
//	tr.RunTest(Test2, "2");
//	tr.RunTest(Test3, "3");
//	tr.RunTest(Test4, "4");
//	tr.RunTest(Test5, "5");
//	tr.RunTest(Test6, "6");


	int x, N;
	cin >> x >> N;

	Expression e(x);

	for (int i = 0; i < N; i++) {
		char operation;
		int num;
		cin >> operation;
		cin.ignore(1);
		cin >> num;
		e.addNewOperation(operation, num);
	}

	e.printExpression();

	return 0;
}
