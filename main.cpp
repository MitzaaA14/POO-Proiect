#include "Catalog.h"
#include "Logger.h"
#include <iostream>
#include <cstring>

// Custom observer for console logging
class ConsoleLogObserver : public LogObserver {
public:
    void onLogMessage(const std::string& message) override {
        std::cout << "LOG: " << message << std::endl;
    }
};

int main(int argc, char* argv[]) {
    try {
        // Setup logging
        ConsoleLogObserver consoleObserver;
        Logger::getInstance().addObserver(&consoleObserver);

        Catalog catalog;
        std::string loadFromFile = "tastatura.txt";

        if (argc > 1) {
            if (strcmp(argv[1], "hibrid") == 0) {
                catalog.SetHibridLoading();
                if (argc > 2) {
                    loadFromFile = argv[2];
                }
            } else {
                loadFromFile = argv[1];
            }

            catalog.loadFromFile(loadFromFile);

            if (catalog.IsHibridLoading()) {
                catalog.displayProducts();
                catalog.displayUsers();
                std::cin >> catalog;
            }
        } else {
            std::cin >> catalog;
        }

        if (!catalog.IsHibridLoading()) {
            catalog.displayProducts();
            catalog.displayUsers();
        }

        std::cout << catalog << std::endl;

    } catch (const InvalidPriceException& e) {
        std::cerr << "Price error: " << e.what() << std::endl;
        Logger::getInstance() += std::string("Error: ") + e.what();
    } catch (const InvalidEmailException& e) {
        std::cerr << "Email error: " << e.what() << std::endl;
        Logger::getInstance() += std::string("Error: ") + e.what();
    } catch (const CatalogException& e) {
        std::cerr << "Catalog error: " << e.what() << std::endl;
        Logger::getInstance() += std::string("Error: ") + e.what();
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        Logger::getInstance() += std::string("Critical Error: ") + e.what();
    }

    return 0;
}