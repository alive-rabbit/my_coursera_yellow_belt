#include "bus_manager.h"

void BusManager::AddBus(const std::string& bus, const std::vector<std::string>& stops)
{
    buses_to_stops.insert(make_pair(bus, stops));
    for (const auto& stop : stops) 
    {
        stops_to_buses[stop].push_back(bus);
    }
}


BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const
{
    auto iter = stops_to_buses.find(stop);
    if (iter == stops_to_buses.end()) 
    {
        return BusesForStopResponse{vector<string>()};
    } 
    else 
    {
        return BusesForStopResponse{iter->second};
    }
}


StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const
{
    std::vector<std::pair<std::string, std::vector<std::string>>> result;

    auto iter = buses_to_stops.find(bus);
    if (iter != buses_to_stops.end()) 
    {
        for (const auto& stop : iter->second) 
        {
            result.push_back(make_pair(stop, stops_to_buses.at(stop)));
        }
    }
    return StopsForBusResponse{bus, result};
}


AllBusesResponse BusManager::GetAllBuses() const {
  return AllBusesResponse{buses_to_stops};
}
