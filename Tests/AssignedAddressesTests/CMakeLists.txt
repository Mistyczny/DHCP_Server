cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
set(This AssignedAddressesTests)
project(${This})

set(SOURCES ../../Sources/src/AssignedAddresses.cpp)

set(UT_SOURCES AssignedAddressesUT.cpp)
set(MUTEX_SOURCES AssignedAddressesMutexTests.cpp)

add_executable(AssignedAddressesTests_UT ${COMMON_TEST_SOURCES} ${UT_SOURCES} ${SOURCES})
add_executable(AssignedAddressesTests_MUTEX ${COMMON_TEST_SOURCES} ${MUTEX_SOURCES} ${SOURCES})

add_test(AssignedAddressUT AssignedAddressesTests_UT)
add_test(AssignedAddressMutex AssignedAddressesTests_MUTEX)