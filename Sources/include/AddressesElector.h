#pragma once
#include "AssignedAddresses.h"
#include <boost/asio.hpp>
#include <optional>

class AddressesElector {
    private:
        AssignedAddresses& assignedAdddresses;
        boost::asio::ip::address_v4_range addressesRangeV4;
    public:
        AddressesElector(AssignedAddresses&);
        ~AddressesElector();

        std::optional<boost::asio::ip::address_v4> proposeV4Address();
};