#pragma once
#include <boost/asio.hpp>
#include <array>

#define LOCAL_NETWORKING_SETTINGS_NAME "LocalNetworkingSettings"
#define SUBNET_MASK_PROPERTY_NAME "SubnetMask"
#define GATEAWAY_ADDRESS_PROPERTY_NAME "GatewayAddress"
#define ROUTER_ADDRESS_PROPERTY_NAME "RouterAddress"
#define ADDRESS_POOL_PROPERTY_NAME "AddressPool"
#define ADDRESS_POOL_START_PROPERTY_NAME "StartAddress"
#define ADDRESS_POOL_END_PROPERTY_NAME "EndAddress"

struct LocalNetworkingSettings{
    boost::asio::ip::address_v4 subnetMask;
    boost::asio::ip::address_v4 gatewayAddress;
    boost::asio::ip::address_v4 routerAddress;
    boost::asio::ip::address_v4 dnsAddress;
    boost::asio::ip::address_v4_range addressesPool;
};