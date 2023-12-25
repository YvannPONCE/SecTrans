#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

#include "./../header/main.h"
#include "./../header/server.h"
#include "./../header/client.h"
#include "./../header/fileManager.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Server server(5001);
    std::cin.get();

    std::vector<std::string> fileData = fileManager::read( std::filesystem::path("./test.txt") );
    fileData = fileManager::wrap(fileData);

    Client client(5001);
    for (const std::string& buffer : fileData) {
        client.sendmsg(buffer);
    }
    std::cin.get();

    std::vector<std::string> file = server.getfile();
    fileManager::print(file);
    std::cin.get();
    
    server.stop();
    return 0;
}