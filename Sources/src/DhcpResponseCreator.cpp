#include "DhcpResponseCreator.h"
#include "DhcpUtils.h"
#include "DhcpDefines.h"
#include <iostream>
#include <cstddef>
#include <algorithm>
#include <array>
#include "DhcpDatagramOptionsCreator.h"

DhcpResponseCreator::DhcpResponseCreator(DhcpDatagram* _clientDatagram, AssignedAddresses& _assignedAddresses):  clientDatagram{_clientDatagram},
                                                                                                                assignedAddresses{_assignedAddresses},
                                                                                                                responseDatagram{} {
    
    memset(&responseDatagram.bootFileName,0,sizeof(responseDatagram.bootFileName));
    memset(&responseDatagram.serverName,0,sizeof(responseDatagram.serverName));
    memset(&responseDatagram.hardwareAddress,0,sizeof(responseDatagram.hardwareAddress));
}

DhcpResponseCreator::~DhcpResponseCreator() {

}

void DhcpResponseCreator::writeCommon() {
    this->responseDatagram.operationCode = std::byte(DHCP_RESPONSE);
    this->responseDatagram.hops = std::byte(0);
    this->responseDatagram.secondsElapsed = 0;
    this->responseDatagram.flags = 0x8000;
}

std::set<std::byte> DhcpResponseCreator::readClientRequestedOptions() {
    std::set<std::byte> clientRequestedOptions{};
    std::optional<size_t> clientsRequestsPosition = DhcpUtils::findOptionPosition(clientDatagram->options,DHCP_Defines::OptionCode::ParameterList);
    if(clientsRequestsPosition.has_value()) {
        size_t howManyParameters = std::to_integer<size_t>(clientDatagram->options[*clientsRequestsPosition+1]);

        for(size_t readingPosition = *clientsRequestsPosition + 2; readingPosition < *clientsRequestsPosition + howManyParameters + 2; ++readingPosition) {
            clientRequestedOptions.insert(clientDatagram->options[readingPosition]);
        }
    } else {
        std::cout<<"NOT FOUND"<<std::endl;
    }
    
    return clientRequestedOptions;
}

DhcpDatagram& DhcpResponseCreator::getResponse() {
    return this->responseDatagram;
}

void DhcpResponseCreator::rewriteClientData() {
    this->responseDatagram.hardwareType = clientDatagram->hardwareType;
    this->responseDatagram.hardwareTypeLength = clientDatagram->hardwareTypeLength;
    this->responseDatagram.transactionID = clientDatagram->transactionID;
    this->responseDatagram.hardwareAddress = clientDatagram->hardwareAddress;
}