#include "ExistingAddressesLoader.h"

ExistingAddressesLoader::ExistingAddressesLoader() : documentExists{false}{
    if(document.LoadFile("/opt/DHCP/ExistingAddresses.xml")==XML_SUCCESS){
        documentExists = true;
    }
}

ExistingAddressesLoader::~ExistingAddressesLoader(){

}

bool ExistingAddressesLoader::load(){
    rootNode = document.FirstChild();

    if(rootNode==nullptr) return false;

    addrElement = xmlDoc.NewElement("Date");
}