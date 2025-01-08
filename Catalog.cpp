#include "Catalog.h"
#include <iostream>
#include <fstream>
#include <algorithm>

std::string userPrefix = "user:";

std::istream& operator>>(std::istream& is, Catalog& catalog) {
    Logger::getInstance() += "Starting data input";
    std::cout << "Introdu datele" << std::endl;

    if (!catalog.hibridLoading) {
        catalog.loadProducts(is);
        catalog.loadUsers(is);
    }

    catalog.loadOrders(is);
    return is;
}

void Catalog::loadOrders(std::istream& is) {
    std::string username, produs;

    while (1) {
        std::cout << "nume utilizator pentru comanda: (comenzi introduse: "
                  << orders.size() << ")" << std::endl;
        is >> username;

        if (username.find(".next") != std::string::npos) {
            return;
        }

        auto userIt = std::find_if(users.begin(), users.end(),
                                   [&username](const User& u) { return u.getUsername() == username; });

        if (userIt == users.end()) {
            Logger::getInstance() += "User not found: " + username;
            throw ProductNotFoundException(username);
        }

        Order order(*userIt);
        while(1) {
            std::cout << "produs:" << std::endl;
            is >> produs;

            if (produs.find(".next") != std::string::npos) {
                break;
            }

            auto productIt = std::find_if(products.begin(), products.end(),
                                          [&produs](const std::unique_ptr<Product>& p) { return p->getName() == produs; });

            if (productIt == products.end()) {
                Logger::getInstance() += "Product not found: " + produs;
                throw ProductNotFoundException(produs);
            }

            order.addProduct(**productIt);
            Logger::getInstance() += "Added product " + produs + " to order for " + username;

            std::cout << "scrie .next ca sa finalizezi" << std::endl;
        }
        orders.push_back(std::move(order));

        std::cout << "scrie .next ca sa finalizezi" << std::endl;
    }
}

void Catalog::loadUsers(std::istream& is) {
    std::string nume, email;

    while (1) {
        std::cout << "nume utilizator: (utilizatori introdusi: "
                  << users.size() << ")" << std::endl;
        is >> nume;

        if (nume.find(".next") != std::string::npos) {
            return;
        }

        std::cout << "email:" << std::endl;
        is >> email;

        if (!isValidEmail(email)) {
            throw InvalidEmailException(email);
        }

        users.emplace_back(nume, email);
        Logger::getInstance() += "Added user: " + nume + " with email: " + email;

        std::cout << "scrie .next ca sa treci la introducere comenzi" << std::endl;
    }
}

void Catalog::loadProducts(std::istream& is) {
    std::string tip, nume, spec, tipSpec, priceStr;
    double price;

    while (1) {
        std::cout << "Tip produs (electronic/food/clothing) - ai adaugat pana acum: "
                  << products.size() << std::endl;
        is >> tip;

        if (tip.find(".next") != std::string::npos) {
            return;
        }

        std::cout << "Nume: " << std::endl;
        is >> nume;

        std::cout << "Pret:" << std::endl;
        is >> priceStr;

        try {
            price = Product::validateAndParsePrice(priceStr);
        } catch (const InvalidPriceException& e) {
            Logger::getInstance() += std::string("Price validation failed: ") + e.what();
            throw;
        }

        if (tip.find("electronic") != std::string::npos) {
            std::cout << "Specificatii:" << std::endl;
            is >> spec;
            products.push_back(std::make_unique<Electronic>(nume, price, spec));

        } else if (tip.find("food") != std::string::npos) {
            std::cout << "Specificatii:" << std::endl;
            is >> spec;
            products.push_back(std::make_unique<Food>(nume, price, spec));

        } else if (tip.find("clothing") != std::string::npos) {
            std::cout << "Specificatii:" << std::endl;
            is >> spec;
            products.push_back(std::make_unique<Clothing>(nume, price, spec));

        } else {
            std::cout << "Nume Specificatii:" << std::endl;
            is >> tipSpec;

            std::cout << "Specificatii:" << std::endl;
            if (tipSpec == "size") {
                int intSpec;
                is >> intSpec;
                products.push_back(std::make_unique<Generic<int>>(nume, price, tip, tipSpec, intSpec));
            } else {
                is >> spec;
                products.push_back(std::make_unique<Generic<std::string>>(nume, price, tip, tipSpec, spec));
            }
        }

        Logger::getInstance() += "Added product: " + nume + " of type: " + tip;
        std::cout << "scrie .next ca sa treci la introducere utilizatori" << std::endl;
    }
}

void Catalog::loadFromFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file) {
        Logger::getInstance() += "Failed to open file: " + fileName;
        throw std::runtime_error("Error: Could not open file " + fileName);
    }

    loadData(file);
    Logger::getInstance() += "Successfully loaded data from file: " + fileName;
}

void Catalog::loadData(std::ifstream& input) {
    std::string line;
    std::string section;

    while (std::getline(input, line)) {
        if (line == "Produse:") {
            section = "produse";
            continue;
        } else if (line == "Utilizatori:") {
            section = "utilizatori";
            continue;
        } else if (line == "Comenzi:") {
            section = "comenzi";
            continue;
        }

        try {
            if (section == "produse") {
                // Product loading logic...
                std::string name = line;
                double price;
                input >> price;
                input.ignore();

                std::string description;
                std::getline(input, description);

                if (description.find("Electronic") != std::string::npos) {
                    products.push_back(std::make_unique<Electronic>(name, price, "1 year"));
                } else if (description.find("Food") != std::string::npos) {
                    products.push_back(std::make_unique<Food>(name, price, "2025-12-31"));
                } else if (description.find("Clothing") != std::string::npos) {
                    products.push_back(std::make_unique<Clothing>(name, price, "M"));
                } else {
                    std::string tipSpec;
                    std::getline(input, tipSpec);

                    if (tipSpec == "size") {
                        int intSpec;
                        input >> intSpec;
                        input.ignore();
                        products.push_back(std::make_unique<Generic<int>>(
                                name, price, description, tipSpec, intSpec));
                    } else {
                        std::string strSpec;
                        input >> strSpec;
                        input.ignore();
                        products.push_back(std::make_unique<Generic<std::string>>(
                                name, price, description, tipSpec, strSpec));
                    }
                }
            }
            else if (section == "utilizatori") {
                std::string username = line;
                std::string email;
                std::getline(input, email);

                if (!isValidEmail(email)) {
                    throw InvalidEmailException(email);
                }

                users.emplace_back(username, email);
            }
            else if (section == "comenzi") {
                if (hibridLoading) continue;

                if (line.rfind(userPrefix, 0) == 0) {
                    std::string username = line.substr(userPrefix.length());
                    auto userIt = std::find_if(users.begin(), users.end(),
                                               [&username](const User& u) { return u.getUsername() == username; });

                    if (userIt == users.end()) {
                        throw ProductNotFoundException(username);
                    }

                    orders.emplace_back(*userIt);
                } else {
                    if (orders.empty()) continue;

                    auto productIt = std::find_if(products.begin(), products.end(),
                                                  [&line](const std::unique_ptr<Product>& p) { return p->getName() == line; });

                    if (productIt == products.end()) {
                        throw ProductNotFoundException(line);
                    }

                    orders.back().addProduct(**productIt);
                }
            }
        } catch (const std::exception& e) {
            Logger::getInstance() += std::string("Error while loading data: ") + e.what();
            throw;
        }
    }
}

void Catalog::displayProducts() const {
    std::cout << " ========================= Products ========================== " << std::endl;
    for (const auto& product : products) {
        product->display();
    }
}

void Catalog::displayUsers() const {
    std::cout << " ========================= Users =========================== " << std::endl;
    for (const auto& user : users) {
        user.display();
    }
}

void Catalog::displayOrders() const {
    std::cout << " ========================= Orders =========================== " << std::endl;
    for (const auto& order : orders) {
        order.display();
    }
}

std::ostream& operator<<(std::ostream& os, const Catalog& catalog) {
    os << " ========================= Orders =========================== " << std::endl;
    for (const auto& order : catalog.orders) {
        os << order;
    }
    return os;
}