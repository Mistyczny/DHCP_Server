#include "DhcpServer.h"
#include "LeasingMonitor.h"
#include <iostream>
#include "Settings.h"

DhcpServer::DhcpServer() :  ioContext{}, assignedAddresses{},
                            addrAllocator{ioContext,assignedAddresses} {
}

DhcpServer::~DhcpServer() {

}

void DhcpServer::loadServerSettings() {
    Settings* settings = Settings::getInstance();
    if(!settings->load()) {
        settings->setDefault();
        std::cout<<"Failed to load settings for server, default settings will be loaded but server might not work properly"<<std::endl;
    }
}

bool DhcpServer::startTasks() {
    bool tasksStarted = true;
    try {
        this->startAddressesAllocator();
        this->startTimersThread();
    } catch(std::exception& ex) {
        tasksStarted = false;
    }

    return tasksStarted;
}

void DhcpServer::startAddressesAllocator() {
    this->addrAllocator.listen();
}

void DhcpServer::startTimersThread() {
    std::thread th{[](AssignedAddresses& addresses){
        LeasingMonitor monitor(addresses);
        monitor.run();
    },std::ref(assignedAddresses)};

    th.detach();
}

void DhcpServer::run(){
    ioContext.run();
}