#include "DhcpOfferCreator.h"
#include "AddressesElector.h"
#include "ReservedAdresses.h"
#include <optional>
#include <algorithm>

DhcpOfferCreator::DhcpOfferCreator(DhcpDatagram* _clientDatagram, AssignedAddresses& _assignedAddresses) : DhcpResponseCreator{_clientDatagram, _assignedAddresses} {
    
}

DhcpOfferCreator::~DhcpOfferCreator() {

}

void DhcpOfferCreator::setMessageTypeOption() {
    this->responseDatagram.options[currentOptionsSpot++] = std::byte(DhcpDatagramTypes::Options::MessageType);
    this->responseDatagram.options[currentOptionsSpot++] = std::byte(1); /* Sizeof message */
    this->responseDatagram.options[currentOptionsSpot++] = std::byte(2); 
}

bool DhcpOfferCreator::create() {
    this->addClientAddress();
    this->setDhcpMagic();
    this->setMessageTypeOption();
    this->addServerIdentifierOption();
    this->addLeasingDurationOption();
    this->addSubnetMaskOption();
    this->addRouterAddressOption();
    this->addDomainNameServerOption();
    this->addEndOptionBit();
}

void DhcpOfferCreator::addClientAddress() {
    AddressesElector elector(assignedAddresses);
    std::optional<boost::asio::ip::address_v4> proposal = elector.proposeV4Address();
    if(proposal.has_value()) {
        this->responseDatagram.offeredIpAddress = *proposal;
    }
}