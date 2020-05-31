#include "DhcpUtils.h"
#include <iostream>

namespace DhcpUtils {
    
std::array<int,4> addressToIntParts(boost::asio::ip::address_v4 addr) {
    std::array<int,4> partials;
    std::string address = addr.to_string();

    for(size_t octet = 0; octet < partials.size(); octet++) {
        size_t nextDot = address.find_first_of('.');
        if(nextDot != std::string::npos) {
            partials[octet] = std::stoi(address.substr(0,nextDot));
            address.erase(0,nextDot+1);
        } else partials[octet] = std::stoi(address);
    }

    return partials;
}

boost::asio::ip::address_v4 stdByteArrayToAddress(std::array<std::byte,4>& addressParts) {
    std::string addrString{};
    for(size_t octet = 0; octet < addressParts.size(); ++octet){
        addrString += std::to_string(std::to_integer<int>(addressParts[octet]));
    }
    
    return boost::asio::ip::address_v4::from_string(addrString);
}

std::optional<size_t> findOptionPosition(std::array<std::byte,DHCP_OPTIONS_LENGTH>& options, int searchingOption) {
    size_t position = 4; /* Starting from position 4, because 0,1,2,3 is taken by DHCP Magic, which we ignore */

    while(position < DHCP_OPTIONS_LENGTH) {
        if(std::to_integer<int>(options[position]) == 0) return {};

        if(std::to_integer<int>(options[position]) == searchingOption) {
            return position;
        } else {
            size_t step = std::to_integer<size_t>(options[position+1]);
            position += step + 2;
        }
    }

    return {};
}

} // DhcpUtils namespace