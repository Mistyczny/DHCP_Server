#pragma once
#include "OccupiedAddresses.h"
#include "AssignedAddresses.h"

class LeasingMonitor{
    private:
        AssignedAddresses& assignedAddresses;
        system_clock::time_point timePointNow;

        void removeEndedTimers();
    public:
        LeasingMonitor(AssignedAddresses&);
        ~LeasingMonitor();

        void run();
};