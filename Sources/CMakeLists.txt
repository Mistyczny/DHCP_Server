cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
set(This DHCP_Server)
project(${This})

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/outputApp)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/outputApp)

set (STD_CXX "c++17")
set (REDISCPP_FLAGS "-DREDISCPP_HEADER_ONLY=ON")

set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/3rdParty/boost_1_73_0)
set(Boost_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/3rdParty/boost_1_73_0/stage/lib)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall ")
set (CMAKE_POSITION_INDEPENDENT_CODE ON)

set(SOURCES src/DhcpServer.cpp
            src/Settings.cpp
            src/SettingsRecorder.cpp
            src/AssignedAddresses.cpp
            src/LeasingMonitor.cpp
            src/AutomaticAddressAllocator.cpp
            src/MessageHandler.cpp
            src/StaticAddressesRecorder.cpp
            src/DhcpResponseCreator.cpp
            src/DhcpOfferCreator.cpp
            src/DhcpAckCreator.cpp
            src/DhcpUtils.cpp
            src/DhcpDatagramOptionsCreator.cpp
            src/Logger.cpp)

find_package(Boost 1.72.0)

# Executable
add_executable( ${This} main.cpp ${SOURCES})

find_library(tinyxml tinyxml2 "../3rdParty/tinyxml2")
target_link_libraries(${This} PRIVATE ${tinyxml})

target_include_directories(${This} PRIVATE "./include")
target_include_directories(${This} PRIVATE "../3rdParty/boost_1_73_0/")
target_include_directories(${This} PRIVATE "../3rdParty/tinyxml2/")