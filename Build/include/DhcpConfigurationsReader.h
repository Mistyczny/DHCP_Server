#pragma once
#include "DhcpConfigurations.h"
#include <iostream>
#include <string>
#include <fstream>


class DhcpConfigurationsReader{
    private:
        DhcpConfigurations config;
        std::ifstream configFile;
        std::string readingBuffer;

        bool openConfigFile();
        void readConfigFromFile();
        void readConfig();
        void setStandardConfigurations();
    public:
        DhcpConfigurationsReader();
        ~DhcpConfigurationsReader();

        DhcpConfigurations getConfig() const;
};