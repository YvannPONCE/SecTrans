#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "../header/engine.h"
#include "../header/wrapper.h"
#include "../header/encryptionManager.h"
#include "../header/client.h"

Engine::Engine(): _connexions(), _encryptionManager(), _client() {}

void Engine::processRequest(std::string request){
    std::string type = request.substr(0,4);
    request = request.substr(5);

    if(type == "INIT"){
        int port; 
        std::string clientPublicKey; 
        Wrapper::unWrappInit(request, port, clientPublicKey);

        _encryptionManager.setClientPublicKey(clientPublicKey);

        std::string response = Wrapper::wrapPUBK(_encryptionManager.getPublicKey());
        _client.sendmsg(port, response);
    }
    else if (type == "FILE")
    {   
        std::string plain = _encryptionManager.decrypt(request);
        std::cout << "Plain : " << plain <<  std::endl;
    }
    else
    {
    }
    
    
    
}

void Engine::sendPubKey(std::string request){

}