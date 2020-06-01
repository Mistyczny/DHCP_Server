#pragma once
#include "DhcpDatagram.h"
#include <array>
#include <cstddef>

namespace TestUtils {
    std::array<std::byte,DHCP_OPTIONS_LENGTH> createOptions();
}