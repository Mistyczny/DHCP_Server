#pragma once
#include "DhcpDatagram.h"
#include "AssignedAddresses.h"
#include "Settings.h"
#include <boost/asio.hpp>
#include <iostream>
#include <vector>

class DhcpResponseCreator {
    protected:
        DhcpDatagram* clientDatagram;
        DhcpDatagram responseDatagram;

        size_t currentOptionsSpot;
        std::vector<std::byte> clientRequestedOptions;
        AssignedAddresses& assignedAddresses;

        void setDhcpMagic();
        void addDhcpMagicOption();
        void addHostNameOption();
        void addServerIdentifierOption();
        void addLeasingDurationOption();
        void addSubnetMaskOption();
        void addRouterAddressOption();
        void addDomainNameServerOption();
        void addEndOptionBit();

        bool readClientRequestedOptions();
        bool addClientRequestedOptions();
    public:
        DhcpResponseCreator(DhcpDatagram* _clientDatagram, AssignedAddresses& _assignedAddresses);
        virtual ~DhcpResponseCreator();

        virtual bool create() = 0;
        virtual void rewriteClientData();
        virtual void setMessageTypeOption() = 0;
        DhcpDatagram& getResponse();
};