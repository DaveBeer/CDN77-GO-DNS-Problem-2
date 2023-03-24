#pragma once
#include <forward_list>
#include <cstdint>
#include <memory>
#include <optional>
#include "RoutingRecord.h"
#include "IPNetwork.h"

class ServerData
{
public:

    struct DNSRecord
    {
        DNSRecord(int spl, uint16_t pop) : scopePrefixLength(spl), popId(pop) {}

        int scopePrefixLength;
        uint16_t popId;
    };

    ServerData();

    void AddRecord(RoutingRecord const& r);
    std::optional<DNSRecord> Route(IPNetwork const& network) const;

private:

    std::forward_list<DNSRecord> records;

    struct TrieNode
    {
        DNSRecord const* record = nullptr;
        std::unique_ptr<TrieNode> childs[2];
    };

    std::unique_ptr<TrieNode> root;
};
