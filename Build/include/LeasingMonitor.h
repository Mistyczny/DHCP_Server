#pragma once
#include "OccupiedAddresses.h"

class LeasingMonitor{
    private:
        OccupiedAddresses& addresses;
        system_clock::time_point timePointNow;

        void removeEndedTimers();
    public:
        LeasingMonitor(OccupiedAddresses&);
        ~LeasingMonitor();

        void run();
};