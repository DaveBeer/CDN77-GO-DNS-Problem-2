#include "IPNetwork.h"
#include <cassert>
#include <sstream>

IPNetwork::IPNetwork(std::string const& s)
{
    Load(s);
}

void IPNetwork::Load(std::string const& s)
{
    auto const slashPos = s.find('/');
    assert(slashPos != std::string::npos);
    ip.Load(s.substr(0, slashPos));

    std::istringstream iss(s.substr(slashPos + 1));
    iss >> prefixLength;
    assert(iss);
}
