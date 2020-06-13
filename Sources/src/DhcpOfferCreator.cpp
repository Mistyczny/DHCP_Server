#include "DhcpOfferCreator.h"
#include "AddressesElector.h"
#include "DhcpDefines.h"
#include "DhcpDatagramOptionsCreator.h"
#include <optional>
#include <algorithm>
#include <iostream>
#include "Logger.h"

DhcpOfferCreator::DhcpOfferCreator(DhcpDatagram* _clientDatagram, AssignedAddresses& _assignedAddresses) : DhcpResponseCreator{_clientDatagram, _assignedAddresses} {

}

DhcpOfferCreator::~DhcpOfferCreator() {

}

bool DhcpOfferCreator::create() {
    this->writeCommon();
    this->rewriteClientData();
    if(!this->addClientAddress()) {
        Logging::ERROR("Failure during electing address for client");
    } else if(!this->addClientRequestedOptions()) {
        Logging::ERROR("Failure during writing datagram options");
    } else {
        return true;
    }

    return false;
}

bool DhcpOfferCreator::addClientRequestedOptions() {
    auto optionsToWrite = readClientRequestedOptions();
    optionsToWrite.insert(std::byte(DHCP_Defines::OptionCode::DhcpServerIdentifier));
    optionsToWrite.insert(std::byte(DHCP_Defines::OptionCode::LeasingAddressTime));

    DhcpDatagramOptionsCreator creator(responseDatagram.options);
    return creator.writeOptions(std::move(optionsToWrite),std::byte(DHCP_Defines::Offer));
}

bool DhcpOfferCreator::addClientAddress() {
    AddressesElector elector(assignedAddresses);
    std::optional<boost::asio::ip::address_v4> proposal = elector.proposeV4Address();
    if(proposal.has_value()) {
        this->responseDatagram.offeredIpAddress = *proposal;
        return true;
    }
    return false;
}