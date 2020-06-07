cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
set(This DHCP_SERVER_PROJECT)
project(${This})
enable_testing()

# Project properties
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

SET(Boost_USE_MULTITHREAD ON)
SET(Boost_NO_SYSTEM_PATHS TRUE)

add_subdirectory(Sources)
add_subdirectory(Tests)