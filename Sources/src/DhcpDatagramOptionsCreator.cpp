#include "DhcpDatagramOptionsCreator.h"
#include "DhcpDefines.h"
#include "Settings.h"
#include "DhcpUtils.h"
#include <algorithm>

DhcpDatagramOptionsCreator::DhcpDatagramOptionsCreator(std::array<std::byte,DHCP_OPTIONS_LENGTH>& datagramOptions_):currentOptionsSpot{0},
                                                                                                                    datagramOptions{datagramOptions_} {
    this->setupHandlers();
}

DhcpDatagramOptionsCreator::~DhcpDatagramOptionsCreator(){

}

void DhcpDatagramOptionsCreator::setupHandlers() {
    requestsHandlers.push_back(&DhcpDatagramOptionsCreator::addSubnetMaskOption);
    requestsHandlers.push_back(&DhcpDatagramOptionsCreator::addRouterAddressOption);
    requestsHandlers.push_back(&DhcpDatagramOptionsCreator::addDNSAddressOption);
    requestsHandlers.push_back(&DhcpDatagramOptionsCreator::addHostNameOption);
    requestsHandlers.push_back(&DhcpDatagramOptionsCreator::addServerIdentifierOption);
    requestsHandlers.push_back(&DhcpDatagramOptionsCreator::addLeasingDurationOption);
}

bool DhcpDatagramOptionsCreator::writeOptions(std::set<std::byte> clientRequestedOptions, std::byte messageType) {
    this->addDhcpMagic();
    this->addMessageType(messageType);
    size_t writedOptions{};
    std::for_each(clientRequestedOptions.begin(), clientRequestedOptions.end(), [&](const std::byte& option) {
        for(size_t index = 0; index < requestsHandlers.size(); ++index ) {
            if(requestsHandlers[index](this,option)) {
                writedOptions++;
                break;
            }
        }
    });
    this->addEndOptionBit();

    return writedOptions == clientRequestedOptions.size();
}

void DhcpDatagramOptionsCreator::addDhcpMagic() {
    this->datagramOptions[currentOptionsSpot++] = std::byte(99);
    this->datagramOptions[currentOptionsSpot++] = std::byte(130);
    this->datagramOptions[currentOptionsSpot++] = std::byte(83);
    this->datagramOptions[currentOptionsSpot++] = std::byte(99);
}

void DhcpDatagramOptionsCreator::addMessageType(std::byte messageType) {
    this->datagramOptions[currentOptionsSpot++] = std::byte(DHCP_Defines::OptionCode::DhcpMessageType);
    this->datagramOptions[currentOptionsSpot++] = std::byte(1);
    this->datagramOptions[currentOptionsSpot++] = std::byte(messageType);
}

bool DhcpDatagramOptionsCreator::addHostNameOption(std::byte requestedOption) {
    if(std::to_integer<size_t>(requestedOption) != DHCP_Defines::OptionCode::Hostname) return false;

    return true;
}

bool DhcpDatagramOptionsCreator::addServerIdentifierOption(std::byte requestedOption) {
    if(std::to_integer<size_t>(requestedOption) != DHCP_Defines::OptionCode::DhcpServerIdentifier) {
        return false;
    } else if(currentOptionsSpot + 6 > DHCP_OPTIONS_LENGTH) {
        return false;
    }
    Settings* settings = Settings::getInstance();
    std::array<int,4> partitionedAddress = DhcpUtils::addressToIntParts(settings->getServerSettings().networkServerAddress);
    this->datagramOptions[currentOptionsSpot++] = std::byte(DHCP_Defines::OptionCode::DhcpServerIdentifier);
    this->datagramOptions[currentOptionsSpot++] = std::byte(4);

    for(size_t pos = 0; pos < 4; pos++) {
        this->datagramOptions[currentOptionsSpot++] = std::byte(partitionedAddress[pos]);
    }

    return true;
}

bool DhcpDatagramOptionsCreator::addLeasingDurationOption(std::byte requestedOption) {
    if(std::to_integer<size_t>(requestedOption) != DHCP_Defines::OptionCode::LeasingAddressTime) {
        return false;
    } else if(currentOptionsSpot + 6 > DHCP_OPTIONS_LENGTH) {
        return false;
    }

    this->datagramOptions[currentOptionsSpot++] = std::byte(DHCP_Defines::OptionCode::LeasingAddressTime);
    this->datagramOptions[currentOptionsSpot++] = std::byte(4);
    
    /* For now leasing timer set at 1 day, in future might want make configureable */
    this->datagramOptions[currentOptionsSpot++] = std::byte(0);
    this->datagramOptions[currentOptionsSpot++] = std::byte(1);
    this->datagramOptions[currentOptionsSpot++] = std::byte(81);
    this->datagramOptions[currentOptionsSpot++] = std::byte(128);

    return true;
}

bool DhcpDatagramOptionsCreator::addSubnetMaskOption(std::byte requestedOption) {
    if(std::to_integer<size_t>(requestedOption) != DHCP_Defines::OptionCode::SubnetMask) {
        return false;
    } else if(currentOptionsSpot + 6 > DHCP_OPTIONS_LENGTH) {
        return false;
    }

    Settings* settings = Settings::getInstance();
    std::array<int,4> partitionedAddress = DhcpUtils::addressToIntParts(settings->getNetworkSettings().subnetMask);

    this->datagramOptions[currentOptionsSpot++] = std::byte(DHCP_Defines::OptionCode::SubnetMask);
    this->datagramOptions[currentOptionsSpot++] = std::byte(4);

    for(size_t pos = 0; pos < 4; pos++) {
        this->datagramOptions[currentOptionsSpot++] = std::byte(partitionedAddress[pos]);
    }

    return true;
}

bool DhcpDatagramOptionsCreator::addRouterAddressOption(std::byte requestedOption) {
    if(std::to_integer<size_t>(requestedOption) != DHCP_Defines::OptionCode::RouterAddress) {
        return false;
    } else if(currentOptionsSpot + 6 > DHCP_OPTIONS_LENGTH) {
        return false;
    }

    Settings* settings = Settings::getInstance();
    std::array<int,4> partitionedAddress = DhcpUtils::addressToIntParts(settings->getNetworkSettings().routerAddress);

    this->datagramOptions[currentOptionsSpot++] = std::byte(DHCP_Defines::OptionCode::RouterAddress);
    this->datagramOptions[currentOptionsSpot++] = std::byte(4);

    for(size_t pos = 0; pos < 4; pos++) {
        this->datagramOptions[currentOptionsSpot++] = std::byte(partitionedAddress[pos]);
    }

    return true;
}

bool DhcpDatagramOptionsCreator::addDNSAddressOption(std::byte requestedOption) {
    if(std::to_integer<size_t>(requestedOption) != DHCP_Defines::OptionCode::DnsServerAddress) {
        return false;
    } else if(currentOptionsSpot + 6 > DHCP_OPTIONS_LENGTH) {
        return false;
    }

    this->datagramOptions[currentOptionsSpot++] = std::byte(DHCP_Defines::OptionCode::DnsServerAddress);
    this->datagramOptions[currentOptionsSpot++] = std::byte(4);

    this->datagramOptions[currentOptionsSpot++] = std::byte(192);
    this->datagramOptions[currentOptionsSpot++] = std::byte(168);
    this->datagramOptions[currentOptionsSpot++] = std::byte(0);
    this->datagramOptions[currentOptionsSpot++] = std::byte(112);

    return true;
}

void DhcpDatagramOptionsCreator::addEndOptionBit() {
    this->datagramOptions[DHCP_OPTIONS_LENGTH-1] = std::byte(255);
}