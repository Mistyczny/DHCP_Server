#include "AutomaticAddressAllocator.h"
#include "DhcpDatagram.h"

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
        std::cout<<"THERE IS A AMESSAGE"<<std::endl;
        if(bytesRead > 0 ) {
            this->datagramReceived(bytesRead);
        } else {
            std::cout<<"Error during listening on socket"<<std::endl;
        }
    }
}

void AutomaticAddressAllocator::datagramReceived(std::size_t bytesRead) {
    if(receivedMessageHandler.createResponse()) {
        boost::asio::ip::udp::endpoint ep(boost::asio::ip::address_v4::broadcast(), 68);

        if(socket.send_to(boost::asio::buffer(receivedMessageHandler.getResponseBuffer()),ep) <= 0) {
            std::cout<<"Failed to send response message"<<std::endl;
        } else std::cout<<"SEND MESSAGE"<<std::endl;
    } else {
        std::cout<<"Failed to create response message"<<std::endl;
    }
}