#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>
#include <tuple>

using namespace std;

enum class Lang {
	DE, FR, IT
};

struct Region {
	string std_name;
	string parent_std_name;
	map<Lang, string> names;
	int64_t population;
};

int FindMaxRepetitionCount(const vector<Region>& regions) {
	map<tuple<string, string, map<Lang, string>, int64_t>, int> new_regions;

	int result = 0;

	for (const auto& region : regions) {
		result = max(result, ++new_regions[tie(region.std_name, region.parent_std_name, region.names, region.population)]);
	}



//	for (const auto& region : new_regions) {
//		if (region.second > max) {
//			max = region.second;
//		}
//	}

	return result;
}


int main() {

	cout << FindMaxRepetitionCount({
										   {
												   "Moscow",
												   "Russia",
												   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
												   89
										   }, {
												   "Russia",
												   "Eurasia",
												   {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
												   89
										   }, {
												   "Moscow",
												   "Russia",
												   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
												   89
										   }, {
												   "Moscow",
												   "Russia",
												   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
												   89
										   }, {
												   "Russia",
												   "Eurasia",
												   {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
												   89
										   },
								   }) << endl;

	cout << FindMaxRepetitionCount({
										   {
												   "Moscow",
												   "Russia",
												   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
												   89
										   }, {
												   "Russia",
												   "Eurasia",
												   {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
												   89
										   }, {
												   "Moscow",
												   "Russia",
												   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
												   89
										   }, {
												   "Moscow",
												   "Toulouse",
												   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
												   89
										   }, {
												   "Moscow",
												   "Russia",
												   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
												   31
										   },
								   }) << endl;
	return 0;
}