#pragma once
#include <boost/asio.hpp>
#include <array>
#include <optional>
#include "DhcpDatagram.h"

namespace DhcpUtils {
    std::array<int,4> addressToIntParts(boost::asio::ip::address_v4 addr);
    boost::asio::ip::address_v4 stdByteArrayToAddress(std::array<std::byte,4>& addressParts);
    std::optional<size_t> findOptionPosition(std::array<std::byte,DHCP_OPTIONS_LENGTH>& options, int searchingOption);
};