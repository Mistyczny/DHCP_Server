#include "AddressesElector.h"

AddressesElector::AddressesElector(OccupiedAddresses& addrs): occuppiedAdddresses{addrs}{

}

AddressesElector::~AddressesElector(){

}

boost::asio::ip::address_v4 AddressesElector::proposeV4Address(){
    //boost::asio::ip::address_v4 proposedAddress = addressesRangeV4.beginAddress;

    for(auto iter = addressesRangeV4.begin(); iter!= addressesRangeV4.end(); iter++){
        if(occuppiedAdddresses.assignedAddrs.contain(*iter)){
            continue;
        }
    }
}

boost::asio::ip::address_v6 AddressesElector::proposeV6Address(){

}