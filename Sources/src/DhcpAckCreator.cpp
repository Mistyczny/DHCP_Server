#include "DhcpAckCreator.h"
#include "DhcpUtils.h"
#include "DhcpDatagramOptionsCreator.h"
#include "DhcpDefines.h"
#include <iostream>

DhcpAckCreator::DhcpAckCreator(DhcpDatagram* _clientDatagram, AssignedAddresses& _assignedAddresses) : DhcpResponseCreator{_clientDatagram, _assignedAddresses} {

}

DhcpAckCreator::~DhcpAckCreator() {

}

bool DhcpAckCreator::create() {
    this->writeCommon();
    this->rewriteClientData();

    if(!this->verifyClientAddress()) {
        std::cout<<"LOGGING ERR"<<std::endl;
    } else if(!this->addClientRequestedOptions()) {
        std::cout<<"LOGGING ERR"<<std::endl;
    } else {
        return true;
    }

    return false;
}

bool DhcpAckCreator::addClientRequestedOptions() {
    auto optionsToWrite = readClientRequestedOptions();
    optionsToWrite.insert(std::byte(DHCP_Defines::OptionCode::DhcpServerIdentifier));
    optionsToWrite.insert(std::byte(DHCP_Defines::OptionCode::LeasingAddressTime));

    DhcpDatagramOptionsCreator creator(responseDatagram.options);
    return creator.writeOptions(std::move(optionsToWrite),std::byte(DHCP_Defines::Offer));
}

bool DhcpAckCreator::verifyClientAddress() {
    std::optional<size_t> addrPosition = DhcpUtils::findOptionPosition(clientDatagram->options,DHCP_Defines::OptionCode::ParameterList);
    if(addrPosition.has_value()) {
        std::array<std::byte,4> address{};
        address[0] = clientDatagram->options[*addrPosition+2];
        address[1] = clientDatagram->options[*addrPosition+3];
        address[2] = clientDatagram->options[*addrPosition+4];
        address[3] = clientDatagram->options[*addrPosition+5];
        boost::asio::ip::address_v4 addr;
        AssignedAddress assigned;
        std::cout<<std::to_integer<int>(address[0])<<std::endl;
        std::cout<<std::to_integer<int>(address[1])<<std::endl;
        std::cout<<std::to_integer<int>(address[2])<<std::endl;
        std::cout<<std::to_integer<int>(address[3])<<std::endl;
        assigned.ip = DhcpUtils::stdByteArrayToAddress(address);
        assigned.clientHardwareAddress = clientDatagram->hardwareAddress;
        assigned.assignationTime = std::chrono::system_clock::now();
        assigned.leasingType = AssignationType::LONG_LEASING;
        this->responseDatagram.offeredIpAddress = assigned.ip;
        if(!assignedAddresses.contain(addr)) {
            assignedAddresses.push(assigned);
        }
        return true;
    }

    return false;
}