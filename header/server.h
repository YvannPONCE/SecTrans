// Server.h

#ifndef SERVER_H
#define SERVER_H

class Server {
private:
    int _port;
    void* _serverHandler;

    void* loadLibrary(std::string libraryPath);

public:
    // Constructor
    Server(int port);
    int stop();

    /* read message sent by client */
    int getmsg(char msg_read[1024]);
};

#endif