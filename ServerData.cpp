#include "ServerData.h"
#include <cassert>
#include <algorithm>

ServerData::ServerData()
{
    root = std::make_unique<TrieNode>();
}

void ServerData::AddRecord(RoutingRecord const& r)
{
    auto* curNode = root.get();

    for (auto bitIdx = 0; bitIdx < r.ntw.prefixLength; ++bitIdx)
    {
        curNode->UpdateScopePrefixLength(r.ntw.prefixLength);
        auto& child = curNode->childs[r.ntw.ip.GetBit(bitIdx)];

        if (child == nullptr)
        {
            child = std::make_unique<TrieNode>();
        }

        curNode = child.get();
    }

    curNode->UpdateScopePrefixLength(r.ntw.prefixLength);
    assert(r.popId != TrieNode::invalidPopId);
    curNode->dns.popId = r.popId;
}

std::optional<ServerData::DNSRecord> ServerData::Route(IPNetwork const& network) const
{
    auto const* curNode = root.get();
    auto const* mostSpecificDNSRecord = &curNode->dns;

    for (auto bitIdx = 0; bitIdx < network.prefixLength; ++bitIdx)
    {
        auto& child = curNode->childs[network.ip.GetBit(bitIdx)];

        if (child == nullptr)
        {
            break;
        }

        curNode = child.get();

        if (curNode->dns.popId != TrieNode::invalidPopId)
        {
            mostSpecificDNSRecord = &curNode->dns;
        }
    }

    if (mostSpecificDNSRecord->popId == TrieNode::invalidPopId)
    {
        return {};
    }
    else
    {
        return {*mostSpecificDNSRecord};
    }
}

void ServerData::TrieNode::UpdateScopePrefixLength(int const newSpl)
{
    dns.scopePrefixLength = std::max(dns.scopePrefixLength, newSpl);
}
