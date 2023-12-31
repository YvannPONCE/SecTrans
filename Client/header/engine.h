// engine.h
#include "./encryptionManager.h"
#include "./client.h"
#include "./server.h"
#include "./fileManager.h"

#ifndef ENGINE_H
#define ENGINE_H

class Engine {
private:
    EncryptionManager  _encryptionManager;
    Client _client;
    Server _server;

    void startConnexion();

public:
    Engine();
    
    void sendRequest( std::string type);
    void sendRequest(std::string type, std::string username, std::string password, std::string path);
    void sendRequest(std::string type, std::string username, std::string password);
    void processRequest(std::string request);
    std::string waitForResponse();
};

#endif
