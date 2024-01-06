#ifndef ENCRYPTION_MANAGER_H
#define ENCRYPTION_MANAGER_H

#include <iostream>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>

class EncryptionManager {
private:
   EVP_PKEY* _keyPair = nullptr;
   EVP_PKEY* _serverKeyPair = nullptr;

public:
    EncryptionManager();
    ~EncryptionManager();

    std::string getPublicKey();
    std::string getServerPublicKey();
    void setServerPublicKey(std::string serverPublicKey);
    std::string encrypt(const std::string &plaintext);
    std::string decrypt(std::string data);
};

#endif
