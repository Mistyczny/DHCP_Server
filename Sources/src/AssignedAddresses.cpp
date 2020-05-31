#include "AssignedAddresses.h"
#include <iostream>

AssignedAddresses::AssignedAddresses() {

}

AssignedAddresses::~AssignedAddresses() {

}

void AssignedAddresses::lock() {
    this->locker.lock();
}

void AssignedAddresses::unlock() {
    this->locker.unlock();
}

std::vector<AssignedAddress>& AssignedAddresses::getAddrStorage(){
    return addrStorage;
}

bool AssignedAddresses::push(AssignedAddress& addrToAssign) {
    std::scoped_lock lock{locker};
    addrStorage.push_back(std::move(addrToAssign));
    return true;
}

bool AssignedAddresses::remove(boost::asio::ip::address_v4 removeWithAddress) {
    std::scoped_lock lock{locker};
    if(addrStorage.empty()) return false;

    /* Search and remove provided in_addr */
    for(std::vector<AssignedAddress>::iterator iter =  addrStorage.begin();iter<addrStorage.end();iter++){
        if(iter->ip == removeWithAddress) {
            addrStorage.erase(iter);
            return true;
        }
    }

    /* Return false if given in_addr is not found in storage*/
    return false;
}

std::vector<AssignedAddress>::iterator AssignedAddresses::remove_nolock(const std::vector<AssignedAddress>::iterator iter) {
    std::vector<AssignedAddress>::iterator it;
    it = addrStorage.erase(iter);
    return it;
}

size_t AssignedAddresses::size() const {
    std::scoped_lock lock{locker};
    return this->addrStorage.size();
}

size_t AssignedAddresses::size_nolock() const {
    return this->addrStorage.size();
}

bool AssignedAddresses::contain(boost::asio::ip::address_v4 addr){
    std::scoped_lock lock{locker};
    bool found{false};

    for(std::vector<AssignedAddress>::iterator iter = addrStorage.begin(); iter!=addrStorage.end();iter++){
        if(iter->ip == addr) {
            found = true;
            break;
        }
    }

    return found;
}