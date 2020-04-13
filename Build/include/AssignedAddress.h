#pragma once
#include <boost/asio.hpp>
#include <chrono>
#include <iostream>
#include <array>
#include "DhcpDatagram.h"

using namespace std::chrono;
using namespace boost::asio::ip;

struct AssignedAddress{
    uint16_t leasingType;
    boost::asio::ip::address ip;
    std::array<unsigned char,MAX_DHCP_CHADDR_LENGTH> clientHardwareAddress;
    std::chrono::system_clock::time_point assignationTime;
};

enum AssignationType{
    STATIC=0,
    SHORT_LEASING,
    LONG_LEASING
};

enum AssignationDurationInSeconds{
    SHORT_LEASING_TIME = 5,
    LONG_LEASING_TIME = 20
};