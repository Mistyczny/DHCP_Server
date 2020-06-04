cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
set(This DhcpUtilsTests)
project(${This})

set(SOURCES ../../Sources/src/DhcpDatagramOptionsCreator.cpp)

set(UT_SOURCES DhcpUtilsFindOptionPositionUT.cpp)

add_executable(${This} ${COMMON_TEST_SOURCES} ${UT_SOURCES} ${SOURCES})

add_test(DhcpUtilsTests ${This})