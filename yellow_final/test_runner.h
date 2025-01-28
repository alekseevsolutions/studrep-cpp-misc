#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <set>
#include <map>


using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s);

template <class T>
ostream& operator << (ostream& os, const set<T>& s);

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m);

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

void Assert(bool b, const string& hint = {});

class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name);

	~TestRunner();

private:
	int fail_count = 0;
};


template <class TestFunc>
void TestRunner::RunTest(TestFunc func, const string& test_name) {
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