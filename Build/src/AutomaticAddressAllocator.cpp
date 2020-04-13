#include "AutomaticAddressAllocator.h"
#include "DhcpDatagram.h"


AutomaticAddressAllocator::AutomaticAddressAllocator(boost::asio::io_context& ioContext,OccupiedAddresses& occupiedAddrs) :
                                                    ioContext{ioContext},addrsElector{occupiedAddrs},
                                                    socket{ioContext,boost::asio::ip::udp::endpoint{boost::asio::ip::udp::v4(), 8004}}{

}

AutomaticAddressAllocator::~AutomaticAddressAllocator(){
}

void AutomaticAddressAllocator::start() {
    this->startReading();
}

void AutomaticAddressAllocator::startReading() {
    MessageHandler newClient{addrsElector};
    std::size_t bytesRead = socket.receive_from(boost::asio::buffer(*newClient.getBuffer()), remoteEndpoint);

    this->datagramReceived(newClient,bytesRead);
    this->startReading();
}

void AutomaticAddressAllocator::datagramReceived(MessageHandler& newClient,std::size_t bytesRead){
    if(newClient.createResponse()){

    }
}