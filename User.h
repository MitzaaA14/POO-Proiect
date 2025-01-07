// User.h
#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

class User {
private:
    std::string username;
    std::string email;

public:
    User(const std::string& username, const std::string& email) : username(username), email(email) {}

    const std::string& getUsername() const { return username; }

    void display() const;
};

#endif // USER_H

