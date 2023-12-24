#include <iostream>
#include <cstdlib>
#include <dlfcn.h>
#include <string>

#include "../header/server.h"
#include "../include/server.h"

#define CHUNK_SIZE 1024

Server::Server(int port) : _port(port) {
    loadLibrary("lib/libserver.so");
    typedef int (*startserverFunction)(int);
    startserverFunction startserver = reinterpret_cast<startserverFunction>(dlsym(_serverHandler, "startserver"));
    if (!startserver) {
        std::cerr << "Error getting symbol: " << dlerror() << std::endl;
        dlclose(_serverHandler);
        return;
    }
    startserver(_port);
    std::cout << "Server started on port "<< _port << std::endl;
}

int Server::stop() {
    typedef int (*stopserverFunction)();
    stopserverFunction stopserver = reinterpret_cast<stopserverFunction>(dlsym(_serverHandler, "stopserver"));
    if (!stopserver) {
        std::cerr << "Error getting symbol: " << dlerror() << std::endl;
        dlclose(_serverHandler);
        return 1;
    }
    stopserver();
    dlclose(_serverHandler);
    std::cout << "Server stopped" << std::endl;
    return EXIT_SUCCESS;
}

/* read message sent by client */
std::string Server::getmsg() {
    char message[CHUNK_SIZE];

    typedef int (*getmsgFunction)(const char msg[CHUNK_SIZE]);
    getmsgFunction getmsg = reinterpret_cast<getmsgFunction>(dlsym(_serverHandler, "getmsg"));
    if (!getmsg) {
        std::cerr << "Error getting symbol: " << dlerror() << std::endl;
        dlclose(_serverHandler);
        return "";
    }
    getmsg(message);
    return  std::string(message);
    
}

void Server::loadLibrary(std::string libraryPath)
{
    void* library = dlopen(libraryPath.c_str(), RTLD_LAZY);
    
    if (!library) {
        std::cerr << "Error loading the library: " << dlerror() << std::endl;
        return;
    }
    _serverHandler = library;
}