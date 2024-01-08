#include <iostream>
#include <cstdlib>
#include <cstring>
#include <dlfcn.h>
#include <string>
#include <vector>

#include "./../header/client.h"

#define CHUNK_SIZE 1024

// Constructor
Client::Client(int port) : _port(port) {
    loadLibrary("../lib/libclient.so");
}

/* send message (maximum size: 1024 bytes) */
int Client::sendmsg(std::string type ,const std::string message)
{
    typedef int (*sndmsgFunction)(const char msg[1024], int port);
    sndmsgFunction sndmsg = reinterpret_cast<sndmsgFunction>(dlsym(_clientHandler, "sndmsg"));
    if (!sndmsg) {
        std::cerr << "Error getting symbol: " << dlerror() << std::endl;
        dlclose(_clientHandler);
        return EXIT_FAILURE;
    } 

    // SPLIT in PART OF 1024
    std::vector<std::string> chunks;
    for (size_t i = 0; i < message.length(); i += CHUNK_SIZE) {
        chunks.push_back(message.substr(i, CHUNK_SIZE));
    }


    sndmsg(type.c_str(), _port);
    for (const auto& chunk : chunks) {
        sndmsg(chunk.c_str(), _port);
    }
    sndmsg("###EOF###", _port);
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