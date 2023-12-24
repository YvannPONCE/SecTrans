#include <iostream>
#include <string>

#include "./../header/main.h"
#include "./../header/server.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Server server(5001);
    std::cin.get();
    server.stop();
    return 0;
}