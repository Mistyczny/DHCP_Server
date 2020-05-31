cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
set(This DhcpUtilsTests)
project(${This})

set(BOOST_ROOT /usr/include/boost)
set(Boost_INCLUDE_DIR /usr/include/boost/include)
set(Boost_LIBRARY_DIR /usr/include/boost/lib)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -std=${STD_CXX} ${REDISCPP_FLAGS}")
set (CMAKE_CXX_FLAGS_RELEASE "-O3 -g0 -std=${STD_CXX} -Wall -DNDEBUG ${REDISCPP_FLAGS}")
set (CMAKE_POSITION_INDEPENDENT_CODE ON)

