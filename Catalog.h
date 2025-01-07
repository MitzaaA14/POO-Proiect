// Catalog.h
#ifndef CATALOG_H
#define CATALOG_H

#include "Order.h"
#include <fstream>
#include <algorithm>
#include <exception>

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
public:
    void SetHibridLoading() { hibridLoading = true; };
    bool IsHibridLoading() { return hibridLoading; };

    void loadFromFile(const std::string& fileName);

    void displayProducts() const;

    void displayUsers() const;

    void displayOrders() const;

    friend std::ostream& operator<<(std::ostream& os, const Catalog& catalog);
    friend std::istream& operator>>(std::istream& is, Catalog& catalog);

};

#endif // CATALOG_H

