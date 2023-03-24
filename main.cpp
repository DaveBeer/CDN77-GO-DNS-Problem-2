#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "IPNetwork.h"
#include "ServerData.h"

void PrintRoute(ServerData const& sd, std::string const& ecs)
{
    std::cout << "ECS: " << ecs << '\n';

    auto const &optr = sd.Route(IPNetwork{ecs});

    if (optr.has_value())
    {
        std::cout << "pop: " << optr->popId << '\n';
        std::cout << "scope prefix length: " << optr->scopePrefixLength << '\n';
    }
    else
    {
        std::cout << "couldn't route\n";
    }

    std::cout << std::endl;
}

int main()
{
    ServerData sd;
    std::ifstream file{"routing-data.txt"};
    std::string s;

    while (std::getline(file, s))
    {
        sd.AddRecord(RoutingRecord{s});
    }

    PrintRoute(sd, "2001:49f0:d0b8:8a00::/56");
    PrintRoute(sd, "2804:1c1c:2000::/34");
    PrintRoute(sd, "2804:1c1c:2000::/35");
    PrintRoute(sd, "2804:1c1c:2000::/36");
    PrintRoute(sd, "2804:1c1c:2000::/37");
    PrintRoute(sd, "2804:1c1c:2000::/47");
    PrintRoute(sd, "2804:1c1c:2000::/48");
    PrintRoute(sd, "2800::/8");

    return EXIT_SUCCESS;
}