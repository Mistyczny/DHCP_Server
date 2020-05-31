#pragma once
#include "LocalNetworkingSettings.h"
#include "ServerSettings.h"
#include <atomic>
#include <iostream>

class Settings {
    private:
        static inline std::atomic<Settings*> instance;
        static inline std::mutex settingsLocker;

        LocalNetworkingSettings networkProperties;
        ServerSettings localMachineProperties;
    public:
        Settings();
        ~Settings();

        ServerSettings& getServerSettings();
        LocalNetworkingSettings& getNetworkSettings();
        
        bool save();
        bool load();
        void setDefault();

        static inline Settings* getInstance() {
            if(instance == nullptr) {
                std::lock_guard<std::mutex> lock(settingsLocker);
                instance = new Settings();
            }
            return instance;
        }
};