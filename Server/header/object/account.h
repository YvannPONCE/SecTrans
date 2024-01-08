// account.h

#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account {
private:
    std::string _username;
    std::string _password;

public:
    // Constructor
    Account(std::string username, std::string password);

    std::string getUsername(); 
    bool verify(std::string password);
};

#endif
