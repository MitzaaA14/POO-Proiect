#include "User.h"
#include "Logger.h"
#include <iostream>

void User::display() const {
    std::cout << "User: " << username << " | Email: " << email << "\n";
}

// Member operator overloading
bool User::operator==(const std::string& other_username) const {
    return username == other_username;
}

// Non-member operator overloading
std::ostream& operator<<(std::ostream& os, const User& user) {
    os << "User: " << user.username << " | Email: " << user.email;
    return os;
}