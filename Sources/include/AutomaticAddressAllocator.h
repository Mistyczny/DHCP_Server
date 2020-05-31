#pragma once
#include <array>
#include <memory>
#include <boost/asio.hpp>
#include "AssignedAddresses.h"
#include "MessageHandler.h"

class AutomaticAddressAllocator{
    private:
        boost::asio::io_context& ioContext;
        boost::asio::ip::udp::socket socket;
        boost::asio::ip::udp::endpoint remoteEndpoint;
        MessageHandler receivedMessageHandler;

        void startReading();
        void datagramReceived(std::size_t bytesRead);
    public:
        AutomaticAddressAllocator(boost::asio::io_context&,AssignedAddresses&);
        ~AutomaticAddressAllocator();
        
        void listen();
};