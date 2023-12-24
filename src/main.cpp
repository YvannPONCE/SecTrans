#include <iostream>
#include <string>

#include "./../header/main.h"
#include "./../header/server.h"
#include "./../header/client.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Server server(5001);
    std::cin.get();

    Client client(5001);
    client.sendmsg("Hello darling");
    std::cin.get();

    std::string message = server.getmsg();
    std::cout << "Received : " << message << std::endl;
    std::cin.get();
    
    server.stop();
    return 0;
}