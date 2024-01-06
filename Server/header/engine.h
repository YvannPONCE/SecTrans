// engine.h
#include "object/connexionDetails.h"
#include "./encryptionManager.h"
#include "./client.h"

#ifndef ENGINE_H
#define ENGINE_H

class Engine {
private:
    std::vector<ConnexionDetails> _connexions;
    EncryptionManager  _encryptionManager;
    Client _client;
    void initConnexion();
    void sendPubKey(std::string request);

public:
    Engine();
    
    void processRequest(std::string request);
};

#endif
