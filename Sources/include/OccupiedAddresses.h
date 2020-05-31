#pragma once
#include "ReservedAdresses.h"
#include "AssignedAddresses.h"

struct OccupiedAddresses{
    AssignedAddresses assignedAddrs;
    ReservedAddresses reservedAddrs;
};