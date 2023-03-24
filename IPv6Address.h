#pragma once
#include <cstdint>
#include <array>
#include <string>
#include <cstdlib>

class IPv6Address
{
public:

    void Load(std::string const& addr);

    bool GetBit(std::size_t index) const;

private:

    using DataType = std::array<uint16_t, 8>;

    void LoadFromPrefix(std::string const& prefix);
    void LoadFromSuffix(std::string const& suffix);
    void LoadFromString(std::string const& s, DataType::size_type dataStartPos);

    DataType address = {0, 0, 0, 0, 0, 0, 0, 0};

};