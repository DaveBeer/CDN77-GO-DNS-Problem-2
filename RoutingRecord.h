#pragma once
#include <cstdint>
#include <string>
#include "IPNetwork.h"

struct RoutingRecord
{
    explicit RoutingRecord(std::string const& s);
    
    IPNetwork ntw;

    using PopIdType = uint16_t;
    PopIdType popId;
};