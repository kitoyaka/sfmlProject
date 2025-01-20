//
// Created by rigry on 19.01.2025.
//

#include "UserManager.h"

void UserManager::loadUsers() {
    std::ifstream  file(filename);
    if(!file.is_open())
    {
        std::cerr << "Could not open the file: " << filename << std::endl;
    }
    std::string line;
    while(std::getline(file, line))
    {
        std::ifstream  iss(line);
        std::string login, password;
        if(std::getline(iss, login, ':') && std::getline(iss, password))
        {
            users[login] = password;
        }
    }

    file.close();
}

void UserManager::saveUsers() {
    std::ofstream file(filename);
    if(file.is_open())
    {
        std::cerr << "Could not oper the file: " << filename << std:: endl;
    }
    for(auto& [login, password] : users)
    {
        file << login << ":" << password << "\n";
    }

    file.close();
}