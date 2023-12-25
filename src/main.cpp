#include <iostream>
#include <string>
#include <vector>

#include "./../header/main.h"
#include "./../header/server.h"
#include "./../header/client.h"
#include "./../header/fileREader.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Server server(5001);
    std::cin.get();

    std::vector<std::string> fileData = fileREader::read("./test.txt");

    Client client(5001);
    for (const std::string& buffer : fileData) {
        client.sendmsg(buffer);
    }
    std::cin.get();

    std::string message = server.getmsg();
    std::cout << "Received : " << message << std::endl;
    std::cin.get();
    
    server.stop();
    return 0;
}