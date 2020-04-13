#pragma once
#include "DhcpConfigurations.h"
#include "OccupiedAddresses.h"
#include "AutomaticAddressAllocator.h"
#include "LeasingMonitor.h"
#include <boost/asio.hpp>

class DhcpServer{
    private:
        DhcpConfigurations serverConfig;
        boost::asio::io_context ioContext;
        OccupiedAddresses occupiedAddrs;
        AutomaticAddressAllocator addrAllocator;

        bool startServices();
    public:
        DhcpServer();
        ~DhcpServer();
        void run();
};