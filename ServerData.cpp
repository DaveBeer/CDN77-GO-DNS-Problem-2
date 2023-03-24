#include "ServerData.h"

ServerData::ServerData()
{
    root = std::make_unique<TrieNode>();
}

void ServerData::AddRecord(RoutingRecord const& r)
{
    auto* curNode = root.get();

    for (auto bitIdx = 0; bitIdx < r.ntw.prefixLength; ++bitIdx)
    {
        auto& child = curNode->childs[r.ntw.ip.GetBit(bitIdx)];

        if (child == nullptr)
        {
            child = std::make_unique<TrieNode>();
        }

        curNode = child.get();
    }

    curNode->record = &records.emplace_front(r.ntw.prefixLength, r.popId);
}

std::optional<ServerData::DNSRecord> ServerData::Route(IPNetwork const& network) const
{
    auto const* curNode = root.get();
    auto const* mostSpecificRecord = curNode->record;

    for (auto bitIdx = 0; bitIdx < network.prefixLength; ++bitIdx)
    {
        auto& child = curNode->childs[network.ip.GetBit(bitIdx)];

        if (child == nullptr)
        {
            break;
        }

        curNode = child.get();

        if (curNode->record != nullptr)
        {
            mostSpecificRecord = curNode->record;
        }
    }

    if (mostSpecificRecord == nullptr)
    {
        return {};
    }
    else
    {
        return {*mostSpecificRecord};
    }
}
