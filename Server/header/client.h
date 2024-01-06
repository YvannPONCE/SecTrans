// Client.h

#ifndef CLIENT_H
#define CLIENT_H

class Client {
private:
    void* _clientHandler;
    void loadLibrary(std::string libraryPath);

public:
    // Constructor
    Client();

    /* send message (maximum size: 1024 bytes) */
    int sendmsg(int port, std::string message); 
};

#endif
