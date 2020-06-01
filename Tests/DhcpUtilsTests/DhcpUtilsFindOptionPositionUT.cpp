#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE DhcpTests
#endif
#include "DhcpUtils.h"
#include "DhcpDatagram.h"
#include <boost/test/unit_test.hpp>
#include <array>
#include <cstddef>

BOOST_AUTO_TEST_SUITE(FindOptionPosition)
    BOOST_AUTO_TEST_CASE(Searching_Option_Exists) {
        /* Creating example options */
        std::array<std::byte,DHCP_OPTIONS_LENGTH> options;
        /* Dhcp Magic Block */
        options[0] = std::byte(99);
        options[1] = std::byte(123);
        options[2] = std::byte(124);
        options[3] = std::byte(99);
        /* End of Dhcp Magic Block */
        options[4] = std::byte(1);
        options[5] = std::byte(2);
        options[6] = std::byte(4);
        options[7] = std::byte(7);
        options[8] = std::byte(6);
        options[9] = std::byte(2);
        options[10] = std::byte(22);
        options[11] = std::byte(32);
        options[12] = std::byte(11);
        options[13] = std::byte(2);
        options[14] = std::byte(33);
        options[15] = std::byte(34);
        options[16] = std::byte(32);
        auto returnedValue = DhcpUtils::findOptionPosition(options, 11);
        BOOST_CHECK(returnedValue);
        BOOST_CHECK_EQUAL(12, static_cast<int>(*returnedValue));
    }

    BOOST_AUTO_TEST_CASE(Searching_Option_NotExists) {
        /* Creating example options */
        std::array<std::byte,DHCP_OPTIONS_LENGTH> options;
        /* Dhcp Magic Block */
        options[0] = std::byte(99);
        options[1] = std::byte(123);
        options[2] = std::byte(124);
        options[3] = std::byte(99);
        /* End of Dhcp Magic Block */
        options[4] = std::byte(1);
        options[5] = std::byte(2);
        options[6] = std::byte(4);
        options[7] = std::byte(7);
        options[8] = std::byte(6);
        options[9] = std::byte(2);
        options[10] = std::byte(22);
        options[11] = std::byte(32);
        options[12] = std::byte(11);
        options[13] = std::byte(2);
        options[14] = std::byte(33);
        options[15] = std::byte(34);
        options[16] = std::byte(32);
        auto returnedValue = DhcpUtils::findOptionPosition(options, 77);
        BOOST_CHECK(!returnedValue);
    }

    BOOST_AUTO_TEST_CASE(Searching_Option_NotExists_And_Is_Parameter) {
        /* Creating example options */
        std::array<std::byte,DHCP_OPTIONS_LENGTH> options;
        /* Dhcp Magic Block */
        options[0] = std::byte(99);
        options[1] = std::byte(123);
        options[2] = std::byte(124);
        options[3] = std::byte(99);
        /* End of Dhcp Magic Block */
        options[4] = std::byte(1);
        options[5] = std::byte(2);
        options[6] = std::byte(4);
        options[7] = std::byte(7);
        options[8] = std::byte(6);
        options[9] = std::byte(2);
        options[10] = std::byte(22);
        options[11] = std::byte(32);
        options[12] = std::byte(11);
        options[13] = std::byte(2);
        options[14] = std::byte(33);
        options[15] = std::byte(34);
        options[16] = std::byte(32);
        auto returnedValue = DhcpUtils::findOptionPosition(options, 22);
        BOOST_CHECK(!returnedValue);
    }

BOOST_AUTO_TEST_SUITE_END()