// Server.h

#ifndef SERVER_H
#define SERVER_H

class Server {
private:
    int _port;
    void* _serverHandler;

    std::string getStringMsg();
    void loadLibrary(std::string libraryPath);

public:
    // Constructor
    Server(int port);
    int stop();

    /* read message sent by client */
    std::vector<std::string> getfile();
};

#endif
