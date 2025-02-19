//
// Created by rigry on 19.01.2025.
//

#ifndef SFMLPROJECT_USERMANAGER_H
#define SFMLPROJECT_USERMANAGER_H
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class UserManager {
private:
    std::unordered_map<std::string, std::string> users;
    std::string filename;

public:
    UserManager(const std::string& file) : filename(file) {
        loadUsers();
    }
    ~UserManager()  {
        saveUsers();
    }


    void loadUsers();
    void saveUsers();
    bool loginUser(const std::string& login, const std::string& password);
    void registerUser(const std::string& login, const std::string& password);
};


#endif //SFMLPROJECT_USERMANAGER_H
