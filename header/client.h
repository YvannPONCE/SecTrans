// Client.h

#ifndef CLIENT_H
#define CLIENT_H

class Client {
private:
    int _port;
    void* _clientHandler;

    void loadLibrary(std::string libraryPath);

public:
    // Constructor
    Client(int port);

    /* send message (maximum size: 1024 bytes) */
    int sendmsg(std::string message); 
};

#endif
