#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE DhcpTests
#endif
#include <boost/asio.hpp>
#include <boost/test/unit_test.hpp>
#include "AssignedAddresses.h"
#include "AssignedAddress.h"
#include <iostream>

BOOST_AUTO_TEST_SUITE(AssignedAddressesUT)
    BOOST_AUTO_TEST_CASE(Adding_new_addresses) {
        AssignedAddresses addresses;
        AssignedAddress address;

        address.ip = boost::asio::ip::address_v4::from_string("127.0.0.1");
        address.clientHardwareAddress = std::array<unsigned char,16>{'A','B','C'};
        
        BOOST_TEST(addresses.push(address) == true);
        BOOST_CHECK_EQUAL(addresses.size(), static_cast<size_t>(1));
    }

    BOOST_AUTO_TEST_CASE(Adding_new_addresses_that_exists) {
        AssignedAddresses addresses;
        AssignedAddress address;
        
        address.ip = boost::asio::ip::address_v4::from_string("127.0.0.1");
        address.clientHardwareAddress = std::array<unsigned char,16>{'A','B','C'};
        
        BOOST_TEST(addresses.push(address) == true);
        BOOST_CHECK_EQUAL(addresses.size(), static_cast<size_t>(1));
        
        BOOST_TEST(addresses.push(address) == false);
        BOOST_CHECK_EQUAL(addresses.size(), static_cast<size_t>(1));
    }

    BOOST_AUTO_TEST_CASE(Adding_And_Removing_addresses) {
        AssignedAddresses addresses;
        AssignedAddress addressOne;
        addressOne.ip = boost::asio::ip::address_v4::from_string("127.0.0.1");
        addressOne.clientHardwareAddress = std::array<unsigned char,16>{'A','B','C'};
        
        BOOST_TEST(addresses.push(addressOne) == true);
        BOOST_CHECK_EQUAL(addresses.size(), static_cast<size_t>(1));

        AssignedAddress addressTwo;
        addressTwo.ip = boost::asio::ip::address_v4::from_string("127.0.0.2");
        addressTwo.clientHardwareAddress = std::array<unsigned char,16>{'A','B','D'};
        
        BOOST_TEST(addresses.push(addressTwo) == true);
        BOOST_CHECK_EQUAL(addresses.size(), static_cast<size_t>(2));

        BOOST_TEST(addresses.remove(boost::asio::ip::address_v4::from_string("127.0.0.2")) == true);
        BOOST_TEST(addresses.remove(boost::asio::ip::address_v4::from_string("127.0.0.2")) == false);
    }
BOOST_AUTO_TEST_SUITE_END()