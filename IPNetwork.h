#pragma once
#include <string>
#include "IPv6Address.h"

struct IPNetwork
{
    IPNetwork() = default;
    explicit IPNetwork(std::string const& s);
    
    void Load(std::string const& s);
    
    IPv6Address ip;
    int prefixLength = 0;
};