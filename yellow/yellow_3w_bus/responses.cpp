#pragma once

#include <iostream>
#include "responses.h"

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