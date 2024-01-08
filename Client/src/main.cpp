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

int main(int argc, char* argv[]) {

    // Check if there are exactly five command-line arguments
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " -f <file_name> -u <username>" << std::endl;
        return 1; // Return an error code
    }

    std::string option1 = argv[1];
    std::string value1 = argv[2];
    std::string option2 = argv[3];
    std::string value2 = argv[4];

    // Check if the first and third arguments are the -f and -u options
    if (option1 == "-f" && option2 == "-u") {
        // Print the file name and username
        std::string password;
        std::cout << "Enter password: ";
        std::getline(std::cin, password);

        Engine engine;
        engine.sendRequest("INIT", "");
        engine.sendRequest("FILE", value2 + "\n" + password + "\n" + value1  );

    } else {
        std::cerr << "Error: Invalid option sequence. Use -f <file_name> -u <username>" << std::endl;
        return 1; // Return an error code
    }

    return 0; // Return success

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

    //Engine engine;
    //engine.sendRequest("INIT", "");
    //engine.sendRequest("FILE", "./test.txt");
    //return 0;
}