// CustomExceptions.h
#ifndef CUSTOM_EXCEPTIONS_H
#define CUSTOM_EXCEPTIONS_H

#include <exception>
#include <string>

class CatalogException : public std::exception {
protected:
    std::string message;
public:
    explicit CatalogException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class InvalidPriceException : public CatalogException {
public:
    explicit InvalidPriceException(const std::string& price)
            : CatalogException("Invalid price format: " + price) {}
};

class InvalidEmailException : public CatalogException {
public:
    explicit InvalidEmailException(const std::string& email)
            : CatalogException("Invalid email format: " + email) {}
};

class ProductNotFoundException : public CatalogException {
public:
    explicit ProductNotFoundException(const std::string& name)
            : CatalogException("Product not found: " + name) {}
};

#endif // CUSTOM_EXCEPTIONS_H