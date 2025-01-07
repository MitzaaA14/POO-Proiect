// Main.cpp
#include "Catalog.h"
#include <iostream>
#include <cstring>

int main(int argc, char* argv[]) {

    try {
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
    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << "\n";
    }

    return 0;
}