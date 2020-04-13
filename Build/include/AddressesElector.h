#pragma once
#include <boost/asio.hpp>
#include "OccupiedAddresses.h"

class AddressesElector {
    private:
        OccupiedAddresses& occuppiedAdddresses;
        boost::asio::ip::address_v4_range addressesRangeV4;
        boost::asio::ip::address_v6_range addressesRangeV6;
    public:
        AddressesElector(OccupiedAddresses&);
        ~AddressesElector();

        boost::asio::ip::address_v4 proposeV4Address();
        boost::asio::ip::address_v6 proposeV6Address();
};