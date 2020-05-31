#include "Properties.h"

Properties::Properties() {
    this->localMachineProperties.networkServerAddress = boost::asio::ip::address_v4::from_string("192.168.1.191");
    this->localMachineProperties.serverName = "DHCP_Kacpra";
    this->localMachineProperties.serverHardwareAddress = "08:00:27:6d:b0:9e";

    networkProperties.gatewayAddress = boost::asio::ip::address_v4::from_string("192.168.0.1");
    networkProperties.routerAddress = boost::asio::ip::address_v4::from_string("192.168.0.1");
    networkProperties.subnetMask[0] = std::byte(255);
    networkProperties.subnetMask[1] = std::byte(255);
    networkProperties.subnetMask[2] = std::byte(255);
    networkProperties.subnetMask[3] = std::byte(0);
}

Properties::~Properties() {

}

LocalNetworkingProperties Properties::getNetworkProperties() const {
    return this->networkProperties;
}

ServerProperties Properties::getServerProperties() const {
    return this->localMachineProperties;
}