#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE DhcpTests
#endif
#include "DhcpUtils.h"
#include "DhcpDatagram.h"
#include "DhcpDefines.h"
#include "DhcpDatagramOptionsCreator.h"
#include <boost/test/unit_test.hpp>
#include <array>
#include <cstddef>

BOOST_AUTO_TEST_SUITE(DhcpDatagramOptionsCreatorTests)
    BOOST_AUTO_TEST_CASE(Requisted_Options_Supported) {
        std::set<std::byte> requestedOptions;
        requestedOptions.insert(std::byte(DHCP_Defines::OptionCode::DhcpServerIdentifier));
        requestedOptions.insert(std::byte(DHCP_Defines::OptionCode::LeasingAddressTime));
        requestedOptions.insert(std::byte(DHCP_Defines::OptionCode::SubnetMask));
        std::array<std::byte,DHCP_OPTIONS_LENGTH> options;

        DhcpDatagramOptionsCreator creator(options);
        BOOST_TEST(creator.writeOptions(requestedOptions, std::byte(2)));
    }

    BOOST_AUTO_TEST_CASE(Requisted_Options_Not_Supported) {
        std::set<std::byte> requestedOptions;
        requestedOptions.insert(std::byte(DHCP_Defines::OptionCode::DhcpServerIdentifier));
        requestedOptions.insert(std::byte(DHCP_Defines::OptionCode::LeasingAddressTime));
        requestedOptions.insert(std::byte(DHCP_Defines::OptionCode::SubnetMask));
        requestedOptions.insert(std::byte(77));
        std::array<std::byte,DHCP_OPTIONS_LENGTH> options;

        DhcpDatagramOptionsCreator creator(options);
        BOOST_CHECK(!creator.writeOptions(requestedOptions, std::byte(2)));
    }

    BOOST_AUTO_TEST_CASE(Example_Offer_Creation) {
        std::set<std::byte> requestedOptions;
        requestedOptions.insert(std::byte(DHCP_Defines::OptionCode::DhcpServerIdentifier));
        requestedOptions.insert(std::byte(DHCP_Defines::OptionCode::LeasingAddressTime));
        requestedOptions.insert(std::byte(DHCP_Defines::OptionCode::SubnetMask));
        requestedOptions.insert(std::byte(DHCP_Defines::OptionCode::RouterAddress));
        requestedOptions.insert(std::byte(DHCP_Defines::OptionCode::DnsServerAddress));
        std::array<std::byte,DHCP_OPTIONS_LENGTH> options;

        DhcpDatagramOptionsCreator creator(options);
        BOOST_TEST(creator.writeOptions(requestedOptions, std::byte(DHCP_Defines::Offer)));
    }

    BOOST_AUTO_TEST_CASE(Example_Ack_Creation) {
        std::set<std::byte> requestedOptions;
        requestedOptions.insert(std::byte(DHCP_Defines::OptionCode::DhcpServerIdentifier));
        requestedOptions.insert(std::byte(DHCP_Defines::OptionCode::LeasingAddressTime));
        requestedOptions.insert(std::byte(DHCP_Defines::OptionCode::SubnetMask));
        requestedOptions.insert(std::byte(DHCP_Defines::OptionCode::RouterAddress));
        requestedOptions.insert(std::byte(DHCP_Defines::OptionCode::DnsServerAddress));
        std::array<std::byte,DHCP_OPTIONS_LENGTH> options;

        DhcpDatagramOptionsCreator creator(options);
        BOOST_TEST(creator.writeOptions(requestedOptions, std::byte(DHCP_Defines::Ack)));
    }
BOOST_AUTO_TEST_SUITE_END()