#pragma once
#include <boost/asio.hpp>

#define SERVER_SETTINGS_NAME "ServerSettings"
#define NETWORK_SERVER_ADDRESS_PROPERTY_NAME "NetworkServerAddress"
#define SERVER_NAME_PROPERTY_NAME "ServerName"
#define SERVER_HARDWARE_ADDRESS_PROPERTY_NAME "ServerHardwareAddress"

struct ServerSettings {
    boost::asio::ip::address_v4 networkServerAddress;
    std::string serverName;
    std::string serverHardwareAddress;
};