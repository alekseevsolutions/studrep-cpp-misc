#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

using namespace std;

int CloseVal(const map<int, string> &m, const int &x) {
	int closest = 0;
	for (auto &item: m) {
		if (item.first > closest && item.first <= x) {
			closest = item.first;
		}
	}
	return closest;
}


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

int main() {
	Person person;

	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year: {1900, 1965, 1990}) {
		cout << person.GetFullName(year) << endl;
	}

	person.ChangeFirstName(1970, "Appolinaria");
	for (int year: {1969, 1970}) {
		cout << person.GetFullName(year) << endl;
	}

	person.ChangeLastName(1968, "Volkova");
	for (int year: {1969, 1970}) {
		cout << person.GetFullName(year) << endl;
	}

	return 0;
}

