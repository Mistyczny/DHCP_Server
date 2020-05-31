#pragma once
#include "tinyxml2.h"
#include "AssignedAddress.h"
#include <vector>

using namespace tinyxml2;

class StaticAddressesRecorder {
    private:
        inline static char staticAddressesFile[] = "/opt/DHCP/DhcpStaticAddresses.xml";
        XMLNode* root;
        XMLDocument staticAddressesDocument;
        size_t numberOfRecords;
        
        size_t findLastRecordNumber();

        size_t instertedAt(AssignedAddress address);
    public:
        StaticAddressesRecorder();
        ~StaticAddressesRecorder();

        bool save(AssignedAddress address);
        bool remove(AssignedAddress address);
        bool isAssignedStatic(AssignedAddress address);
        std::vector<AssignedAddress> readAll();
};