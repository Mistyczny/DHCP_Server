#include "DhcpServer.h"
#include "DhcpConfigurationsReader.h"
#include <string>

DhcpServer::DhcpServer() :  ioContext{},
                            occupiedAddrs{},
                            addrAllocator{ioContext,occupiedAddrs}{
    DhcpConfigurationsReader reader;
    serverConfig = reader.getConfig();
}

DhcpServer::~DhcpServer(){

}

bool DhcpServer::startServices() {
    try{
        addrAllocator.start();

        std::thread th{[](OccupiedAddresses& addresses){
            LeasingMonitor monitor(addresses);
            monitor.run();
        },std::ref(occupiedAddrs)};
        th.detach();

        return true;
    } catch(std::exception& ex) {
        return false;
    }
}

void DhcpServer::run(){
    if(this->startServices())
        ioContext.run();
}