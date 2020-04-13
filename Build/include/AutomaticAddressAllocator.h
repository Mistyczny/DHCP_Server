#pragma once
#include <array>
#include <memory>
#include <boost/asio.hpp>
#include "AddressesElector.h"
#include "OccupiedAddresses.h"
#include "MessageHandler.h"

class AutomaticAddressAllocator{
    private:
        boost::asio::io_context& ioContext;
        boost::asio::ip::udp::socket socket;
        boost::asio::ip::udp::endpoint remoteEndpoint;
        AddressesElector addrsElector;

        void startReading();
        void datagramReceived(MessageHandler& newClient,std::size_t bytesRead);
    public:
        AutomaticAddressAllocator(boost::asio::io_context&,OccupiedAddresses&);
        ~AutomaticAddressAllocator();

        void start();
};