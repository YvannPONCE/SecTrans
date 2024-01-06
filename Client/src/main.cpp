#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

#include "./../header/main.h"
#include "./../header/client.h"
#include "./../header/fileManager.h"
#include "./../header/wrapper.h"
#include "./../header/encryptionManager.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    EncryptionManager encryptionManager;

    std::string pub_key = encryptionManager.getPublicKey();
    std::cout << "---------------------" << std::endl;
    std::cout << pub_key << std::endl;
    std::cout << "---------------------" << std::endl;
    encryptionManager.setServerPublicKey(pub_key);

    std::string server_pub_key = encryptionManager.getServerPublicKey();

    std::string data = "Hello, World!";
    std::string encryptedData = encryptionManager.encrypt(data);

    std::string decryptedData = encryptionManager.decrypt(encryptedData);
    std::cout << "Decrypted data : " << decryptedData << std::endl;

    Client client(5001);
    std::vector<std::string> fileData = fileManager::read( std::filesystem::path("./test.txt") );
    fileData = fileManager::wrap(fileData);

    std::string hostname = "localhost";
    int port = 5002;

    std::string request = Wrapper::wrap(hostname, port, pub_key);

    client.sendmsg(pub_key);
    return 0;
}