#include "Order.h"
#include "Logger.h"
#include <iostream>

void Order::addProduct(const Product& product) {
    products.push_back(product.clone());
    Logger::getInstance() += "Added product " + product.getName() + " to order for " + user.getUsername();
}

double Order::calculateTotal() const {
    double total = 0;
    for (const auto& product : products) {
        total += product->getPrice();
    }
    return total;
}

void Order::display() const {
    std::cout << "\nOrder for " << user.getUsername() << ":\n";
    for (const auto& product : products) {
        product->display();
    }
    std::cout << "Total: " << calculateTotal() << "\n";
}

// Operator overloading as non-member function
std::ostream& operator<<(std::ostream& os, const Order& order) {
    os << "\nOrder for " << order.user.getUsername() << ":\n";
    for (const auto& product : order.products) {
        os << *product;
    }
    os << "Total: " << order.calculateTotal() << "\n";
    return os;
}

// Member operator overloading
Order& Order::operator+=(const Product& product) {
    addProduct(product);
    return *this;
}