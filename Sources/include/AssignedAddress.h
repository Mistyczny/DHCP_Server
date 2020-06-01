#pragma once
#include "DhcpDatagram.h"
#include <boost/asio.hpp>
#include <chrono>
#include <array>

using namespace std::chrono;
using namespace boost::asio::ip;

struct AssignedAddress {
    uint8_t leasingType;
    boost::asio::ip::address_v4 ip;
    std::chrono::system_clock::time_point assignationTime;
    std::array<unsigned char,MAX_DHCP_CHADDR_LENGTH> clientHardwareAddress;

    bool operator==(AssignedAddress& other) {
        if(this->ip != other.ip) return false;
        else if(this->clientHardwareAddress != other.clientHardwareAddress) return false;
        else return true;
    }
};

enum AssignationType{
    STATIC=0,
    SHORT_LEASING,
    LONG_LEASING
};

enum AssignationDurationInSeconds{
    SHORT_LEASING_TIME = 43200,
    LONG_LEASING_TIME = 86400
};