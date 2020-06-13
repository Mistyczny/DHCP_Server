#pragma once
#include "DhcpResponseCreator.h"
#include "DhcpDatagram.h"
#include "OccupiedAddresses.h"

class DhcpAckCreator : public DhcpResponseCreator {
    private:
        bool verifyClientAddress();
        virtual bool addClientRequestedOptions() override;
    public:
        DhcpAckCreator(DhcpDatagram* _clientDatagram, AssignedAddresses& _assignedAddresses);
        virtual ~DhcpAckCreator();

        virtual bool create() override;
};