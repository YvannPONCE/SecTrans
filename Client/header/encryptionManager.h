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

    std::string unsignedCharToString(unsigned char* encryptedData, int len);
    void charToUnsignedChar(std::string data, unsigned char* unsigneCharArray, int len);
    std::string unsignedCharToReadableString(unsigned char* decryptedData, int len);

public:
    EncryptionManager();
    ~EncryptionManager();

    std::string getPublicKey();
    std::string getServerPublicKey();
    void setServerPublicKey(std::string serverPublicKey);
    std::string encrypt(const std::string &plaintext);
    std::string ownEncrypt(const std::string &plaintext);
    std::string decrypt(const std::string cypherText);
    void generateNewKey();
    void loadKeyFile();
    static std::string sha256(const std::string& input);
};

#endif
