#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <numeric>

//#include "test_runner.h"

using namespace std;

ostream& operator<<(ostream& os, const vector<int> &v) {
	for (const auto &item : v) {
		cout << item << " ";
	}
	return os;
}

int factorial(int i)
{
	if (i==0) return 1;
	else return i*factorial(i-1);
}

void Foo(const int N) {
	vector<int> v(N);
	iota(v.rbegin(), v.rend(), 1);

	do {
		for (const auto& item : v) {
			cout << item << " ";
		}
		cout << endl;
	} while (prev_permutation(v.begin(), v.end()));
}


int main() {
	int N;
	cin >> N;
	Foo(N);

	return 0;
}
