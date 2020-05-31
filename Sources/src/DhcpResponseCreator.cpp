#include "DhcpResponseCreator.h"
#include "DhcpUtils.h"
#include "DhcpDefines.h"
#include <iostream>
#include <cstddef>
#include <algorithm>
#include <array>

std::array<int,4> addressOctetsToInt(boost::asio::ip::address_v4 addr) {
    std::array<int,4> partials;
    std::string address = addr.to_string();

    for(size_t pos = 0; pos < 4; pos++) {
        size_t nextDot = address.find_first_of('.');
        if(nextDot != std::string::npos) {
            partials[pos] = std::stoi(address.substr(0,nextDot));
            address.erase(0,nextDot+1);
        } else partials[pos] = std::stoi(address);
    }

    return partials;
}

std::array<std::string,4> addressOctets(boost::asio::ip::address_v4 addr) {
    std::array<std::string,4> partials;
    std::string address = addr.to_string();

    for(size_t pos = 0; pos < 4; pos++) {
        size_t nextDot = address.find_first_of('.');
        if(nextDot != std::string::npos) {
            partials[pos] = address.substr(0,nextDot);
            address.erase(0,nextDot+1);
        } else partials[pos] = address;
    }

    return partials;
}

DhcpResponseCreator::DhcpResponseCreator(DhcpDatagram* _clientDatagram, AssignedAddresses& _assignedAddresses):  clientDatagram{_clientDatagram},
                                                                                                                assignedAddresses{_assignedAddresses},
                                                                                                                responseDatagram{},
                                                                                                                currentOptionsSpot{} {
    this->responseDatagram.operationCode = std::byte(DHCP_RESPONSE);
    this->responseDatagram.hops = std::byte(0);
    this->responseDatagram.secondsElapsed = 0;

    memset(&responseDatagram.bootFileName,0,sizeof(responseDatagram.bootFileName));
    memset(&responseDatagram.serverName,0,sizeof(responseDatagram.serverName));
    memset(&responseDatagram.hardwareAddress,0,sizeof(responseDatagram.hardwareAddress));

    this->rewriteClientData();
}

DhcpResponseCreator::~DhcpResponseCreator() {

}

bool DhcpResponseCreator::readClientRequestedOptions() {
    std::optional<size_t> clientsRequestsPosition = DhcpUtils::findOptionPosition(clientDatagram->options,DHCP_Defines::OptionCode::ParameterList);
    if(clientsRequestsPosition.has_value()) {
        size_t howManyParameters = std::to_integer<size_t>(clientDatagram->options[*clientsRequestsPosition+1]);

        for(size_t readingPosition = *clientsRequestsPosition + 2; readingPosition < *clientsRequestsPosition + howManyParameters + 2; ++readingPosition) {
            clientRequestedOptions.push_back(clientDatagram->options[readingPosition]);
        }
    }
    else return false;
}

DhcpDatagram& DhcpResponseCreator::getResponse() {
    return this->responseDatagram;
}

void DhcpResponseCreator::rewriteClientData() {
    this->responseDatagram.hardwareType = clientDatagram->hardwareType;
    this->responseDatagram.hardwareTypeLength = clientDatagram->hardwareTypeLength;
    this->responseDatagram.transactionID = clientDatagram->transactionID;
    this->responseDatagram.flags = clientDatagram->flags;
    this->responseDatagram.hardwareAddress = clientDatagram->hardwareAddress;
}

/* This function set DHCP standard magic values, it should never be changes */
void DhcpResponseCreator::setDhcpMagic() {
    this->responseDatagram.options[currentOptionsSpot++] = std::byte(99);
    this->responseDatagram.options[currentOptionsSpot++] = std::byte(130);
    this->responseDatagram.options[currentOptionsSpot++] = std::byte(83);
    this->responseDatagram.options[currentOptionsSpot++] = std::byte(99);
}

void DhcpResponseCreator::addDhcpMagicOption() {
    this->responseDatagram.options[currentOptionsSpot++] = std::byte(99);
    this->responseDatagram.options[currentOptionsSpot++] = std::byte(130);
    this->responseDatagram.options[currentOptionsSpot++] = std::byte(83);
    this->responseDatagram.options[currentOptionsSpot++] = std::byte(99);
}

void DhcpResponseCreator::addServerIdentifierOption() {
    Settings* settings = Settings::getInstance();
    std::array<int,4> partitionedAddress = addressOctetsToInt(settings->getServerSettings().networkServerAddress);

    this->responseDatagram.options[currentOptionsSpot++] = std::byte(54);
    this->responseDatagram.options[currentOptionsSpot++] = std::byte(4);

    for(size_t pos = 0; pos < 4; pos++) {
        this->responseDatagram.options[currentOptionsSpot++] = std::byte(partitionedAddress[pos]);
    }
}

void DhcpResponseCreator::addLeasingDurationOption() {
    this->responseDatagram.options[currentOptionsSpot++] = std::byte(51);
    this->responseDatagram.options[currentOptionsSpot++] = std::byte(4);
    
    /* For now leasing timer set at 1 day, in future might want make configureable */
    this->responseDatagram.options[currentOptionsSpot++] = std::byte(0);
    this->responseDatagram.options[currentOptionsSpot++] = std::byte(1);
    this->responseDatagram.options[currentOptionsSpot++] = std::byte(81);
    this->responseDatagram.options[currentOptionsSpot++] = std::byte(128);
}

void DhcpResponseCreator::addSubnetMaskOption() {
    Settings* settings = Settings::getInstance();
    std::array<int,4> partitionedAddress = addressOctetsToInt(settings->getNetworkSettings().subnetMask);

    this->responseDatagram.options[currentOptionsSpot++] = std::byte(1);
    this->responseDatagram.options[currentOptionsSpot++] = std::byte(4);

    for(size_t pos = 0; pos < 4; pos++) {
        this->responseDatagram.options[currentOptionsSpot++] = std::byte(partitionedAddress[pos]);
    }
}

void DhcpResponseCreator::addRouterAddressOption() {
    Settings* settings = Settings::getInstance();
    std::array<int,4> partitionedAddress = addressOctetsToInt(settings->getNetworkSettings().routerAddress);

    this->responseDatagram.options[currentOptionsSpot++] = std::byte(3);
    this->responseDatagram.options[currentOptionsSpot++] = std::byte(4);

    for(size_t pos = 0; pos < 4; pos++) {
        this->responseDatagram.options[currentOptionsSpot++] = std::byte(partitionedAddress[pos]);
    }
}

void DhcpResponseCreator::addDomainNameServerOption() {
    this->responseDatagram.options[currentOptionsSpot++] = std::byte(54);
    this->responseDatagram.options[currentOptionsSpot++] = std::byte(4);

    this->responseDatagram.options[currentOptionsSpot++] = std::byte(192);
    this->responseDatagram.options[currentOptionsSpot++] = std::byte(168);
    this->responseDatagram.options[currentOptionsSpot++] = std::byte(0);
    this->responseDatagram.options[currentOptionsSpot++] = std::byte(112);
}

void DhcpResponseCreator::addEndOptionBit() {
    this->responseDatagram.options[currentOptionsSpot] = std::byte(255);
}

void DhcpResponseCreator::addHostNameOption() {

}