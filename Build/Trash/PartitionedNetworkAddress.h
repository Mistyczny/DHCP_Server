#pragma once
#include <array>
#include <string>

struct PartitionedNetworkAddress{
    std::array<unsigned int,4> octets;

    std::string getFullAddressAsString();
    bool partitionNetworkAddress(std::string&);
};