#include <iostream>
#include <cstdlib>
#include <cstring>
#include <dlfcn.h>
#include <string>

#include "./../header/client.h"

#define CHUNK_SIZE 1024

// Constructor
Client::Client() {
    loadLibrary("lib/libclient.so");
}

/* send message (maximum size: 1024 bytes) */
int Client::sendmsg(int port, std::string message)
{
    typedef int (*sndmsgFunction)(const char msg[1024], int port);
    sndmsgFunction sndmsg = reinterpret_cast<sndmsgFunction>(dlsym(_clientHandler, "sndmsg"));
    if (!sndmsg) {
        std::cerr << "Error getting symbol: " << dlerror() << std::endl;
        dlclose(_clientHandler);
        return EXIT_FAILURE;
    } else if(std::strlen(message.c_str()) > 1024)
    {
        std::cerr << "The message is too big" << std::endl;
        return EXIT_FAILURE;
    }
    sndmsg(message.c_str(), port);
    sndmsg("###EOF###", port);
    std::cout << "Sent : " << std::endl << message << "\n" << std::endl;
    return EXIT_SUCCESS;
}

void Client::loadLibrary(std::string libraryPath)
{
    void* library = dlopen(libraryPath.c_str(), RTLD_LAZY);
    
    if (!library) {
        std::cerr << "Error loading the library: " << dlerror() << std::endl;
        return;
    }
    _clientHandler = library;
}