#include "AvailableAddresses.h"
#include <exception>

AvailableAddresses::AvailableAddresses(){

}

AvailableAddresses::~AvailableAddresses(){

}

void AvailableAddresses::lock(){
    this->locker.lock();
}

void AvailableAddresses::unlock(){
    this->locker.unlock();
}

bool AvailableAddresses::emplace(address_v4& address){
    std::scoped_lock lock(locker);
    return this->emplace_nolock(address);
}

bool AvailableAddresses::emplace_nolock(address_v4& address){
    auto [pointer,emplaced] = this->avaiableAddresses.emplace(address);
    return emplaced;
}

bool AvailableAddresses::erase(std::set<address_v4>::iterator iter) {
    std::scoped_lock lock(locker);
    return this->erase_nolock(iter);
}

bool AvailableAddresses::erase_nolock(std::set<address_v4>::iterator iter) {
    try{
        avaiableAddresses.erase(iter);
        return true;
    } catch(std::exception& ex){
        return false;
    }
}

size_t AvailableAddresses::size() const{
    std::scoped_lock lock(locker);
    return this->avaiableAddresses.size();
}