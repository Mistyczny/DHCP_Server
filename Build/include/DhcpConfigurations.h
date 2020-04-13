#pragma once
#include <string>

#ifdef _WIN32
#define filepath "C:\\DHCP\\config.txt"
#elif __linux__
#define filepath "/opt/DHCP/config"
#endif

#define STANDARD_SERVER_NAME "serverName"

#define STANDARD_SERVER_ADDRESS "192.168.0.1"

#define STANDARD_START_ADDRESS "192.168.0.2"

#define STANDARD_ADDRESS_END "192.168.1.254"

struct DhcpConfigurations{
    std::string serverName;
    std::string serverAddress;
    std::string startingAddress;
    std::string endingAddress;
};