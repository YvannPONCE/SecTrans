#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <unistd.h>

#include "./../header/main.h"
#include "./../header/server.h"
#include "./../header/engine.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Engine engine;
    Server server(5001);
    while (true)
    {
        std::string request = server.getRequest();
        engine.processRequest(request);
        sleep(1);
    }
    
    server.stop();
    return 0;
}