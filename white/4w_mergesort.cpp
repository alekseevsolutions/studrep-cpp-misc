#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <numeric>

//#include "test_runner.h"

using namespace std;


template <typename RandomIt>
void MergeSort2(RandomIt range_begin, RandomIt range_end) {
	int const range = range_end - range_begin;

	if (range >= 2) {
		vector<typename RandomIt::value_type> elements(range_begin, range_end);
		auto mid = elements.begin() + range / 2;

		MergeSort(elements.begin(), mid);
		MergeSort(mid, elements.end());

		merge(elements.begin(), mid, mid, elements.end(), range_begin);
	} else {
		return;
	}
}

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	int const range = range_end - range_begin;

	if (range >= 3) {
		vector<typename RandomIt::value_type> elements(range_begin, range_end), tmp;

		auto one_third = elements.begin() + range / 3;
		auto two_third = one_third + range / 3;



		MergeSort(elements.begin(), one_third);
		MergeSort(one_third, two_third);
		MergeSort(two_third, elements.end());

		merge(elements.begin(), one_third, one_third, two_third, back_inserter(tmp));
		merge(tmp.begin(), tmp.end(), two_third, elements.end(), range_begin);

	} else {
		return;
	}
}



int main() {
	vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
	MergeSort(begin(v), end(v));
	for (int x : v) {
		cout << x << " ";
	}
	cout << endl;
	return 0;
}
