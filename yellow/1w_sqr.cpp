#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>
#include <set>
#include <tuple>
#include <cmath>

using namespace std;

template <typename T> T Sqr(T t);
template <typename First, typename Second> pair<First, Second> Sqr(const pair<First, Second>& p);
template <typename T> vector<T> Sqr(const vector<T>& vi);
template <typename Key, typename Value> map<Key, Value> Sqr(const map<Key, Value>& m);


template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& p) {
	return {Sqr(p.first), Sqr(p.second)};
}

template <typename T>
vector<T> Sqr(const vector<T>& vi) {
	vector<T> result;
	for (const auto& x : vi){
		result.push_back(Sqr(x));
	}
	return result;
}

template <typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& m) {
	map<Key, Value> result;
	for (const auto& item : m) {
		result[item.first] = Sqr(item.second);
	}
	return m;
}

template <typename T>
T Sqr(T t) {
	return t * t;
}

int main() {
	vector<int> v = {1, 2, 3};
	cout << "vector:";
	for (int x : Sqr(v)) {
		cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = {
			{4, {2, 2}},
			{7, {4, 3}}
	};
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
		cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}

	return 0;
}