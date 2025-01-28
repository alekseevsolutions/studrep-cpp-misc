#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;


int main() {
	int p;
	cin >> p;

	map<string, vector<string>> buses, stops;

	for (int i = 0; i < p; ++i) {
		string query;
		cin >> query;

		if (query == "NEW_BUS") {
			string bus;
			int stop_count;

			cin >> bus >> stop_count;

			for (int s = 0; s < stop_count; ++s) {
				string new_stop;
				cin >> new_stop;
				stops[new_stop].push_back(bus);
				buses[bus].push_back(new_stop);
			}

		} else if (query == "BUSES_FOR_STOP") {
			string stop;
			cin >> stop;

			if (!stops[stop].empty()) {
				for (const auto &b: stops[stop]) {
					cout << b << " ";
				}
				cout << endl;
			} else {
				cout << "No stop" << endl;
			}

		} else if (query == "STOPS_FOR_BUS") {
			string bus;
			cin >> bus;

			if (!buses.count(bus)) {
				cout << "No bus" << endl;
			} else {
				for (const auto &s: buses[bus]) {
					cout << "Stop " << s << ": ";
					if (stops[s].size() == 1) {
						cout << "no interchange";
					} else {
						for (auto &b: stops[s]) {
							cout << (b != bus ? b + " " : "");
						}
					}
					cout << endl;
				}
			}

		} else if (query == "ALL_BUSES") {

			if (buses.empty()) {
				cout << "No buses" << endl;
			} else {
				for (const auto &item: buses) {
					cout << "Bus " << item.first << ": ";
					for (const auto &s : item.second){
						cout << s << " ";
					}
					cout << endl;
				}
			}
		}
	}
}

