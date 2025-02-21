//
// Created by rigry on 19.01.2025.
//

#include "UserManager.h"
#include <iostream>
#include <fstream>
#include <sstream>


bool UserManager::loginUser(const std::string& login, const std::string& password) {
    auto it  = users.find(login);
    return it != users.end() && it->second == password;
}


void UserManager::registerUser(const std::string& login, const std::string& password) {
    if (users.find(login) != users.end()) {
        return; // Пользователь уже существует
    }
    users[login] = password;
    saveUsers(); // Сохраняем данные в файл
    std::cout << "User registered and saved!" << std::endl;
}



void UserManager::loadUsers() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Для кожного рядка використовуємо istringstream
        std::istringstream iss(line);
        std::string login, password;

        // Парсимо логін і пароль, розділені символом ':'
        if (std::getline(iss, login, ':') && std::getline(iss, password)) {
            users[login] = password;  // Додаємо логін і пароль до мапи(хеша)
        } else {
            std::cerr << "Invalid format in line: " << line << std::endl;
        }
    }

    file.close();
}

void UserManager::saveUsers() {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open the file for writing: " << filename << std::endl;
        return;
    }
    for (const auto& [login, password] : users) {
        file << login << ":" << password << "\n";
    }
    if (file.fail()) {
        std::cerr << "Failed to write to file: " << filename << std::endl;
    } else {
        std::cout << "Users saved to file: " << filename << std::endl;
    }
    file.close();
}

