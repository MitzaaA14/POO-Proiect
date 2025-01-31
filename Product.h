#ifndef PRODUCT_H
#define PRODUCT_H

#include "CustomExceptions.h"
#include <iostream>
#include <string>
#include <memory>
#include <regex>

class Product {
protected:
    std::string name;
    double price;

    virtual void print(std::ostream& os) const = 0;

public:
    Product(const std::string& name, double price) : name(name), price(price) {}
    virtual ~Product() = default;

    virtual void display() const = 0;
    virtual std::unique_ptr<Product> clone() const = 0;

    double getPrice() const { return price; }
    const std::string& getName() const { return name; }

    // Static method for price validation
    static bool isValidPrice(const std::string& price) {
        std::regex pricePattern(R"(^\d+(\.\d{1,2})?$)");
        return std::regex_match(price, pricePattern);
    }

    static double validateAndParsePrice(const std::string& priceStr) {
        if (!isValidPrice(priceStr)) {
            throw InvalidPriceException(priceStr);
        }
        return std::stod(priceStr);
    }

    // Non-member operator overloading declaration
    friend Product& operator+(Product& product, double priceIncrease);
    friend std::ostream& operator<<(std::ostream& os, const Product& product);
};

class Electronic : public Product {
    std::string warranty;

protected:
    void print(std::ostream& os) const override {
        os << "Electronic: " << name << " | Price: " << price << " | Warranty: " << warranty << "\n";
    }

public:
    Electronic(const std::string& name, double price, const std::string& warranty)
            : Product(name, price), warranty(warranty) {}

    void display() const override;
    std::unique_ptr<Product> clone() const override;
};

class Food : public Product {
    std::string expirationDate;

protected:
    void print(std::ostream& os) const override {
        os << "Food: " << name << " | Price: " << price << " | Expiration Date: " << expirationDate << "\n";
    }

public:
    Food(const std::string& name, double price, const std::string& expirationDate)
            : Product(name, price), expirationDate(expirationDate) {}

    void display() const override;
    std::unique_ptr<Product> clone() const override;
};

class Clothing : public Product {
    std::string size;

protected:
    void print(std::ostream& os) const override {
        os << "Clothing: " << name << " | Price: " << price << " | Size: " << size << "\n";
    }

public:
    Clothing(const std::string& name, double price, const std::string& size)
            : Product(name, price), size(size) {}

    void display() const override;
    std::unique_ptr<Product> clone() const override;
};

template <class T>
class Generic : public Product {
    std::string type;
    std::string specName;
    T specValue;

protected:
    void print(std::ostream& os) const override {
        os << type << ": " << name << " | Price: " << price << " | " << specName << ": " << specValue << "\n";
    }

public:
    Generic(const std::string& name, double price, const std::string& type, const std::string& specName, const T specValue)
            : Product(name, price), type(type), specName(specName), specValue(specValue) {}

    void display() const override {
        print(std::cout);
    }

    std::unique_ptr<Product> clone() const override {
        return std::make_unique<Generic>(*this);
    }
};

#endif // PRODUCT_H