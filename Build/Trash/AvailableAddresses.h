#pragma once
#include <mutex>
#include <set>
#include <netinet/in.h>
#include <boost/asio.hpp>

using namespace boost::asio::ip;

class AvailableAddresses{
    private:
        mutable std::mutex locker;
        std::set<address_v4> avaiableAddresses;
    public:
        AvailableAddresses();
        ~AvailableAddresses();
        void lock();
        void unlock();

        bool emplace(address_v4& address);
        bool emplace_nolock(address_v4& address);

        bool erase(std::set<address_v4>::iterator iter);
        bool erase_nolock(std::set<address_v4>::iterator iter);

        size_t size() const;
};