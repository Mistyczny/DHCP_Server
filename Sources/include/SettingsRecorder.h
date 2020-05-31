#pragma once
#include "Settings.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class SettingsRecorder {
    private:
        inline static char settingsFile[] = "/opt/DHCP/DhcpSettings.xml";
        
        Settings& settings;
        XMLNode* root;
        XMLDocument settingsDocument;

        bool saveLocalNetworkingSettings();
        bool loadLocalNetworkingSettings();
        bool saveServerProperties();
        bool loadServerSettings();
        bool loadingSettings();

        bool saveProperty(XMLElement* node,std::string_view name,const char* data);
    public:
        SettingsRecorder(Settings& setting);
        ~SettingsRecorder();

        bool save();
        bool load();
};