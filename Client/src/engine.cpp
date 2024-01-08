#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "../header/engine.h"
#include "../header/wrapper.h"
#include "../header/encryptionManager.h"
#include "../header/client.h"

#define MAX_SIZE 256

Engine::Engine(): _encryptionManager(), _client(5001), _server(5002) {}

void Engine::sendRequest(std::string type, std::string data){
    if(type == "INIT"){
        std::string request = Wrapper::wrapINIT(5002, _encryptionManager.getPublicKey());
        _client.sendmsg("INIT#" , request.c_str());
        std::string response = waitForResponse();
        processRequest(response);
    }
    else if (type == "FILE")
    {
        std::string path = data;
        std::string file_data = FileManager::read(std::filesystem::path(path));

        std::string cypher = _encryptionManager.encrypt(file_data);
        //std::string plain = _encryptionManager.decrypt(cypher);
        //std::cout << "Plain : " << plain << std::endl;
         _client.sendmsg("FILE#", cypher);
    }
    else
    {
        std::cout << "None" << std::endl;
    }

}

void Engine::processRequest(std::string request){
    std::string type = Wrapper::getType(request);
    if(type == "PUBK"){
        std::string serverPubKey = Wrapper::unwrappPUBK(request);
        _encryptionManager.setServerPublicKey(serverPubKey);
    }
    else if (type == "FILE")
    {
        std::cout << "FILE" << std::endl;
        
    }
    else
    {
        std::cout << "None" << std::endl;
    }
    
}

std::string Engine::waitForResponse(){
    return  _server.getRequest(); 
}