#include "DhcpDatagramOptionsCreator.h"
#include "DhcpDefines.h"
#include "Settings.h"
#include <iostream>

DhcpDatagramOptionsCreator::DhcpDatagramOptionsCreator(std::array<std::byte,DHCP_OPTIONS_LENGTH>& datagramOptions_) : datagramOptions{datagramOptions_} {
    this->setupHandlers();
}

DhcpDatagramOptionsCreator::~DhcpDatagramOptionsCreator(){

}

void DhcpDatagramOptionsCreator::setupHandlers() {
    requestsHandlers.push_back(&DhcpDatagramOptionsCreator::addHostNameOption);
    requestsHandlers.push_back(&DhcpDatagramOptionsCreator::addServerIdentifierOption);
}

bool DhcpDatagramOptionsCreator::writeOptions(std::vector<std::byte>& clientRequestedOptions) {
    this->addDhcpMagic();

    size_t writedOptions{};
    for(size_t reqOpt = 0; reqOpt < clientRequestedOptions.size(); ++reqOpt) {
        for(size_t index = 0; index < requestsHandlers.size(); ++index ) {
            if(requestsHandlers[index](this,clientRequestedOptions[reqOpt])) {
                writedOptions++;
                break;
            }
        }
    }

    return writedOptions == clientRequestedOptions.size();
}

void DhcpDatagramOptionsCreator::addDhcpMagic() {
    this->datagramOptions[currentOptionsSpot++] = std::byte(99);
    this->datagramOptions[currentOptionsSpot++] = std::byte(130);
    this->datagramOptions[currentOptionsSpot++] = std::byte(83);
    this->datagramOptions[currentOptionsSpot++] = std::byte(99);
}

bool DhcpDatagramOptionsCreator::addHostNameOption(std::byte requestedOption) {
    if(std::to_integer<size_t>(requestedOption) != DHCP_Defines::OptionCode::Hostname) return false;

    return true;
}

bool DhcpDatagramOptionsCreator::addServerIdentifierOption(std::byte requestedOption) {
    if(std::to_integer<size_t>(requestedOption) != DHCP_Defines::OptionCode::DhcpServerIdentifier) return false;

    return true;
}

bool DhcpDatagramOptionsCreator::addLeasingDurationOption(std::byte requestedOption) {
    if(std::to_integer<size_t>(requestedOption) != DHCP_Defines::OptionCode::LeasingAddressTime) return false;

    this->datagramOptions[currentOptionsSpot++] = std::byte(51);
    this->datagramOptions[currentOptionsSpot++] = std::byte(4);
    
    /* For now leasing timer set at 1 day, in future might want make configureable */
    this->datagramOptions[currentOptionsSpot++] = std::byte(0);
    this->datagramOptions[currentOptionsSpot++] = std::byte(1);
    this->datagramOptions[currentOptionsSpot++] = std::byte(81);
    this->datagramOptions[currentOptionsSpot++] = std::byte(128);

    return true;
}