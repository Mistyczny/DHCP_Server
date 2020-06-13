cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
set(This DhcpResponseCreatorsUT)
project(${This})

set(COMMON_SOURCES  ../../Sources/src/DhcpResponseCreator.cpp
                    ../../Sources/src/AssignedAddresses.cpp
                    ../../Sources/src/AddressesElector.cpp
                    ../../Sources/src/DhcpDatagramOptionsCreator.cpp
                    ../../Sources/src/DhcpUtils.cpp
                    ../../Sources/src/Settings.cpp
                    ../../Sources/src/SettingsRecorder.cpp
                    ../../Sources/src/Logger.cpp)

set(DHCP_OFFER_SOURCES ../../Sources/src/DhcpOfferCreator.cpp)

add_executable(DhcpOfferCreator DhcpOfferCreatorUT.cpp ${COMMON_TEST_SOURCES} ${COMMON_SOURCES} ${DHCP_OFFER_SOURCES})

add_test(DhcpOfferCreator DhcpOfferCreator)