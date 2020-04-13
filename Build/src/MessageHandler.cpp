#include "MessageHandler.h"
#include "MessageError.h"
#include "DhcpDefines.h"
#include "MessageUtilities.h"
#include "HardwareType.h"
#include <exception>
#include <iostream>

MessageHandler::MessageHandler(AddressesElector& addr) :    errorCode{},
                                                            occupiedAddrs{addr}{
    datagram = reinterpret_cast<DhcpDatagram*>(&recvBuffer);
}

MessageHandler::~MessageHandler(){

}

std::array<char,548>* MessageHandler::getBuffer() {
    return &recvBuffer;
}

DhcpDatagram& MessageHandler::getResponse(){
    return responseDatagram;
}

bool MessageHandler::createResponse(){
    try{
        this->process();
    } catch (std::exception& ex) {
        this->errorCode = MessageError::UNKOWN_ERROR;
    }

    return !errorCode;
}

void MessageHandler::process(){
    switch(int opCode = std::to_integer<int>(datagram->operationCode); opCode){
        case DHCP_Defines::Client_message:
            this->createServerResponse();
            break;
        case DHCP_Defines::Server_message:
            this->errorCode = MessageError::SERVER_RECEIVED_RESPONSE_OPCODE;
            return;
        default:
            this->errorCode = MessageError::WRONG_OPCODE_CODE;
            return;
    }
}

void MessageHandler::createServerResponse(){
    if(!this->setResponseConstantParameters()) {
        return;
    }

    switch(datagram->options[53]){
        case DHCP_Defines::Discover:
            this->onDiscover();
            break;
        case DHCP_Defines::Request:
            this->onRequest();
            break;
        case DHCP_Defines::Release:
            this->onRelease();
            break;
        default:
            return;
    }

}

bool MessageHandler::setResponseConstantParameters() {
    this->responseDatagram.operationCode = std::byte(DHCP_Defines::Server_message);

    if(HardwareTypes::isCorrect(this->datagram->hardwareType)){
        this->responseDatagram.hardwareType = this->datagram->hardwareType;
        this->responseDatagram.hardwareTypeLength = this->datagram->hardwareTypeLength;
    } else {
        this->errorCode = MessageError::BAD_HARDWARE_TYPE_CODE;
        return false;
    }

    this->responseDatagram.hops = std::byte(0);
    this->responseDatagram.transactionID = datagram->transactionID;
    this->responseDatagram.secondsElapsed = 0;

    return true;
}

void MessageHandler::assignClientNewAddress() {
   // boost::asio::ip::address offeringAddr{occupiedAddrs.nextAddrProposal};
}

void MessageHandler::onDiscover() {
    
}

void MessageHandler::onRequest(){

}

void MessageHandler::onRelease(){

}