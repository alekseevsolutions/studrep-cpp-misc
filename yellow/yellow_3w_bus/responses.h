#pragma once

#include <string>
#include <vector>
#include <map>

using namespace std;

struct BusesForStopResponse {
	vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
	pair<string, vector<string>> bus;
	const map<string, vector<string>>& stops;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
	map<string, vector<string>> buses_to_stop;
};

ostream& operator << (ostream& os, const AllBusesResponse& r);