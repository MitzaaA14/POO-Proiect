#include "Logger.h"

// Initialize static member
std::unique_ptr<Logger> Logger::instance = nullptr;

// Constructor implementation
Logger::Logger() {
    logFile.open("catalog.log", std::ios::app);
}

// getInstance implementation
Logger& Logger::getInstance() {
    if (!instance) {
        instance = std::unique_ptr<Logger>(new Logger());
    }
    return *instance;
}

// addObserver implementation
void Logger::addObserver(LogObserver* observer) {
    observers.push_back(observer);
}

// removeObserver implementation
void Logger::removeObserver(LogObserver* observer) {
    observers.erase(
            std::remove_if(observers.begin(), observers.end(),
                           [observer](LogObserver* obs) { return obs == observer; }),
            observers.end()
    );
}

// log implementation
void Logger::log(const std::string& message) {
    logFile << message << std::endl;
    for (auto observer : observers) {
        observer->onLogMessage(message);
    }
}

// operator+= implementation
Logger& Logger::operator+=(const std::string& message) {
    log(message);
    return *this;
}