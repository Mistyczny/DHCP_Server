#include "StaticAddressesRecorder.h"

#define RECORD_NOT_FOUND 0

StaticAddressesRecorder::StaticAddressesRecorder() : numberOfRecords{}, root{} {
    if(staticAddressesDocument.LoadFile(staticAddressesFile) == tinyxml2::XML_SUCCESS) {
        root = staticAddressesDocument.FirstChild();
        if(root) {
            numberOfRecords = findLastRecordNumber();
        }
    } else {
        root = staticAddressesDocument.NewElement("StaticAddresses");
        staticAddressesDocument.InsertFirstChild(root);
    }
}

StaticAddressesRecorder::~StaticAddressesRecorder() {

}

size_t StaticAddressesRecorder::findLastRecordNumber() {
    size_t recordsCounter{1};
    std::string recordPrefix = "Address_";
    XMLElement* sectionHeader{};

    while(sectionHeader = root->FirstChildElement(("Address_"+std::to_string(recordsCounter)).c_str())) {
        recordsCounter++;
    }

    return recordsCounter-1;
}

bool StaticAddressesRecorder::save(AssignedAddress address) {
    if(isAssignedStatic(address)) return false;

    bool savedSuccessfully{false};
    std::string recordHeader = "Address_" + std::to_string(++numberOfRecords);
    XMLElement* sectionHeader = staticAddressesDocument.NewElement(recordHeader.c_str());
    
    XMLElement* addrPart = staticAddressesDocument.NewElement("IP");
    addrPart->SetText(address.ip.to_string().c_str());
    sectionHeader->InsertEndChild(addrPart);
    addrPart = staticAddressesDocument.NewElement("MAC");
    std::string str((char*)address.clientHardwareAddress.data());
    addrPart->SetText(str.c_str());
    sectionHeader->InsertEndChild(addrPart);

    root->InsertEndChild(sectionHeader);
    staticAddressesDocument.SaveFile(staticAddressesFile);
    return savedSuccessfully;
}

size_t StaticAddressesRecorder::instertedAt(AssignedAddress address) {
    if(!root) return RECORD_NOT_FOUND;
    size_t recordIndex{1};
    std::cout<<"1"<<std::endl;
    XMLElement* sectionHeader;
    while(sectionHeader = root->FirstChildElement(("Address_"+std::to_string(recordIndex)).c_str()), sectionHeader != nullptr) {
        XMLElement* ip = sectionHeader->FirstChildElement("IP");
        XMLElement* mac = sectionHeader->FirstChildElement("MAC");

        if(address.ip.to_string() == ip->GetText() && std::string((char*)address.clientHardwareAddress.data()) == std::string(mac->GetText())) {
            return recordIndex;
        }

        recordIndex++;
    }

    return RECORD_NOT_FOUND;
}

bool StaticAddressesRecorder::isAssignedStatic(AssignedAddress address) {
    if(!root) return false;

    return this->instertedAt(address);
}

bool StaticAddressesRecorder::remove(AssignedAddress address) {
    if(!root) return false;

    size_t recordIndex = instertedAt(address);

    if(recordIndex > 0) {
        XMLElement* recordToDelete = root->FirstChildElement(("Address_"+std::to_string(recordIndex)).c_str());
        XMLElement* lastRecord = root->FirstChildElement(("Address_"+std::to_string(findLastRecordNumber())).c_str());
        
        XMLElement* ipToDelete = recordToDelete->FirstChildElement("IP");
        std::cout<<ipToDelete->GetText()<<std::endl;
        XMLElement* macToDelete = recordToDelete->FirstChildElement("MAC");

        XMLElement* lastRecordIp = lastRecord->FirstChildElement("IP");
        XMLElement* lastRecordMac = lastRecord->FirstChildElement("MAC");

        ipToDelete->SetText(lastRecordIp->GetText());
        macToDelete->SetText(lastRecordMac->GetText());

        root->DeleteChild(lastRecord);
        numberOfRecords--;

        staticAddressesDocument.SaveFile(staticAddressesFile);
        return true;
    }

    return false;
}