#include "MessageHandler.h"
#include "MessageError.h"
#include "DhcpDefines.h"
#include "HardwareType.h"
#include "DhcpOfferCreator.h"
#include "Settings.h"
#include <exception>
#include <iostream>
#include "DhcpAckCreator.h"
#include "Logger.h"
#include "DhcpUtils.h"
#include <optional>

MessageHandler::MessageHandler(AssignedAddresses& addrs) :  assignedAdddresses{addrs} {
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
}

bool MessageHandler::createResponse() {
    bool created{false};
    try{
        created = this->process();
    } catch (std::exception& ex) {
        std::string error{};
        Logging::ERROR("Exception catched:" + static_cast<std::string>(ex.what()));
    }

    return created;
}

bool MessageHandler::process() {
    bool processing{false};
    switch(std::to_integer<int>(datagram->operationCode)) {
        case DHCP_Defines::Client_message:
            processing = this->createServerResponse();
            break;
        case DHCP_Defines::Server_message:
            Logging::WARNING("Received message with server response opcode");
            break;
        default:
            Logging::WARNING("Received message with unkown opcode = "+std::to_string(std::to_integer<int>(datagram->operationCode)));
            break;
    }
    return processing;
}

bool MessageHandler::createServerResponse() {
    bool responseCreted{false};
    std::optional<size_t> messageTypePosition = DhcpUtils::findOptionPosition(datagram->options,DHCP_Defines::OptionCode::DhcpMessageType);
    if(messageTypePosition.has_value()) {
        switch(int messageType = std::to_integer<int>(datagram->options[*messageTypePosition]);messageType) {
            case DHCP_Defines::Discover:
                responseCreted = this->createOffer();
                break;
            case DHCP_Defines::Request:
                responseCreted = this->createAck();
                break;
            case DHCP_Defines::Release:
                responseCreted = this->onRelease();
                break;
        }
    }

    return responseCreted;
}

bool MessageHandler::createOffer() {
    DhcpOfferCreator offerCreator(datagram, assignedAdddresses);
    if(offerCreator.create()) {
        memcpy(&responseBuffer,&offerCreator.getResponse(),sizeof(DhcpDatagram));
        return true;
    }

    return false;
}

bool MessageHandler::createAck() {
    DhcpAckCreator ackCreator(datagram, assignedAdddresses);
    if(ackCreator.create()) {
        memcpy(&responseBuffer,&ackCreator.getResponse(),sizeof(DhcpDatagram));
        return true;
    }

    return false;
}

bool MessageHandler::onRelease() {
    /* Not implemented yet */
    return false;
}

std::array<char,sizeof(DhcpDatagram)>& MessageHandler::getResponseBuffer() {
    return this->responseBuffer;
}