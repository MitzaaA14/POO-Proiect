#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

class User {
private:
    std::string username;
    std::string email;

public:
    User(const std::string& username, const std::string& email)
            : username(username), email(email) {}

    const std::string& getUsername() const { return username; }
    const std::string& getEmail() const { return email; }

    void display() const;

    // Member operator overloading
    bool operator==(const std::string& other_username) const;

    // Non-member operator overloading declaration
    friend std::ostream& operator<<(std::ostream& os, const User& user);
};

#endif // USER_H