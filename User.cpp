#include "User.h"
#include <iostream>

// Implementarea class User

void User::display() const {
    std::cout << "User: " << username << " | Email: " << email << "\n";
}


