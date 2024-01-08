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
    if (argc != 5 && argc != 4) {
        std::cerr << "Usage: " << argv[0] << " -up    -u <username> <file_path>" << std::endl;
        std::cerr << "Usage: " << argv[0] << " -list  -u <username>            " << std::endl;
        std::cerr << "Usage: " << argv[0] << " -down  -u <username> <file_name>" << std::endl;
        return 1; // Return an error code
    }

    std::string command = argv[1];
    std::string option = argv[2];
    std::string username = argv[3];

    std::string path = "";
    if(argc == 5){
        path = argv[4];
    }
    

    // Check if the first and third arguments are the -f and -u options
    if(option == "-u"){
        if (command == "-up") {
            // Print the file name and username
            std::string password;
            std::cout << "Enter password: ";
            std::getline(std::cin, password);

            Engine engine;
            engine.sendRequest("INIT");
            engine.sendRequest("FILE", username, password, path );
            
            

        } else if (command == "-list") {
            std::string password;
            std::cout << "Enter password: ";
            std::getline(std::cin, password);

            Engine engine;
            engine.sendRequest("INIT");
            engine.sendRequest("LIST", username, password);
        } else if (command == "-down") {
            std::string password;
            std::cout << "Enter password: ";
            std::getline(std::cin, password);

            Engine engine;
            engine.sendRequest("INIT");
            engine.sendRequest("DOWN", username, password, path);
        }else
        {
            std::cerr << "Usage: " << argv[0] << " -up    -u <username> <file_path>" << std::endl;
            std::cerr << "Usage: " << argv[0] << " -list  -u <username>            " << std::endl;
            std::cerr << "Usage: " << argv[0] << " -down  -u <username> <file_name>" << std::endl;
            return 1; // Return an error code
        }
    }else
    {
        std::cerr << "Usage: " << argv[0] << " -up    -u <username> <file_path>" << std::endl;
        std::cerr << "Usage: " << argv[0] << " -list  -u <username>            " << std::endl;
        std::cerr << "Usage: " << argv[0] << " -down  -u <username> <file_name>" << std::endl;
        return 1; // Return an error code
    }
    return 0; // Return success
}