#pragma once

#include <stdexcept>

#include "bus_manager.h"

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
	for (const auto& stop : stops) {
		all_buses[bus].push_back(stop);
		all_stops[stop].push_back(bus);
	}
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
	try {
		return BusesForStopResponse{all_stops.at(stop)};
	} catch (out_of_range&) {
		return BusesForStopResponse{{}};
	}
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
	try {
		return StopsForBusResponse{make_pair(bus, all_buses.at(bus)), all_stops};
	} catch (out_of_range&) {
		return StopsForBusResponse{make_pair(bus, vector<string>()), all_stops};
	}
}

AllBusesResponse BusManager::GetAllBuses() const {
	if (all_buses.empty()){
		return AllBusesResponse{};
	} else {
		return AllBusesResponse{all_buses};
	}
}