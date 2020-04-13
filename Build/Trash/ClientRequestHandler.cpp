#include "HardwareType.h"

#include "ClientRequestHandler.h"
#include <exception>
#include <string>
#include <iostream>
#include <array>
#include "DhcpDefines.h"
#include "MessageError.h"

ClientRequestHandler::ClientRequestHandler(NetworkAddresses& networkAddr) : addresses{networkAddr},errorCode{-1}{
    datagram = reinterpret_cast<DhcpDatagram*>(&recvBuffer);
}

ClientRequestHandler::~ClientRequestHandler(){
    datagram = nullptr;
}

std::array<char,548>* ClientRequestHandler::getBuffer(){
    return &recvBuffer;
}

bool ClientRequestHandler::processDatagram(){
    try{
        this->process();
    } catch(std::exception& ex){
        this->handleException(ex);
        //errorCode = true;
    }

    return errorCode;
}

void ClientRequestHandler::handleException(std::exception& ex) {
    std::cout<<ex.what()<<std::endl;
}

void ClientRequestHandler::process() {
    this->rewriteDataToResponse();

    std::cout<<"THIS IS VALUE OF BYTE: "<<std::to_integer<int>(datagram->operationCode)<<std::endl;

    switch(std::to_integer<int>(datagram->operationCode)){
        case DHCP_Defines::Client_message:
            this->onReplyMessage();
            break;
        case DHCP_Defines::Server_message:
            errorCode = MessageError::SERVER_RECEIVED_RESPONSE_OPCODE;
            return;
        default:
            errorCode = MessageError::WRONG_OPCODE_CODE;
    }
}

void ClientRequestHandler::setResponseHardwareType(){
    if(HardwareTypes::isCorrect(datagram->hardwareType)){
        this->responseDatagram.hardwareType = datagram->hardwareType;
        this->responseDatagram.hardwareTypeLength = datagram->hardwareTypeLength;
    } else {
        errorCode = true;
    }
}

void ClientRequestHandler::rewriteDataToResponse(){
    datagramResponse.transactionID = static_cast<uint32_t>(datagram->transactionID);
    datagramResponse.hardwareAddress = datagram->hardwareAddress;
    datagramResponse.hardwareTypeLength = datagram->hardwareTypeLength;
}

void ClientRequestHandler::fillWithDynamicData(){
    datagramResponse.hops = std::byte(0);
    datagramResponse.secondsElapsed = 0;
}

bool ClientRequestHandler::isClientAddressProvided(){
    //return datagram->currentIpAddress.s_addr==0;
}

void ClientRequestHandler::onReplyMessage(){
    if(!isClientAddressProvided()){
        this->onClientWithoutAddress();
    } else {

    }

    std::cout<<"Transaction: "<<datagramResponse.transactionID<<std::endl;
    std::cout<<"hardwareTypeLen: "<<std::to_integer<int>(datagramResponse.hardwareTypeLength)<<std::endl;
    std::cout<<"hardwareAddr: ";
    for(int i=0;i<datagramResponse.hardwareAddress.size();i++){
        std::cout<<datagramResponse.hardwareAddress[i];
    }
    std::cout<<'\n';
}

void ClientRequestHandler::onRequestMessage(){
    std::cout<<"Transaction: "<<datagramResponse.transactionID<<std::endl;
}

void ClientRequestHandler::onClientWithoutAddress(){
    
}