#include "DhcpConfigurationsReader.h"
#include <exception>

DhcpConfigurationsReader::DhcpConfigurationsReader(){
    openConfigFile() ? readConfigFromFile() : setStandardConfigurations();
}

DhcpConfigurationsReader::~DhcpConfigurationsReader(){
    
}

DhcpConfigurations DhcpConfigurationsReader::getConfig() const{
    return this->config;
}

bool DhcpConfigurationsReader::openConfigFile(){
    configFile.open (filepath, std::ifstream::in);
    std::cout<<filepath<<std::endl;
    return configFile.is_open();
}

void DhcpConfigurationsReader::readConfigFromFile(){
    try{
        this->readConfig();
    } catch(std::exception& ex) {
        throw std::string{"Bad config file has been provided.\n Failed to load data"};
    }
}

void DhcpConfigurationsReader::readConfig(){
    std::string line;
    configFile>>line;
    config.serverName = line;
    configFile>>line;
    config.serverAddress = line;
    configFile>>line;
    config.startingAddress = line;
    configFile>>line;
    config.endingAddress = line;

}

void DhcpConfigurationsReader::setStandardConfigurations(){
    config.serverName = STANDARD_SERVER_NAME;
    config.serverAddress = STANDARD_SERVER_ADDRESS;
    config.startingAddress = STANDARD_START_ADDRESS;
    config.endingAddress = STANDARD_ADDRESS_END;
}