// account.cpp
#include <string>

#include "./../../header/object/account.h"

// Constructor
Account::Account(std::string username, std::string password): _username(username), _password(password) {}

std::string Account::getUsername(){
    return _username;
}
bool Account::verify(std::string password){
    return password == _password;
}