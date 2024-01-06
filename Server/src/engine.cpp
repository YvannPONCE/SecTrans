#include <iostream>
#include <string>
#include <vector>

#include "../header/engine.h"
#include "../header/wrapper.h"
#include "../header/encryptionManager.h"
#include "../header/client.h"

Engine::Engine(): _connexions(), _encryptionManager(), _client() {}

void Engine::processRequest(std::string request){
    std::string type = Wrapper::getType(request);
    if(type == "INIT"){
        int port; 
        std::string clientPublicKey; 
        Wrapper::unWrappInit(request, port, clientPublicKey);

        _encryptionManager.setClientPublicKey(clientPublicKey);

        std::string response = Wrapper::wrapPUBK(_encryptionManager.getPublicKey());
        _client.sendmsg(port, response);
    }
    else if (type == "CONN")
    {
    }
    else
    {
    }
    
    
    
}

void Engine::sendPubKey(std::string request){

}