#pragma once
#include "DhcpResponseCreator.h"
#include "DhcpDatagram.h"
#include "OccupiedAddresses.h"

class DhcpOfferCreator : public DhcpResponseCreator {
    private:
        bool addClientAddress();
        virtual bool addClientRequestedOptions() override;
    public:
        DhcpOfferCreator(DhcpDatagram* _clientDatagram, AssignedAddresses& _assignedAddresses);
        virtual ~DhcpOfferCreator();

        virtual bool create() override;
};