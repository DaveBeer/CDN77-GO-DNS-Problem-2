#include "IPv6Address.h"
#include <sstream>
#include <ios>
#include <cassert>
#include <algorithm>

void IPv6Address::Load(std::string const& addr)
{
    address.fill(0);

    auto const dblColPos = addr.find("::");
    auto const dblColPresent = (dblColPos != std::string::npos);

    if (!dblColPresent || dblColPos > 0)
    {
        auto const prefixSize = (dblColPresent) ? dblColPos : addr.size();
        LoadFromPrefix(addr.substr(0, prefixSize));
    }

    if (dblColPresent)
    {
        LoadFromSuffix(addr.substr(dblColPos + 2)); // empty suffix is ok
    }
}

void IPv6Address::LoadFromPrefix(std::string const& prefix)
{
    LoadFromString(prefix, 0);
}

void IPv6Address::LoadFromSuffix(std::string const& suffix)
{
    auto const colonsCount = std::count(suffix.begin(), suffix.end(), ':');
    LoadFromString(suffix, 7 - colonsCount);
}

void IPv6Address::LoadFromString(std::string const& s, DataType::size_type const dataStartPos)
{
    std::istringstream iss{s};
    iss >> std::hex;

    char colonDummy;
    DataType::value_type quibble;
    auto i = dataStartPos;

    while (iss >> quibble)
    {
        assert(i <= 7);
        address[i++] = quibble;
        iss >> colonDummy;
    }
}

bool IPv6Address::GetBit(std::size_t const index) const
{
    static auto const chunkBitSize = sizeof(DataType::value_type) * 8;
    assert(index < address.size() * chunkBitSize);

    auto const chunk = address[index / chunkBitSize];
    auto const mask = 1u << chunkBitSize - 1 - index % chunkBitSize;

    return (chunk & mask) != 0;
}
