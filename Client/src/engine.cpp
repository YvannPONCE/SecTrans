#include <iostream>
#include <string>
#include <vector>

#include "../header/engine.h"
#include "../header/wrapper.h"
#include "../header/encryptionManager.h"
#include "../header/client.h"

Engine::Engine(): _encryptionManager(), _client(5001), _server(5002) {}

void Engine::sendRequest(const std::string &type, const std::string &data){
    if(type == "INIT"){
        std::string request = Wrapper::wrapINIT(5002, _encryptionManager.getPublicKey());
        _client.sendmsg(request);
        std::string response = waitForResponse();
        processRequest(response);
    }
    else if (type == "FILE")
    {
        std::string path = data;
        std::string file_data = FileManager::read(std::filesystem::path(path));
        std::string cypher_file_data = _encryptionManager.encrypt(file_data);
        std::cout << "------------" << std::endl;
        std::cout << cypher_file_data << std::endl;
        std::cout << "------------" << std::endl;
        std::string request = Wrapper::wrapFILE(cypher_file_data);
        _client.sendmsg(request);

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