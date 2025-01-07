// Order.h
#ifndef ORDER_H
#define ORDER_H

#include "User.h"
#include "Product.h"
#include <vector>
#include <memory>

class Order {
private:
    User user;
    std::vector<std::unique_ptr<Product>> products;

public:
    Order(const User& user) : user(user) {}

    void addProduct(const Product& product);

    double calculateTotal() const;

    void display() const;
    friend std::ostream& operator<<(std::ostream& os, const Order& order);
};



#endif // ORDER_H
