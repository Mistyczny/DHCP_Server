#include "ReservedAdresses.h"

ReservedAddresses::ReservedAddresses(){
    /* Reserve some memory to avoid not neccessary copying while adding new elements */
    reservedAddresses.reserve(5);
}

ReservedAddresses::~ReservedAddresses(){

}

void ReservedAddresses::push_back(ReservedAddress& addr){
    std::scoped_lock lock{locker};
    reservedAddresses.push_back(std::move(addr));
}

void ReservedAddresses::remove(ReservedAddress& addrToRemove){
    std::scoped_lock lock{locker};

    for(auto iter = reservedAddresses.begin(); iter != reservedAddresses.end();iter++){
        if(*iter == addrToRemove) {
            this->remove_nolock(iter);
        }
    }
}

void ReservedAddresses::remove(std::vector<ReservedAddress>::iterator iter){
    std::scoped_lock lock{locker};
    this->remove_nolock(iter);
}

void ReservedAddresses::remove_nolock(std::vector<ReservedAddress>::iterator iter){
    if( iter != std::end(reservedAddresses)) {
        *iter = std::move(reservedAddresses.back());
        reservedAddresses.pop_back();
    }
}

bool ReservedAddresses::contain(boost::asio::ip::address addr){
    std::scoped_lock lock{locker};
    bool found{false};

    for(std::vector<ReservedAddress>::iterator iter = reservedAddresses.begin(); iter!=reservedAddresses.end();iter++){
        if((*iter).ip == addr) {
            found = true;
            break;
        }
    }

    return found;
}

bool ReservedAddresses::try_lock() {
    return locker.try_lock();
}

void ReservedAddresses::unlock() {
    locker.unlock();
}