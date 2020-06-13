#include "Logger.h"
#include <iostream>

namespace Logging {

Logger::Logger() {
    this->fileName = "/opt/DHCP/logs.txt";
    this->file.open(fileName.c_str(),std::ios::ate);
    logLevel = LogLevel::TRACE;
}

Logger::~Logger() {
    if(file.is_open()) {
        file.close();
    }
}

void Logger::log(LogLevel lvl, const std::string& message) {
    std::scoped_lock locked{loggerLocker};
    if(this->logLevel < lvl) {
        if(file<<message) {
            file.flush();
        } else {
            this->reopen();
        }
    }
}

void Logger::reopen() {
    try { file.close(); } catch(...) {}
    try {
        this->file.open(fileName.c_str(),std::ios::ate);
    } catch(std::exception& ex) {
        try { file.close(); } catch(...) {}
        throw ex;
    }
}

};

