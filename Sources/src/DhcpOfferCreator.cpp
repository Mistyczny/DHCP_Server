#include "DhcpOfferCreator.h"
#include "DhcpDefines.h"
#include "DhcpDatagramOptionsCreator.h"
#include "Logger.h"
#include <optional>
#include <algorithm>

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
    bool added{false};
    auto iter = Settings::getInstance()->getNetworkSettings().addressesPool.begin();
    while(iter != Settings::getInstance()->getNetworkSettings().addressesPool.end()) {
        if(!assignedAddresses.contain(*iter)) {
            this->responseDatagram.offeredIpAddress = *iter;
            added = true;
        }
        iter++;
    }

    return added;
}