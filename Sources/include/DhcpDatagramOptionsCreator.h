#pragma once
#include "DhcpDatagram.h"
#include <iostream>
#include <queue>
#include <functional>
#include <array>
#include <vector>
#include <cstddef>

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
    public:
        DhcpDatagramOptionsCreator(std::array<std::byte,DHCP_OPTIONS_LENGTH>& datagramOptions_);
        ~DhcpDatagramOptionsCreator();

        bool writeOptions(std::vector<std::byte>& clientRequestedOptions);
};