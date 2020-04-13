#pragma once
#include "AssignedAddress.h"
#include <boost/asio.hpp>
#include <vector>
#include <deque>
#include <mutex>
#include <memory>
#include <iostream>

/*
 * Class is customized to hold addresses already assigned to new devices
 * 
 * In the future might use std::map instead of std::vector
 */

class AssignedAddresses{
    private:
        mutable std::mutex locker;
        std::vector<AssignedAddress> addrStorage;
    public:
        AssignedAddresses();
        ~AssignedAddresses();

        void lock();
        void unlock();
        
        std::vector<AssignedAddress>& getAddrStorage();
        bool push(AssignedAddress&);
        bool remove(boost::asio::ip::address_v4 removeWithAddress);
        std::vector<AssignedAddress>::iterator remove_nolock(std::vector<AssignedAddress>::iterator removeWithAddress);
        size_t size() const;
        size_t size_nolock() const;

        AssignedAddress* operator[](size_t index){
            return &addrStorage[index];
        }

        bool contain(boost::asio::ip::address addr);
};