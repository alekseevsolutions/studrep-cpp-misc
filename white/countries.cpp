#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;


int main() {
	int p;
	cin >> p;

	map<string, string> capitals;

	for (int i = 0; i < p; ++i) {
		string query;
		cin >> query;

		if (query == "CHANGE_CAPITAL") {
			string country, new_capital;
			cin >> country >> new_capital;

			if (!capitals.count(country)) {
				cout << "Introduce new country " << country << " with capital " << new_capital << endl;
			} else if (capitals[country] == new_capital) {
				cout << "Country " << country << " hasn't changed its capital" << endl;
			} else {
				string old_capital = capitals[country];
				cout << "Country " << country << " has changed its capital from " << old_capital << " to "
					 << new_capital << endl;
			}
			capitals[country] = new_capital;

		} else if (query == "RENAME") {
			string old_country_name, new_country_name;
			cin >> old_country_name >> new_country_name;

			if (old_country_name == new_country_name || capitals.count(new_country_name) ||
				!capitals.count(old_country_name)) {
				cout << "Incorrect rename, skip" << endl;
			} else {
				capitals[new_country_name] = capitals[old_country_name];
				capitals.erase(old_country_name);
				cout << "Country " << old_country_name << " with capital " << capitals[new_country_name] <<
					 " has been renamed to " << new_country_name << endl;
			}

		} else if (query == "ABOUT") {
			string country;
			cin >> country;

			if (!capitals.count(country)) {
				cout << "Country " << country << " doesn't exist" << endl;
			} else {
				cout << "Country " << country << " has capital " << capitals[country] << endl;
			}

		} else if (query == "DUMP") {
			if (capitals.empty()) {
				cout << "There are no countries in the world" << endl;
			} else {
				for (auto &item: capitals) {
					cout << item.first << "/" << item.second << " ";
				}
				cout << endl;
			}
		}
	}
}

