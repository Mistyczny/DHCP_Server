#pragma once
#include "OccupiedAddresses.h"
#include "AssignedAddresses.h"
#include "AutomaticAddressAllocator.h"
#include <boost/asio.hpp>

class DhcpServer {
    private:
        boost::asio::io_context ioContext;
        AssignedAddresses assignedAddresses;
        AutomaticAddressAllocator addrAllocator;
        
        void startAddressesAllocator();
        void startTimersThread();
    public:
        DhcpServer();
        ~DhcpServer();

        void loadServerSettings();
        bool startTasks();
        void run();
};