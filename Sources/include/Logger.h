#pragma once
#include <atomic>
#include <fstream>
#include <mutex>
#include <memory>
#include <fstream>

namespace Logging {
    
enum class LogLevel: uint8_t {TRACE = 0, DEBUG = 1, INFO = 2, WARNING = 3, ERROR = 4};

class Logger {
    private:
        LogLevel logLevel;
        static inline std::unique_ptr<Logger> instance;
        static inline std::mutex loggerLocker;
        std::string fileName;
        std::ofstream file;
    public:
        Logger();
        Logger(Logger&) = delete;
        Logger(Logger&&) = delete;
        ~Logger();

        static Logger& getInstance() {
            if(!instance) {
                std::lock_guard<std::mutex> lock(loggerLocker);
                instance = std::make_unique<Logger>();
            }
            return *instance;
        }

        void log(LogLevel lvl, const std::string& message);
        void reopen();
};

inline void TRACE(const std::string& message) {
    Logger::getInstance().log(LogLevel::TRACE, message);
}

inline void DEBUG(const std::string& message) {
    Logger::getInstance().log(LogLevel::DEBUG, message);
}

inline void INFO(const std::string& message) {
    Logger::getInstance().log(LogLevel::WARNING, message);
}

inline void WARNING(const std::string& message) {
    Logger::getInstance().log(LogLevel::WARNING, message);
}

inline void ERROR(const std::string& message) {
    Logger::getInstance().log(LogLevel::ERROR, message);
}

};