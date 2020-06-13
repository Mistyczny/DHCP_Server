#include "AutomaticAddressAllocator.h"
#include <syslog.h>
#include "DhcpDatagram.h"
#include "Logger.h"
#include <iostream>

AutomaticAddressAllocator::AutomaticAddressAllocator(boost::asio::io_context& ioContext,AssignedAddresses& _assignedAddresses) :
                                                    ioContext{ioContext},receivedMessageHandler{_assignedAddresses},
                                                    socket{ioContext,boost::asio::ip::udp::endpoint{boost::asio::ip::udp::v4(), 67}} {
    boost::asio::socket_base::broadcast option(true);
    socket.set_option(option);
    socket.set_option(boost::asio::ip::udp::socket::reuse_address(true));
}

AutomaticAddressAllocator::~AutomaticAddressAllocator() {

}

void AutomaticAddressAllocator::listen() {
    std::size_t bytesRead{};

    for(;;) {
        this->receivedMessageHandler.clear();

        bytesRead = socket.receive_from(boost::asio::buffer(*receivedMessageHandler.getBuffer()), remoteEndpoint);
        if(bytesRead > 0 ) {
            this->datagramReceived(bytesRead);
        } else {
            Logging::ERROR("Failure on receive_from dhcp clients");
        }
    }
}

void AutomaticAddressAllocator::datagramReceived(std::size_t bytesRead) {
    if(receivedMessageHandler.createResponse()) {
        boost::asio::ip::udp::endpoint broadcastEnpoint(boost::asio::ip::address_v4::broadcast(), 68);

        if(socket.send_to(boost::asio::buffer(receivedMessageHandler.getResponseBuffer()),broadcastEnpoint) <= 0) {
            Logging::ERROR("Failure on sending message broadcast");
        } else {
            Logging::TRACE("Broadcast dhcp message have been sent");
        }
    } else {
        Logging::TRACE("Creating dhcp message failure");
    }
}