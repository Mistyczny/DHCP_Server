#include "PartitionedNetworkAddress.h"
#include <exception>

std::string PartitionedNetworkAddress::getFullAddressAsString(){
    std::string fullAddr;
        
    for(int i=0;i<3;i++){
        fullAddr+= std::to_string(octets[i]);
        fullAddr+=".";
    }
    fullAddr+=std::to_string(octets[3]);
    return fullAddr;
}

bool PartitionedNetworkAddress::partitionNetworkAddress(std::string& partition){
    try{
        size_t pos{};
        for(int i=0;i<3;i++){
            pos = partition.find_first_of(".");
            octets[i] = std::stoul(partition.substr(0,pos));
            partition.erase(0,pos+1);
        }
        octets[3] = std::stoul(partition.substr(0));
        return true;
    } catch(std::exception& ex){
        return false;
    }
}