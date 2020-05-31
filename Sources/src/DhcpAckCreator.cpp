#include "DhcpAckCreator.h"
#include "DhcpUtils.h"

DhcpAckCreator::DhcpAckCreator(DhcpDatagram* _clientDatagram, AssignedAddresses& _assignedAddresses) : DhcpResponseCreator{_clientDatagram, _assignedAddresses} {

}

DhcpAckCreator::~DhcpAckCreator() {

}

bool DhcpAckCreator::create() {
    if(verifyClientAddress()) {
        this->addDhcpMagicOption();
        this->setMessageTypeOption();
        this->addServerIdentifierOption();
        this->addLeasingDurationOption();
        this->addSubnetMaskOption();
        this->addRouterAddressOption();
        this->addDomainNameServerOption();
        this->addEndOptionBit();
        return true;
    }

    return false;
}

void DhcpAckCreator::setMessageTypeOption() {
    this->responseDatagram.options[currentOptionsSpot++] = std::byte(DhcpDatagramTypes::Options::MessageType);
    this->responseDatagram.options[currentOptionsSpot++] = std::byte(1); /* Sizeof message */
    this->responseDatagram.options[currentOptionsSpot++] = std::byte(5); 
}

bool DhcpAckCreator::verifyClientAddress() {
    for(int i=0;i<clientDatagram->options.size(); i++) {
        if(clientDatagram->options[i] == std::byte(80)) {
            std::array<std::byte,4> address{};
            address[0] = clientDatagram->options[i+2];
            address[1] = clientDatagram->options[i+3];
            address[2] = clientDatagram->options[i+4];
            address[3] = clientDatagram->options[i+5];

            boost::asio::ip::address_v4 addr;
            AssignedAddress assigned;
            assigned.ip = DhcpUtils::stdByteArrayToAddress(address);
            assigned.clientHardwareAddress = clientDatagram->hardwareAddress;
            assigned.assignationTime = std::chrono::system_clock::now();
            assigned.leasingType = AssignationType::LONG_LEASING;
            if(!assignedAddresses.contain(addr)) {
                assignedAddresses.push(assigned);
            }
            return true;
        }
    }

    return false;
}