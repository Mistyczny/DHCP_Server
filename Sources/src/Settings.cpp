#include "Settings.h"
#include "SettingsRecorder.h"
#include <iostream>

Settings::Settings() {

}

Settings::~Settings() {
    delete instance;
}

LocalNetworkingSettings& Settings::getNetworkSettings() {
    return this->networkProperties;
}

ServerSettings& Settings::getServerSettings() {
    return this->localMachineProperties;
}

bool Settings::save() {
    SettingsRecorder recorder{*this};
    return recorder.save();
}

bool Settings::load() {
    bool loaded{true};
    SettingsRecorder recorder{*this};
    
    if(!recorder.load()) {
        loaded = false;
        std::cout<<"Settings loading failed"<<std::endl;
    } 

    return loaded;
}

void Settings::setDefault() {

}