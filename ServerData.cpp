#include "ServerData.h"
#include <cassert>

ServerData::ServerData()
{
    root = std::make_unique<TrieNode>();
}

void ServerData::AddRecord(RoutingRecord const& r)
{
    auto* curNode = root.get();
    auto bitIdx = 0;

    for (; bitIdx < r.ntw.prefixLength; ++bitIdx)
    {
        auto& child = curNode->childs[r.ntw.ip.GetBit(bitIdx)];

        if (child == nullptr)
        {
            child = std::make_unique<TrieNode>();
        }

        curNode = child.get();
    }

    assert(bitIdx == r.ntw.prefixLength);
    assert(r.popId != TrieNode::invalidPopId);
    curNode->popId = r.popId;
}

std::optional<ServerData::DNSRecord> ServerData::Route(IPNetwork const& network) const
{
    auto const* curNode = root.get();
    auto mostSpecificDNSRecord = DNSRecord{0, curNode->popId};

    for (auto bitIdx = 0; bitIdx < network.prefixLength; ++bitIdx)
    {
        auto& child = curNode->childs[network.ip.GetBit(bitIdx)];

        if (child == nullptr)
        {
            break;
        }

        curNode = child.get();

        if (curNode->popId != TrieNode::invalidPopId)
        {
            mostSpecificDNSRecord = {bitIdx + 1, curNode->popId};
        }
    }

    if (mostSpecificDNSRecord.popId == TrieNode::invalidPopId)
    {
        return {};
    }
    else
    {
        return {mostSpecificDNSRecord};
    }
}
