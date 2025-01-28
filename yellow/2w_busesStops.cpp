#include <string>
#include <sstream>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
	NewBus,
	BusesForStop,
	StopsForBus,
	AllBuses
};

struct Query {
	QueryType type;
	string bus;
	string stop;
	vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
	string request;
	is >> request;
	if (request == "NEW_BUS") {
		q.type = QueryType::NewBus;
		int stops_count;
		is >> q.bus >> stops_count;
		q.stops.resize(stops_count);
		for (auto& stop : q.stops) {
			is >> stop;
		}
	} else if (request == "BUSES_FOR_STOP") {
		q.type = QueryType::BusesForStop;
		is >> q.stop;
	} else if (request == "STOPS_FOR_BUS") {
		q.type = QueryType::StopsForBus;
		is >> q.bus;
	} else if (request == "ALL_BUSES") {
		q.type = QueryType::AllBuses;
	}

	return is;
}

struct BusesForStopResponse {
	vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
	if (!r.buses.empty()) {
		bool is_first_el = true;
		for (const auto& bus : r.buses) {
			if (is_first_el) {
				is_first_el = false;
			} else {
				os << " ";
			}
			os << bus;
		}
	} else {
		os << "No stop";
	}
	return os;
}

struct StopsForBusResponse {
	pair<string, vector<string>> bus;
	const map<string, vector<string>>& stops;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
	if (!r.bus.second.empty()) {
		bool is_first_el = true;
		for (const auto& stop : r.bus.second) {
			if (is_first_el) {
				is_first_el = false;
			}
			else {
				os << endl;
			}
			os << "Stop " << stop << ":";
			if (r.stops.at(stop).size() == 1) {
				os << " no interchange";
			} else {
				for (const auto& bus : r.stops.at(stop)) {
					os << (bus != r.bus.first ? " " + bus : "");
				}
			}
		}
	} else {
		os << "No bus";
	}
	return os;
}

struct AllBusesResponse {
	map<string, vector<string>> buses_to_stop;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
	if (r.buses_to_stop.empty()) {
		cout << "No buses";
	} else {
		bool is_first_el = true;
		for (const auto& bus_item : r.buses_to_stop) {
			if (is_first_el) {
				is_first_el = false;
			} else {
				os << endl;
			}
			cout << "Bus " << bus_item.first << ": ";
			for (const string& stop : bus_item.second) {
				cout << stop << " ";
			}
		}
	}
	return os;
}


class BusManager {
public:
	void AddBus(const string& bus, const vector<string>& stops) {
		for (const auto& stop : stops) {
			all_buses[bus].push_back(stop);
			all_stops[stop].push_back(bus);
		}
	}

	BusesForStopResponse GetBusesForStop(const string& stop) const {
		try {
			return BusesForStopResponse{all_stops.at(stop)};
		} catch (out_of_range&) {
			return BusesForStopResponse{{}};
		}
	}

	StopsForBusResponse GetStopsForBus(const string& bus) const {
		try {
			return StopsForBusResponse{make_pair(bus, all_buses.at(bus)), all_stops};
		} catch (out_of_range&) {
			return StopsForBusResponse{make_pair(bus, vector<string>()), all_stops};
		}
	}

	AllBusesResponse GetAllBuses() const {
		if (all_buses.empty()){
			return AllBusesResponse{};
		} else {
			return AllBusesResponse{all_buses};
		}
	}
private:
	map<string, vector<string>> all_buses, all_stops;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
	int query_count;
	Query q;

	cin >> query_count;

	BusManager bm;
	for (int i = 0; i < query_count; ++i) {
		cin >> q;
		switch (q.type) {
			case QueryType::NewBus:
				bm.AddBus(q.bus, q.stops);
				break;
			case QueryType::BusesForStop:
				cout << bm.GetBusesForStop(q.stop) << endl;
				break;
			case QueryType::StopsForBus:
				cout << bm.GetStopsForBus(q.bus) << endl;
				break;
			case QueryType::AllBuses:
				cout << bm.GetAllBuses() << endl;
				break;
		}
	}

	return 0;
}
