#include "Product.h"
#include "Logger.h"

// Non-member operator overloading implementation
Product& operator+(Product& product, double priceIncrease) {
    product.price += priceIncrease;
    Logger::getInstance() += "Increased price of " + product.getName() + " by " + std::to_string(priceIncrease);
    return product;
}

std::ostream& operator<<(std::ostream& os, const Product& product) {
    product.print(os);
    return os;
}

void Electronic::display() const {
    print(std::cout);
}

std::unique_ptr<Product> Electronic::clone() const {
    return std::make_unique<Electronic>(*this);
}

void Food::display() const {
    print(std::cout);
}

std::unique_ptr<Product> Food::clone() const {
    return std::make_unique<Food>(*this);
}

void Clothing::display() const {
    print(std::cout);
}

std::unique_ptr<Product> Clothing::clone() const {
    return std::make_unique<Clothing>(*this);
}