#pragma once
#include "DhcpDatagram.h"
#include "AssignedAddresses.h"
#include "Settings.h"
#include <boost/asio.hpp>
#include <iostream>
#include <vector>
#include <set>

class DhcpResponseCreator {
    protected:
        DhcpDatagram* clientDatagram;
        DhcpDatagram responseDatagram;
        size_t currentOptionsSpot;
        AssignedAddresses& assignedAddresses;

        std::set<std::byte> readClientRequestedOptions();
        virtual bool addClientRequestedOptions() = 0;
        void writeCommon();
    public:
        DhcpResponseCreator(DhcpDatagram* _clientDatagram, AssignedAddresses& _assignedAddresses);
        virtual ~DhcpResponseCreator();

        virtual bool create() = 0;
        virtual void rewriteClientData();
        DhcpDatagram& getResponse();
};