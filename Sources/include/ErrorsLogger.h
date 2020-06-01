#pragma once
#include <atomic>
#include <fstream>
#include <mutex>

class ErrorsLogger {
    private:
        static inline std::atomic<ErrorsLogger*> instance;
        static inline std::mutex loggerLocker;
    public:
        ErrorsLogger();
        ~ErrorsLogger();

        static ErrorsLogger* getInstance() {
            if(instance == nullptr) {
                std::lock_guard<std::mutex> lock(loggerLocker);
                instance = new ErrorsLogger();
            }
            return instance;
        }
};