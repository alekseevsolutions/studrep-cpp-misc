#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
	os << "{";
	bool first = true;
	for (const auto& kv : m) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
	if (t != u) {
		ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty()) {
			os << " hint: " << hint;
		}
		throw runtime_error(os.str());
	}
}

void Assert(bool b, const string& hint) {
	AssertEqual(b, true, hint);
}

class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name) {
		try {
			func();
			cerr << test_name << " OK" << endl;
		} catch (exception& e) {
			++fail_count;
			cerr << test_name << " fail: " << e.what() << endl;
		} catch (...) {
			++fail_count;
			cerr << "Unknown exception caught" << endl;
		}
	}

	~TestRunner() {
		if (fail_count > 0) {
			cerr << fail_count << " unit tests failed. Terminate" << endl;
			exit(1);
		}
	}

private:
	int fail_count = 0;
};


int CloseVal(const map<int, string> &m, const int &x) {
	int closest = 0;
	for (auto &item: m) {
		if (item.first > closest && item.first <= x) {
			closest = item.first;
		}
	}
	return closest;
}

/*
class Person {
public:
	void ChangeFirstName(int year, const string &first_name) {
		f_name_changes[year] = first_name;
	}

	void ChangeLastName(int year, const string &last_name) {
		l_name_changes[year] = last_name;
	}

	string GetFullName(int year) {
		int last_f_name_change = CloseVal(f_name_changes, year);
		int last_l_name_change = CloseVal(l_name_changes, year);

		if (!last_f_name_change && !last_l_name_change) {
			return "Incognito";
		} else if (!last_l_name_change) {
			return f_name_changes[last_f_name_change] + " with unknown last name";
		} else if (!last_f_name_change) {
			return l_name_changes[last_l_name_change] + " with unknown first name";
		} else {
			return f_name_changes[last_f_name_change] + " " + l_name_changes[last_l_name_change];
		}
	}

private:
	map<int, string> f_name_changes;
	map<int, string> l_name_changes;
};

*/

void TestPredefinedLastNameFirst() {
	Person person;

	person.ChangeLastName(1965, "Sergeeva");
	person.ChangeFirstName(1967, "Polina");

	AssertEqual(person.GetFullName(1964), "Incognito");
	AssertEqual(person.GetFullName(1966), "Sergeeva with unknown first name");
	AssertEqual(person.GetFullName(1968), "Polina Sergeeva");
}

void TestPredefined() {
	Person person;

	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");

	AssertEqual(person.GetFullName(1964), "Incognito");
	AssertEqual(person.GetFullName(1966), "Polina with unknown last name");
	AssertEqual(person.GetFullName(1968), "Polina Sergeeva");

	person.ChangeFirstName(1969, "Appolinaria");
	AssertEqual(person.GetFullName(1968), "Polina Sergeeva");
	AssertEqual(person.GetFullName(1969), "Appolinaria Sergeeva");
	AssertEqual(person.GetFullName(1970), "Appolinaria Sergeeva");

	person.ChangeLastName(1968, "Volkova");
	AssertEqual(person.GetFullName(1967), "Polina Sergeeva");
	AssertEqual(person.GetFullName(1968), "Polina Volkova");
	AssertEqual(person.GetFullName(1969), "Appolinaria Volkova");

}

int main() {
	TestRunner runner;
	runner.RunTest(TestPredefined, "TestPredefined");
	runner.RunTest(TestPredefinedLastNameFirst, "TestPredefinedLastNameFirst");
	return 0;
}
