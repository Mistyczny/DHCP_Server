#include "AddressesElector.h"
#include "Settings.h"

AddressesElector::AddressesElector(AssignedAddresses& addrs): assignedAdddresses{addrs}{
    addressesRangeV4 = Settings::getInstance()->getNetworkSettings().addressesPool;
}

AddressesElector::~AddressesElector() {

}

std::optional<boost::asio::ip::address_v4> AddressesElector::proposeV4Address() {
    for(auto iter = addressesRangeV4.begin(); iter!= addressesRangeV4.end(); iter++){
        if(assignedAdddresses.contain(*iter)){
            continue;
        } else return boost::asio::ip::address_v4{*iter};
    }

    return {};
}