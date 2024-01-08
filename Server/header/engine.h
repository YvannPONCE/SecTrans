// engine.h
#include "./encryptionManager.h"
#include "./client.h"
#include "./authentification.h"
#include "./fileManager.h"

#ifndef ENGINE_H
#define ENGINE_H

class Engine {
private:
    EncryptionManager  _encryptionManager;
    Client _client;
    Authentification _authentification;
    FileManager _fileManager;

    void initConnexion();
    void sendRequest( std::vector<std::string> fileNames);
    void sendRequest(std::string fileName, std::string fileData);
public:
    Engine();
    
    void processRequest(std::string request);
};

#endif
