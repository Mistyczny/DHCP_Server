cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
set(This DHCP_Server_tests)
enable_testing()

set(BOOST_ROOT /usr/include/boost)
set(Boost_INCLUDE_DIR /usr/include/boost/include)
set(Boost_LIBRARY_DIR /usr/include/boost/lib)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall")
set (CMAKE_POSITION_INDEPENDENT_CODE ON)
add_definitions(-DBOOST_TEST_DYN_LINK)

set(COMMON_TEST_SOURCES ../TestMain.cpp)

find_package(Boost 1.72.0 COMPONENTS unit_test_framework REQUIRED)
find_library(tinyxml tinyxml2 "../3rdParty/tinyxml2")

link_libraries(${tinyxml})
link_libraries(${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

include_directories("../Sources/include")
include_directories("/usr/include/boost/include")
include_directories("../3rdParty/tinyxml2/")

add_subdirectory(DhcpUtilsTests)
add_subdirectory(AssignedAddressesTests)