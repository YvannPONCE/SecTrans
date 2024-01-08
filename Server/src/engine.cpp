#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <filesystem>

#include "../header/engine.h"
#include "../header/wrapper.h"
#include "../header/encryptionManager.h"
#include "../header/client.h"

Engine::Engine(): _connexions(), _encryptionManager(), _client(5002), _authentification(), _fileManager() {}

void Engine::processRequest(std::string request){
    std::string type = request.substr(0,4);
    request = request.substr(5);

    if(type == "INIT"){
         
        std::vector<std::string> requestParameters = Wrapper::unWrappRequest(request);
        std::string clientPublicKey= requestParameters[1];

        _encryptionManager.setClientPublicKey(clientPublicKey);
        _client.sendmsg("PUBK#", _encryptionManager.getPublicKey());
    }
    else if (type == "FILE")
    {   
        std::vector<std::string> requestParameters = Wrapper::unWrappRequest(request);

        std::cout << std::endl;
        std::string plainUsername = _encryptionManager.decrypt(requestParameters[0]);
        std::cout << std::endl;
        std::string plainPassword = _encryptionManager.decrypt(requestParameters[1]);
        std::cout << std::endl;
        std::string plainFileName = _encryptionManager.decrypt(requestParameters[2]);

        if(!_authentification.login(plainUsername, plainPassword)){
            _client.sendmsg("DEND#","");
        }
         _fileManager.registerFile(plainUsername, plainFileName, requestParameters[3]);
        _client.sendmsg("SUCC#","");
           
    } else if (type == "LIST")
    {
        std::vector<std::string> requestParameters = Wrapper::unWrappRequest(request);

        std::cout << std::endl;
        std::string plainUsername = _encryptionManager.decrypt(requestParameters[0]);
        std::cout << std::endl;
        std::string plainPassword = _encryptionManager.decrypt(requestParameters[1]);

        if(!_authentification.login(plainUsername, plainPassword)){
            _client.sendmsg("DEND#","");
        }
        std::vector<std::string> fileNames = FileManager::list(plainUsername);
        sendRequest(fileNames);
    } else if (type == "DOWN")
    {
        std::vector<std::string> requestParameters = Wrapper::unWrappRequest(request);

        std::cout << std::endl;
        std::string plainUsername = _encryptionManager.decrypt(requestParameters[0]);
        std::cout << std::endl;
        std::string plainPassword = _encryptionManager.decrypt(requestParameters[1]);
        std::cout << std::endl;
        std::string plainFileName = _encryptionManager.decrypt(requestParameters[2]);

        if(!_authentification.login(plainUsername, plainPassword)){
            _client.sendmsg("DEND#","");
        }
        std::string cypherFileData = FileManager::readFile(plainUsername, plainFileName);

        std::cout << std::endl;
        std::string cypherFileName = _encryptionManager.encrypt(plainFileName);
        
        sendRequest(cypherFileName , cypherFileData);
    }   
}



void Engine::sendRequest( std::vector<std::string> fileNames){
    std::string request = Wrapper::wrapLIST(fileNames);
    _client.sendmsg("LIST#" , request);
}

void Engine::sendRequest(std::string fileName, std::string fileData){
    std::string request = fileName + static_cast<std::string>("#") + fileData;
    _client.sendmsg("FILE#" , request);
}