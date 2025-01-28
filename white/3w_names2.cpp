#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

string FindNameByYear(const map<int, string> &names, int year) {
	string name;
	for (const auto &item: names) {
		if (item.first <= year) {
			name = item.second;
		} else {
			break;
		}
	}
	return name;
}

vector<string> FindAllNamesByYear(const map<int, string> &names, int year) {
	vector<string> all_names;
	string last_name;
	for (const auto &item: names) {
		if (item.first <= year && last_name != item.second) {
			all_names.insert(all_names.begin(), item.second); // the latest name in the beginning
			last_name = item.second;
		} else {
			break;
		}
	}
	return all_names;
}

string PrintNames(const vector<string> &all_names) {
	string result;
	result = all_names[0]; // the latest name
	if (all_names.size() > 1) {
		result += " (";
		for (int i = 1; i < all_names.size(); ++i) {
			result += all_names[i] + (i == all_names.size() - 1 ? "" : ", ");
		}
		result += ")";
	}

	return result;
}

class Person {
public:
	Person(const string &first_name, const string &last_name, const int &birth_year) {
		year_of_birth = birth_year;
		first_names[birth_year] = first_name;
		last_names[birth_year] = last_name;
	}

	void ChangeFirstName(const int &year, const string &first_name) {
		if (year >= year_of_birth) {
			first_names[year] = first_name;
		}
	}

	void ChangeLastName(const int &year, const string &last_name) {
		if (year >= year_of_birth) {
			last_names[year] = last_name;
		}
	}

	string GetFullName(int &year) const {
		if (year < year_of_birth) {
			return "No person";
		}

		const string first_name = FindNameByYear(first_names, year);
		const string last_name = FindNameByYear(last_names, year);

		if (first_name.empty() && last_name.empty()) {
			return "Incognito";

		} else if (first_name.empty()) {
			return last_name + " with unknown first name";

		} else if (last_name.empty()) {
			return first_name + " with unknown last name";

		} else {
			return first_name + " " + last_name;
		}
	}

	string GetFullNameWithHistory(int &year) const {
		if (year < year_of_birth) {
			return "No person";
		}

		const vector<string> first_names_by_year = FindAllNamesByYear(first_names, year);
		const vector<string> last_names_by_year = FindAllNamesByYear(last_names, year);

		if (first_names_by_year.empty() && last_names_by_year.empty()) {
			return "Incognito";

		} else if (first_names_by_year.empty()) {
			return PrintNames(last_names_by_year) + " with unknown first name";

		} else if (last_names_by_year.empty()) {
			return PrintNames(first_names_by_year) + " with unknown last name";

		} else {
			return PrintNames(first_names_by_year) + " " + PrintNames(last_names_by_year);
		}
	}

private:
	map<int, string> first_names;
	map<int, string> last_names;
	int year_of_birth;
};


int main() {
	Person person("Polina", "Sergeeva", 1960);
	for (int year : {1959, 1960}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeFirstName(1965, "Appolinaria");
	person.ChangeLastName(1967, "Ivanova");
	for (int year : {1965, 1967}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	return 0;
}
