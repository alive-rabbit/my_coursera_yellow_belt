#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <map>

enum class QueryType 
{
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query 
{
    QueryType type;
    std::string bus;
    std::string stop;
    std::vector<std::string> stops;
};

std::istream& operator >> (std::istream& is, Query& q) 
{
    std::string typeStr;
    is >> typeStr;
    if (typeStr == "NEW_BUS") 
    {
        q.type = QueryType::NewBus;
        is >> q.bus;
        int stop_count = 0;
        is >> stop_count;
        q.stops.resize(stop_count);
        for (auto& stop : q.stops) 
        {
            is >> stop;
        }
    }
    else if (typeStr == "BUSES_FOR_STOP") 
    {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    }
    else if (typeStr == "STOPS_FOR_BUS") 
    {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    }
    else if (typeStr == "ALL_BUSES") 
    {
        q.type = QueryType::AllBuses;
    }

    return is;
}

struct BusesForStopResponse 
{
    std::vector<std::string> buses;
};

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r) 
{
    if (r.buses.empty()) 
    {
        os << "No stop";
    }
    else 
    {
        for (const auto& bus : r.buses) 
        {
            os << bus << " ";
        }
    }
    return os;
}

struct StopsForBusResponse 
{
    std::string bus;
    std::vector<std::pair<std::string, std::vector<std::string>>> stops_for_buses;
};

std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r) 
{
    if (r.stops_for_buses.empty()) 
    {
        os << "No bus";
    }
    else 
    {
        bool first = true;
        for (const auto& stop_and_buses : r.stops_for_buses) 
        {
            if (!first) 
            {
                os << std::endl;
            }
            first = false;
            os << "Stop " << stop_and_buses.first << ":";
            if (stop_and_buses.second.size() == 1) 
            {
                os << " no interchange";
            }
            else 
            {
                for (const auto& bus : stop_and_buses.second) 
                {
                    if (bus != r.bus) 
                    {
                        os << " " << bus;
                    }
                }
            }
        }
    }
    return os;
}

struct AllBusesResponse 
{
    std::map<std::string, std::vector<std::string>> buses_to_stops;
};

std::ostream& operator << (std::ostream& os, const AllBusesResponse& r) {
    if (r.buses_to_stops.empty()) 
    {
        os << "No buses";
    }
    else 
    {
        bool first = true;
        for (const auto& bus_and_stops : r.buses_to_stops) 
        {
            if (!first) 
            {
                os << std::endl;
            }
            first = false;
            os << "Bus " << bus_and_stops.first << ":";
            for (const auto& stop : bus_and_stops.second) 
            {
                os << " " << stop;
            }
        }
    }
    return os;
}

class BusManager 
{
public:
    void AddBus(const std::string& bus, const std::vector<std::string>& stops) 
    {
        buses_to_stops.insert(make_pair(bus, stops));
        for (const auto& stop : stops) 
        {
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const std::string& stop) const
    {
        if (stops_to_buses.count(stop) == 0) 
        {
            return BusesForStopResponse{ std::vector<std::string>() };
        }
        else 
        {
            return BusesForStopResponse{ stops_to_buses.at(stop) };
        }
    }

    StopsForBusResponse GetStopsForBus(const std::string& bus) const
    {
        std::vector<std::pair<std::string, std::vector<std::string>>> result;

        if (buses_to_stops.count(bus) > 0) 
        {
            for (const auto& stop : buses_to_stops.at(bus)) 
            {
                result.push_back(std::make_pair(stop, stops_to_buses.at(stop)));
            }
        }
        return StopsForBusResponse{ bus, result };
    }

    AllBusesResponse GetAllBuses() const 
    {
        return AllBusesResponse{ buses_to_stops };
    }

private:
    std::map<std::string, std::vector<std::string>> buses_to_stops;
    std::map<std::string, std::vector<std::string>> stops_to_buses;
};
