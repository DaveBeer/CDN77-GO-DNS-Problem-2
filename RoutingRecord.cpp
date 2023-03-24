#include "RoutingRecord.h"
#include <cassert>
#include <sstream>

RoutingRecord::RoutingRecord(std::string const& s)
{
    std::istringstream iss(s);

    std::string network;
    iss >> network;
    ntw.Load(network);

    iss >> popId;
    assert(iss);
}
