#pragma once
#include <memory>
#include <optional>
#include <limits>
#include "RoutingRecord.h"
#include "IPNetwork.h"

class ServerData
{
public:

    using PopIdType = RoutingRecord::PopIdType;

    struct DNSRecord
    {
        int scopePrefixLength;
        PopIdType popId;
    };

    ServerData();

    void AddRecord(RoutingRecord const& r);
    std::optional<DNSRecord> Route(IPNetwork const& network) const;

private:

    struct TrieNode
    {
        static auto const invalidPopId = std::numeric_limits<PopIdType>::max();

        PopIdType popId = invalidPopId;
        std::unique_ptr<TrieNode> childs[2];
    };

    std::unique_ptr<TrieNode> root;
};
