// Authentification.h
#include <iostream>
#include <unordered_map> 

#ifndef AUTHENTIFICATION_H
#define AUTHENTIFICATION_H

class Authentification {
private:
    std::unordered_map<std::string, std::string> _users ;

    void registerUser(std::string username, std::string password);
public:
    // Constructor
    Authentification();
    bool login(std::string username, std::string password);
    
};

#endif
