#pragma once
#include <stdint.h>
#include <netinet/in.h>
#include <array>
#include <cstddef>
#include <boost/asio.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#define MAX_DHCP_CHADDR_LENGTH 16
#define MAX_DHCP_SERVER_NAME_LENGTH 64
#define MAX_DHCP_FILE_LENGTH 128
#define MAX_DHCP_OPTIONS_LENGTH 78 //std::bytes
#define DHCP_OPTIONS_LENGTH 78

using namespace boost::asio::ip;

#define DHCP_REQUEST 1
#define DHCP_RESPONSE 2

namespace DhcpDatagramTypes{
	enum Options{
		SubnetMask = 1,
		LeasingTime = 51,
		MessageType = 53,
		DhcpServerIdentifier = 54
	};
}

struct DhcpDatagram {
		/* Operation to be performed type */
		std::byte operationCode;

		/* Hardware type on which talk is performed */
		std::byte hardwareType;

		/* Length of hardware address */
		std::byte hardwareTypeLength;

		/* Number of made hops */
		std::byte hops;

		/* Random transaction id number */
		uint32_t transactionID;

		/* Seconds elapsed */
		uint16_t secondsElapsed;

		/* flags */
		uint16_t flags;

		/* IP address of this machine, if it has one already */
		address_v4 currentIpAddress;

		/* IP address offered by DHCP server */
		address_v4 offeredIpAddress;

		/* DHCP server ip address */
		address_v4 serverIpAddress;

		/* DHCP server gateway address */
		address_v4 gatewayIpAddress;

		/* Hardware address of client machine */
		std::array<unsigned char,MAX_DHCP_CHADDR_LENGTH> hardwareAddress;

		/* Name of DHCP server */
		std::array<char,MAX_DHCP_SERVER_NAME_LENGTH> serverName;

		/* Boot file name */
		std::array<char,MAX_DHCP_FILE_LENGTH> bootFileName;

		/* DHCP options */
		std::array<std::byte,DHCP_OPTIONS_LENGTH> options;
};

struct DynamicDhcpDatagram {
		/* Operation to be performed type */
		std::byte operationCode;

		/* Hardware type on which talk is performed */
		std::byte hardwareType;

		/* Length of hardware address */
		std::byte hardwareTypeLength;

		/* Number of made hops */
		std::byte hops;

		/* Random transaction id number */
		uint32_t transactionID;

		/* Seconds elapsed */
		uint16_t secondsElapsed;

		/* flags */
		uint16_t flags;

		/* IP address of this machine, if it has one already */
		address_v4 currentIpAddress;

		/* IP address offered by DHCP server */
		address_v4 offeredIpAddress;

		/* DHCP server ip address */
		address_v4 serverIpAddress;

		/* DHCP server gateway address */
		address_v4 gatewayIpAddress;

		/* Hardware address of client machine */
		std::array<unsigned char,MAX_DHCP_CHADDR_LENGTH> hardwareAddress;

		/* Name of DHCP server */
		std::array<char,MAX_DHCP_SERVER_NAME_LENGTH> serverName;

		/* Boot file name */
		std::array<char,MAX_DHCP_FILE_LENGTH> bootFileName;

		/* DHCP options */
		std::vector<std::byte> options;
};