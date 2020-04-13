#pragma once
#include "tinyxml2.h"

using namespace tinyxml2;

class ExistingAddressesLoader {
    private:
        bool documentExists;
        XMLDocument document;
        XMLNode * rootNode;
        XMLElement *addrElement;
    public:
        ExistingAddressesLoader();
        ~ExistingAddressesLoader();

        bool load();
};