#include <iostream>
#include <string>
#include <vector>

#include "../header/engine.h"
#include "../header/wrapper.h"
#include "../header/encryptionManager.h"

Engine::Engine(): _connexions(), _encryptionManager() {

}

void Engine::processRequest(std::string request){
    std::string type = Wrapper::getType(request);
    if(type == "INIT"){
        std::cout << "INIT" << std::endl;
        std::string hostname; 
        int port; 
        std::string clientPublicKey; 
        Wrapper::unWrappInit(request, hostname, port, clientPublicKey);

        std::cout << hostname << std::endl << port << std::endl << clientPublicKey << std::endl;

        _encryptionManager.setClientPublicKey(clientPublicKey);


    }
    else if (type == "CONN")
    {
        std::cout << "CONN" << std::endl;
    }
    else
    {
        std::cout << "None" << std::endl;
    }
    
    
    
}

void Engine::sendPubKey(std::string request){

}