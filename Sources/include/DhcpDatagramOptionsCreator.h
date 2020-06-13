#pragma once
#include "DhcpDatagram.h"
#include <iostream>
#include <queue>
#include <functional>
#include <array>
#include <vector>
#include <cstddef>
#include <set>

class DhcpDatagramOptionsCreator {
    private:
        size_t currentOptionsSpot;
        std::vector<std::function<bool(DhcpDatagramOptionsCreator*,std::byte)>> requestsHandlers;
        std::array<std::byte,DHCP_OPTIONS_LENGTH>& datagramOptions;
        void setupHandlers();

        void addDhcpMagic();
        bool addHostNameOption(std::byte requestedOption);
        bool addServerIdentifierOption(std::byte requestedOption);
        bool addLeasingDurationOption(std::byte requestedOption);
        bool addSubnetMaskOption(std::byte requestedOption);
        bool addRouterAddressOption(std::byte requestedOption);
        bool addDNSAddressOption(std::byte requestedOption);
        void addMessageType(std::byte messageType);
        void addEndOptionBit();
    public:
        DhcpDatagramOptionsCreator(std::array<std::byte,DHCP_OPTIONS_LENGTH>& datagramOptions_);
        ~DhcpDatagramOptionsCreator();

        bool writeOptions(std::set<std::byte> clientRequestedOptions, std::byte messageType);
};