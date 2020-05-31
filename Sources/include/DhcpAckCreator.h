#pragma once
#include "DhcpResponseCreator.h"
#include "DhcpDatagram.h"
#include "OccupiedAddresses.h"

class DhcpAckCreator : public DhcpResponseCreator {
    private:
        bool verifyClientAddress();
    public:
        DhcpAckCreator(DhcpDatagram* _clientDatagram, AssignedAddresses& _assignedAddresses);
        virtual ~DhcpAckCreator();

        virtual bool create() override;
        virtual void setMessageTypeOption() override;
};