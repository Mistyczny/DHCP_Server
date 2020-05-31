#include "SettingsRecorder.h"
#include <iostream>
#include <string>

#ifndef XMLCheckResult
	#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

SettingsRecorder::SettingsRecorder(Settings& setting) : settings{setting}, root{}{
}

SettingsRecorder::~SettingsRecorder() {

}

bool SettingsRecorder::saveProperty(XMLElement* headerNode,std::string_view name,const char* data) {
    bool propertySaved{true};

    XMLElement* element = settingsDocument.NewElement(name.data());
    if(!element) {
        propertySaved = false;
        std::cout<<"Failed to create element: "<<name<<std::endl;
    } else {
        element->SetText(data);
        headerNode->InsertEndChild(element);
    }

    return propertySaved; 
}

bool SettingsRecorder::save() {
    bool savedSuccessfully{false};
    root = settingsDocument.NewElement("Settings");
    settingsDocument.InsertFirstChild(root);

    if(!saveLocalNetworkingSettings()) {
        savedSuccessfully = false;
        std::cout<<"FAILED TO SAVE LOCAL NETWORKING SETTINGS"<<std::endl;
    } else if (!saveServerProperties()){
        savedSuccessfully = false;
        std::cout<<"FAILED TO SAVE LOCAL NETWORKING SETTINGS"<<std::endl;
    } else {
        savedSuccessfully = true;
    }

    settingsDocument.SaveFile(settingsFile);

    return savedSuccessfully;
}

bool SettingsRecorder::saveLocalNetworkingSettings() {
    bool returnStatus{true};
    XMLElement* sectionHeader = settingsDocument.NewElement(LOCAL_NETWORKING_SETTINGS_NAME);
    if(!sectionHeader) {
        std::cout<<"Failed to create element: "<<LOCAL_NETWORKING_SETTINGS_NAME<<std::endl;
        returnStatus = false;
    } else {
        XMLElement* sectionElement{nullptr};

        sectionElement = settingsDocument.NewElement(SUBNET_MASK_PROPERTY_NAME);
        if(!sectionElement) {
            std::cout<<"Failed to create element: "<<SUBNET_MASK_PROPERTY_NAME<<std::endl;
            returnStatus = false;
        } else {
            sectionElement->SetText(settings.getNetworkSettings().subnetMask.to_string().c_str());
            sectionHeader->InsertEndChild(sectionElement);
        }

        sectionElement = settingsDocument.NewElement(GATEAWAY_ADDRESS_PROPERTY_NAME);
        if(!sectionElement) {
            std::cout<<"Failed to create element: "<<GATEAWAY_ADDRESS_PROPERTY_NAME<<std::endl;
            returnStatus = false;
        } else {
            sectionElement->SetText(settings.getNetworkSettings().gatewayAddress.to_string().c_str());
            sectionHeader->InsertEndChild(sectionElement);
        }

        sectionElement = settingsDocument.NewElement(ROUTER_ADDRESS_PROPERTY_NAME);
        if(!sectionElement) {
            std::cout<<"Failed to create element: "<<ROUTER_ADDRESS_PROPERTY_NAME<<std::endl;
            returnStatus = false;
        } else {
            sectionElement->SetText(settings.getNetworkSettings().routerAddress.to_string().c_str());
            sectionHeader->InsertEndChild(sectionElement);
        }

        sectionElement = settingsDocument.NewElement(ADDRESS_POOL_PROPERTY_NAME);
        if(!sectionElement) {
            std::cout<<"Failed to create element: "<<ADDRESS_POOL_PROPERTY_NAME<<std::endl;
            returnStatus = false;
        } else {
            XMLElement* addrsPoolElement{nullptr};
            
            addrsPoolElement = settingsDocument.NewElement(ADDRESS_POOL_START_PROPERTY_NAME);
            if(!addrsPoolElement) {
                std::cout<<"Failed to create element: "<<ADDRESS_POOL_PROPERTY_NAME<<std::endl;
                returnStatus = false;
            } else {
                addrsPoolElement->SetText(settings.getNetworkSettings().addressesPool.begin()->to_string().c_str());
                sectionElement->InsertEndChild(addrsPoolElement);
            }

            addrsPoolElement = settingsDocument.NewElement(ADDRESS_POOL_END_PROPERTY_NAME);
            if(!addrsPoolElement) {
                std::cout<<"Failed to create element: "<<ADDRESS_POOL_PROPERTY_NAME<<std::endl;
                returnStatus = false;
            } else {
                addrsPoolElement->SetText(settings.getNetworkSettings().addressesPool.end()->to_string().c_str());
                sectionElement->InsertEndChild(addrsPoolElement);
            }
        }

        sectionHeader->InsertEndChild(sectionElement);
    }
    
    root->InsertEndChild(sectionHeader);

    return returnStatus;
}

bool SettingsRecorder::saveServerProperties() {
    bool returnStatus{true};
    
    XMLElement* sectionHeader = settingsDocument.NewElement(SERVER_SETTINGS_NAME);
    if(!sectionHeader) {
        std::cout<<"Failed to create element: "<<SERVER_SETTINGS_NAME<<std::endl;
        returnStatus = false;
    } else {
        XMLElement* sectionElement{nullptr};

        sectionElement = settingsDocument.NewElement(SERVER_NAME_PROPERTY_NAME);
        if(!sectionElement) {
            std::cout<<"Failed to create element: "<<SERVER_NAME_PROPERTY_NAME<<std::endl;
            returnStatus = false;
        } else {
            sectionElement->SetText(settings.getServerSettings().serverName.c_str());
            sectionHeader->InsertEndChild(sectionElement);
        }
        
        sectionElement = settingsDocument.NewElement(NETWORK_SERVER_ADDRESS_PROPERTY_NAME);
        if(!sectionElement) {
            std::cout<<"Failed to create element: "<<NETWORK_SERVER_ADDRESS_PROPERTY_NAME<<std::endl;
            returnStatus = false;
        } else {
            sectionElement->SetText(settings.getServerSettings().networkServerAddress.to_string().c_str());
            sectionHeader->InsertEndChild(sectionElement);
        }
        
        sectionElement = settingsDocument.NewElement(SERVER_HARDWARE_ADDRESS_PROPERTY_NAME);
        if(!sectionElement) {
            std::cout<<"Failed to create element: "<<SERVER_HARDWARE_ADDRESS_PROPERTY_NAME<<std::endl;
            returnStatus = false;
        } else {
            sectionElement->SetText(settings.getServerSettings().serverHardwareAddress.c_str());
            sectionHeader->InsertEndChild(sectionElement);
        }
        
        sectionHeader->InsertEndChild(sectionElement);
    }

    root->InsertEndChild(sectionHeader);
    
    return returnStatus;
}

bool SettingsRecorder::load() {
    bool loadedSuccessfully{false};

    if(settingsDocument.LoadFile(settingsFile)!= tinyxml2::XML_SUCCESS) {
        std::cout<<"Failed to open file with configurations"<<std::endl;
    } else {
        root = settingsDocument.FirstChild();

        if(root == nullptr) {
            std::cout<<"Configuration file is incorrect, could not read root markup"<<std::endl;
        } else {
            loadedSuccessfully = this->loadingSettings();
        }
    }

    return loadedSuccessfully;
}

bool SettingsRecorder::loadingSettings() {
    bool status{false};

    if(!this->loadLocalNetworkingSettings()) {
        std::cout<<"Failed to load local networking settings"<<std::endl;
    } else if (!this->loadServerSettings()) {
        std::cout<<"Failed to load server settings"<<std::endl;
    } else {
        status = true;
    }

    return status;
}

bool SettingsRecorder::loadLocalNetworkingSettings() {
    int returnStatus{true};
    auto& [subnetMask,gatewayAddress,routerAddress,addressesPool] = settings.getNetworkSettings();

    XMLElement* sectionHeader = root->FirstChildElement(LOCAL_NETWORKING_SETTINGS_NAME);
    if(!sectionHeader) {
        std::cout<<"Failed to load: "<<LOCAL_NETWORKING_SETTINGS_NAME<<std::endl;
        returnStatus = false;
    } else {
        XMLElement* sectionElement{nullptr};

        sectionElement = sectionHeader->FirstChildElement(SUBNET_MASK_PROPERTY_NAME);
        if(!sectionElement) {
            returnStatus = false;
            std::cout<<"Failed to load: "<<SUBNET_MASK_PROPERTY_NAME<<std::endl;
        } else subnetMask = boost::asio::ip::address_v4::from_string(sectionElement->GetText());

        sectionElement = sectionHeader->FirstChildElement(GATEAWAY_ADDRESS_PROPERTY_NAME);
        if(!sectionElement) {
            returnStatus = false;
            std::cout<<"Failed to load: "<<GATEAWAY_ADDRESS_PROPERTY_NAME<<std::endl;
        } else gatewayAddress = boost::asio::ip::address_v4::from_string(sectionElement->GetText());

        sectionElement = sectionHeader->FirstChildElement(ROUTER_ADDRESS_PROPERTY_NAME);
        if(!sectionElement) {
            returnStatus = false;
            std::cout<<"Failed to load: "<<ROUTER_ADDRESS_PROPERTY_NAME<<std::endl;
        } else routerAddress = boost::asio::ip::address_v4::from_string(sectionElement->GetText());

        sectionElement = sectionHeader->FirstChildElement(ADDRESS_POOL_PROPERTY_NAME);
        if(!sectionElement) {
            returnStatus = false;
            std::cout<<"Failed to load: "<<ADDRESS_POOL_PROPERTY_NAME<<std::endl;
        } else {
            XMLElement* addressPoolElement{nullptr}; 
            boost::asio::ip::address_v4 start, end;

            addressPoolElement = sectionElement->FirstChildElement(ADDRESS_POOL_START_PROPERTY_NAME);
            if(!addressPoolElement) {
                returnStatus = false;
                std::cout<<"Failed to load: "<<ADDRESS_POOL_START_PROPERTY_NAME<<std::endl;
            } else start = boost::asio::ip::address_v4::from_string(addressPoolElement->GetText());
            
            addressPoolElement = sectionElement->FirstChildElement(ADDRESS_POOL_END_PROPERTY_NAME);
            if(!addressPoolElement) {
                returnStatus = false;
                std::cout<<"Failed to load: "<<ADDRESS_POOL_END_PROPERTY_NAME<<std::endl;
            } else end = boost::asio::ip::address_v4::from_string(addressPoolElement->GetText());

            addressesPool = boost::asio::ip::address_v4_range{start,end};
        }            
    }

    return returnStatus;
}

bool SettingsRecorder::loadServerSettings() {
    bool returnStatus{true};
    auto& [networkServerAddress,serverName,serverHardwareAddress] = settings.getServerSettings();

    XMLElement* sectionHeader = root->FirstChildElement(SERVER_SETTINGS_NAME);
    if(!sectionHeader) {
        std::cout<<"Failed to load: "<<SERVER_SETTINGS_NAME<<std::endl;
        returnStatus = false;
    } else {
        XMLElement* sectionElement{nullptr};

        sectionElement = sectionHeader->FirstChildElement(NETWORK_SERVER_ADDRESS_PROPERTY_NAME);
        if(!sectionElement) {
            returnStatus = false;
            std::cout<<"Failed to load: "<<NETWORK_SERVER_ADDRESS_PROPERTY_NAME<<std::endl;
        } else networkServerAddress = boost::asio::ip::address_v4::from_string(sectionElement->GetText());

        sectionElement = sectionHeader->FirstChildElement(SERVER_NAME_PROPERTY_NAME);
        if(!sectionElement) {
            returnStatus = false;
            std::cout<<"Failed to load: "<<SERVER_NAME_PROPERTY_NAME<<std::endl;
        } else serverName = sectionElement->GetText();

        sectionElement = sectionHeader->FirstChildElement(SERVER_HARDWARE_ADDRESS_PROPERTY_NAME);
        if(!sectionElement) {
            returnStatus = false;
            std::cout<<"Failed to load: "<<SERVER_HARDWARE_ADDRESS_PROPERTY_NAME<<std::endl;
        } else serverHardwareAddress = sectionElement->GetText();
    }

    return returnStatus;
}