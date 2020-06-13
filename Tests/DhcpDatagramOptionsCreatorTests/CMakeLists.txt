cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
set(This DhcpDatagramOptionsCreatorTests)
project(${This})

set(SOURCES ../../Sources/src/DhcpDatagramOptionsCreator.cpp
            ../../Sources/src/DhcpUtils.cpp
            ../../Sources/src/Settings.cpp
            ../../Sources/src/SettingsRecorder.cpp)

set(UT_SOURCES DhcpDatagramOptionsCreatorUT.cpp)

add_executable(${This} ${COMMON_TEST_SOURCES} ${UT_SOURCES} ${SOURCES})

add_test(${This} ${This})