#pragma once
#include "DhcpResponseCreator.h"
#include "DhcpDatagram.h"
#include "OccupiedAddresses.h"

class DhcpOfferCreator : public DhcpResponseCreator {
    private:
        void addClientAddress();
    public:
        DhcpOfferCreator(DhcpDatagram* _clientDatagram, AssignedAddresses& _assignedAddresses);
        virtual ~DhcpOfferCreator();

        virtual bool create() override;
        virtual void setMessageTypeOption() override;
};