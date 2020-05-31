#include "LeasingMonitor.h"
#include "AssignedAddress.h"
#include <chrono>

using namespace std::chrono_literals;

LeasingMonitor::LeasingMonitor(AssignedAddresses& addr): assignedAddresses{addr}{

}

LeasingMonitor::~LeasingMonitor(){

}

void LeasingMonitor::run() {
    while(1) {
        timePointNow = std::chrono::system_clock::now();
        this->removeEndedTimers();
        std::this_thread::sleep_for(2s);
    }
}

void LeasingMonitor::removeEndedTimers() {
    this->assignedAddresses.lock();
    system_clock::time_point addrLeasingEnd;
    
    auto iter = assignedAddresses.getAddrStorage().begin();
    while(iter != assignedAddresses.getAddrStorage().end()) {
        switch(iter->leasingType) {
            case AssignationType::STATIC:
                continue;
            case AssignationType::SHORT_LEASING:
                addrLeasingEnd = iter->assignationTime + seconds(AssignationDurationInSeconds::SHORT_LEASING_TIME);
                break;
            case AssignationType::LONG_LEASING:
                addrLeasingEnd = iter->assignationTime + seconds(AssignationDurationInSeconds::LONG_LEASING_TIME);
                break;
            default:
                continue;
        }

        if(timePointNow >= addrLeasingEnd){
            iter = assignedAddresses.remove_nolock(iter);
        } else iter++;
    }
    this->assignedAddresses.unlock();
}