#pragma once
#include <boost/asio.hpp>
#include <set>
#include <mutex>
#include <array>
#include <chrono>
#include "DhcpDatagram.h"

struct ReservedAddress{
    boost::asio::ip::address ip;
    std::array<unsigned char,MAX_DHCP_CHADDR_LENGTH> clientHardwareAddress;
    std::chrono::system_clock::time_point assignationTime;

    bool operator==(ReservedAddress& other){
        if(ip != other.ip) return false;
        if(clientHardwareAddress != other.clientHardwareAddress) return false;
        return true;
    }
};

class ReservedAddresses{
    private:
        std::mutex locker;
        std::vector<ReservedAddress> reservedAddresses;
    public:
        ReservedAddresses();
        ~ReservedAddresses();

        void push_back(ReservedAddress&);
        void remove(ReservedAddress&);
        void remove(std::vector<ReservedAddress>::iterator iter);
        void remove_nolock(std::vector<ReservedAddress>::iterator iter);

        bool contain(boost::asio::ip::address addr);
};