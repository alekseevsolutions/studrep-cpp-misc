#include <iostream>
#include <string>
#include <vector>
#include <set>

#include "test_runner.h"

using namespace std;

string ch_to_str(const char &c) {
	stringstream ss;
	ss << c;
	return ss.str();
}

/*
template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
		RandomIt range_begin, RandomIt range_end,
		char prefix) {

	// Все строки, начинающиеся с '<prefix>', больше или равны строке "<prefix>"
	auto left = lower_bound(range_begin, range_end, string(1, prefix));

	// Составим следующий в алфавите символ.
	// Не страшно, если prefix = 'z':
	// в этом случае мы получим следующий за 'z' символ в таблице символов
	char next_prefix = static_cast<char>(prefix + 1);

	// Строка "<next_prefix>" в рамках буквенных строк
	// является точной верхней гранью
	// множества строк, начнающихся с '<prefix>'
	auto right = lower_bound(range_begin, range_end, string(1, next_prefix));

	return {left, right};
}

int main() {
	const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};

	const auto m_result =
			FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
	for (auto it = m_result.first; it != m_result.second; ++it) {
		cout << *it << " ";
	}
	cout << endl;

	const auto p_result =
			FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
	cout << (p_result.first - begin(sorted_strings)) << " " <<
		 (p_result.second - begin(sorted_strings)) << endl;

	const auto z_result =
			FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
	cout << (z_result.first - begin(sorted_strings)) << " " <<
		 (z_result.second - begin(sorted_strings)) << endl;

	return 0;
}
*/

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
		RandomIt range_begin, RandomIt range_end,
		const string& prefix) {

	// Все строки, начинающиеся с prefix, больше или равны строке "<prefix>"
	auto left = lower_bound(range_begin, range_end, prefix);

	// Составим строку, которая в рамках буквенных строк является
	// точной верхней гранью множества строк, начинающихся с prefix
	string upper_bound = prefix;
	++upper_bound[upper_bound.size() - 1];

	// Первое встреченное слово, не меньшее upper_bound,
	// обязательно является концом полуинтервала
	auto right = lower_bound(range_begin, range_end, upper_bound);

	return {left, right};
}


int main() {

	const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};

	const auto mo_result =
			FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
	for (auto it = mo_result.first; it != mo_result.second; ++it) {
		cout << *it << " ";
	}
	cout << endl;

	const auto mt_result =
			FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
	cout << (mt_result.first - begin(sorted_strings)) << " " <<
		 (mt_result.second - begin(sorted_strings)) << endl;

	const auto na_result =
			FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
	cout << (na_result.first - begin(sorted_strings)) << " " <<
		 (na_result.second - begin(sorted_strings)) << endl;

	return 0;
}