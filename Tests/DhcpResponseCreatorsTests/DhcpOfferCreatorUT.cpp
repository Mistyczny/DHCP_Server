#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE DhcpTests
#endif
#include <boost/test/unit_test.hpp>
#include "DhcpOfferCreator.h"
#include "AssignedAddresses.h"
#include "DhcpDatagram.h"
#include "DhcpDefines.h"
#include "HardwareType.h"
#include <iostream>
#define TEST_TRANSACTION_ID 12345
#define TEST_FLAGS 321

BOOST_AUTO_TEST_SUITE(DhcpOfferCreatorUT)
    BOOST_AUTO_TEST_CASE(Constructor) {
        AssignedAddresses addresses;
        DhcpDatagram clientDatagram;
        DhcpOfferCreator offerCreator{&clientDatagram, addresses};
    }

    BOOST_AUTO_TEST_CASE(Correct_Operation_Code) {
        AssignedAddresses addresses;
        DhcpDatagram clientDatagram;
        clientDatagram.operationCode = std::byte(DHCP_Defines::opcode::Client_message);
        DhcpOfferCreator offerCreator{&clientDatagram, addresses};
        BOOST_TEST(offerCreator.create());
        DhcpDatagram& createdResponse = offerCreator.getResponse();
        BOOST_TEST(std::to_integer<int>(createdResponse.operationCode) == std::to_integer<int>(std::byte(DHCP_Defines::opcode::Server_message)));
    }

    BOOST_AUTO_TEST_CASE(Rewrite_Client_Data) {
        AssignedAddresses addresses;
        DhcpDatagram clientDatagram;
        clientDatagram.hardwareType = std::byte(HardwareTypes::Ethernet);
        clientDatagram.hardwareTypeLength = std::byte(6);
        clientDatagram.transactionID = TEST_TRANSACTION_ID;
        clientDatagram.flags = TEST_FLAGS;
        DhcpOfferCreator offerCreator{&clientDatagram, addresses};
        BOOST_TEST(offerCreator.create());
        DhcpDatagram& createdResponse = offerCreator.getResponse();
        BOOST_TEST(std::to_integer<int>(createdResponse.hardwareType) == std::to_integer<int>(std::byte(HardwareTypes::Ethernet)));
        BOOST_TEST(std::to_integer<int>(createdResponse.hardwareTypeLength) == std::to_integer<int>(std::byte(6)));
        BOOST_TEST(clientDatagram.transactionID == createdResponse.transactionID);
        BOOST_TEST(clientDatagram.flags, createdResponse.flags);
    }

    BOOST_AUTO_TEST_CASE(Address_Proposing_No_Current_Address_Assigned_Empty) {
        Settings* settings = Settings::getInstance();
        settings->load();
        AssignedAddresses addresses;
        DhcpDatagram clientDatagram;
        DhcpOfferCreator offerCreator{&clientDatagram, addresses};
        BOOST_TEST(offerCreator.create());
        DhcpDatagram& createdResponse = offerCreator.getResponse();
        BOOST_TEST(createdResponse.offeredIpAddress != boost::asio::ip::address_v4::from_string("0.0.0.0"));
    }

    BOOST_AUTO_TEST_CASE(Address_Proposing_No_Current_Address) {
        Settings* settings = Settings::getInstance();
        settings->load();
        AssignedAddresses addresses;
        AssignedAddress addr;
        addr.ip = boost::asio::ip::address_v4::from_string("192.128.0.2");
        addresses.push(addr);
        DhcpDatagram clientDatagram;
        DhcpOfferCreator offerCreator{&clientDatagram, addresses};
        BOOST_TEST(offerCreator.create());
        DhcpDatagram& createdResponse = offerCreator.getResponse();
        BOOST_TEST(createdResponse.offeredIpAddress != boost::asio::ip::address_v4::from_string("192.128.0.2"));
    }
BOOST_AUTO_TEST_SUITE_END()