cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
set(This DHCP_Server)
project(DHCP_Server)

# Linking
include_directories("${PROJECT_ROOT}/Build/include")
include_directories("/usr/local/lib")
include_directories("/usr/local/include")
include_directories("./include")
include_directories("../3rdParty/tinyxml2/")
include_directories("../3rdParty/boost/boost")
# Project properties
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/outputApp)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/outputApp)

# Boost
set(Boost_USE_MULTITHREADED ON)
set(DBOOST_ROOT {PROJECT_SOURCE_DIR}/../3rdParty/boost)
set(DBoost_LIBRARY_DIRS {PROJECT_SOURCE_DIR}/../3rdParty/boost/lib)
include_directories("${PROJECT_SOURCE_DIR}/../3rdParty/boost")

# Source files
set(DHCP_SOURCES src/DhcpServer.cpp
                 src/AssignedAddresses.cpp
                 src/AutomaticAddressAllocator.cpp
                 src/DhcpConfigurationsReader.cpp
                 src/LeasingMonitor.cpp
                 src/ReservedAddresses.cpp
                 src/AddressesElector.cpp
                 src/MessageHandler.cpp)       

# Executable
add_executable( ${This} main.cpp ${DHCP_SOURCES})
