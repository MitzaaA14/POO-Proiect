#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <algorithm>

// Observer Pattern
class LogObserver {
public:
    virtual ~LogObserver() = default;
    virtual void onLogMessage(const std::string& message) = 0;
};

// Singleton Pattern + Subject (from Observer Pattern)
class Logger {
private:
    static std::unique_ptr<Logger> instance;
    std::vector<LogObserver*> observers;
    std::ofstream logFile;

    // Private constructor for singleton
    Logger();

    // Delete copy constructor and assignment operator
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

public:
    static Logger& getInstance();

    void addObserver(LogObserver* observer);
    void removeObserver(LogObserver* observer);
    void log(const std::string& message);

    // Operator overloading as member function
    Logger& operator+=(const std::string& message);

    // Destructor
    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }
};

#endif // LOGGER_H