#ifndef CATALOG_H
#define CATALOG_H

#include "Order.h"
#include "CustomExceptions.h"
#include "Logger.h"
#include <fstream>
#include <algorithm>
#include <exception>
#include <regex>

class Catalog {
private:
    std::vector<std::unique_ptr<Product>> products;
    std::vector<User> users;
    std::vector<Order> orders;
    bool hibridLoading = false;

    void loadData(std::ifstream& input);
    void loadProducts(std::istream& is);
    void loadUsers(std::istream& is);
    void loadOrders(std::istream& is);

    // Helper method for email validation
    static bool isValidEmail(const std::string& email) {
        std::regex emailPattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
        return std::regex_match(email, emailPattern);
    }

public:
    void SetHibridLoading() { hibridLoading = true; }
    bool IsHibridLoading() const { return hibridLoading; }

    void loadFromFile(const std::string& fileName);

    // New operator overloading as member function
    Catalog& operator+=(const User& user) {
        users.push_back(user);
        Logger::getInstance() += "Added user: " + user.getUsername();
        return *this;
    }

    void displayProducts() const;
    void displayUsers() const;
    void displayOrders() const;

    friend std::ostream& operator<<(std::ostream& os, const Catalog& catalog);
    friend std::istream& operator>>(std::istream& is, Catalog& catalog);
};

#endif // CATALOG_H