#include "MessageHandler.h"
#include "MessageError.h"
#include "DhcpDefines.h"
#include "HardwareType.h"
#include "DhcpOfferCreator.h"
#include "Settings.h"
#include <exception>
#include <iostream>
#include "DhcpAckCreator.h"

MessageHandler::MessageHandler(AssignedAddresses& addrs) :  errorCode{},
                                                            assignedAdddresses{addrs} {
    datagram = reinterpret_cast<DhcpDatagram*>(&recvBuffer);
    this->clear();
}

MessageHandler::~MessageHandler() {

}

std::array<char,1024>* MessageHandler::getBuffer() {
    return &recvBuffer;
}

void MessageHandler::clear() {
    memset(&recvBuffer,0,sizeof(recvBuffer));
    memset(&responseBuffer, 0, sizeof(responseBuffer));
    errorCode = 0;
}

bool MessageHandler::createResponse() {
    try{
        this->process();
    } catch (std::exception& ex) {
        this->errorCode = MessageError::UNKOWN_ERROR;
    }

    return true;
}

void MessageHandler::process() {
    switch(std::to_integer<int>(datagram->operationCode)) {
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

void MessageHandler::createServerResponse() {
    switch(int messageType = std::to_integer<int>(datagram->options[6]);messageType){
        case DHCP_Defines::Discover:
            std::cout<<"DISCOVER"<<std::endl;
            this->onDiscover();
            break;
        case DHCP_Defines::Request:
        this->errorCode = 1;
            std::cout<<"REQUEST"<<std::endl;
            this->onRequest();
            break;
        case DHCP_Defines::Release:
         this->errorCode = 2;
            std::cout<<"RELEASE"<<std::endl;
            this->onRelease();
            break;
        default:
            return;
    }
}

void MessageHandler::onDiscover() {
    DhcpOfferCreator offerCreator(datagram, assignedAdddresses);
    if(offerCreator.create()) {
        memcpy(&responseBuffer,&offerCreator.getResponse(),sizeof(DhcpDatagram));
    }
}

void MessageHandler::onRequest() {
    DhcpAckCreator ackCreator(datagram, assignedAdddresses);
    if(ackCreator.create()) {
        memcpy(&responseBuffer,&ackCreator.getResponse(),sizeof(DhcpDatagram));
    }
}

void MessageHandler::onRelease(){

}

std::array<char,sizeof(DhcpDatagram)>& MessageHandler::getResponseBuffer() {
    for(int i=0;i<responseBuffer.size();i++) {
        std::cout<<responseBuffer[i];
    }
    std::cout<<"\n";
    DhcpDatagram* dt = reinterpret_cast<DhcpDatagram*>(&responseBuffer);
    std::cout<<"OP CODE: "<<std::to_integer<int>(dt->operationCode)<<std::endl;
    return this->responseBuffer;
}