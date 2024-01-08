#include <string>
#include <map>
#include <filesystem>

#include "./../header/authentification.h"
#include "./../header/fileManager.h"


Authentification::Authentification(): _users(){}

bool Authentification::login(std::string username, std::string password){
    auto it = _users.find(username);
    if(it == _users.end()){
        registerUser(username, password);
        return true;
    } else
    {
        std::string userPassword = _users[username];
        return userPassword == password;
    }
}

// PRIVATE
void Authentification::registerUser(std::string username, std::string password){
    _users[username] = password;
    FileManager::createFolder(username);
}
