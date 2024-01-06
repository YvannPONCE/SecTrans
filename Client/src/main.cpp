#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

#include "./../header/main.h"
#include "./../header/client.h"
#include "./../header/fileManager.h"
#include "./../header/wrapper.h"
#include "./../header/encryptionManager.h"
#include "./../header/engine.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    //EncryptionManager encryptionManager;
//
    //std::string pub_key = encryptionManager.getPublicKey();
    //encryptionManager.setServerPublicKey(pub_key);
//
//
    //std::string data = "Hello, World!";
    //std::string encryptedData = encryptionManager.encrypt(data);
//
    //std::string decryptedData = encryptionManager.decrypt(encryptedData);
    //std::cout << "Decrypted data : " << decryptedData << std::endl;

    Engine engine;
    engine.sendRequest("INIT", "");
    engine.sendRequest("FILE", "./test.txt");
    return 0;
}